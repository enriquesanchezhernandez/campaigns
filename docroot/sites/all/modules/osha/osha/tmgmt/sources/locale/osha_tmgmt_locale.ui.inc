<?php

class OSHATMGMTLocaleSourceUIController extends TMGMTLocaleSourceUIController {

  /**
   * Gets locale strings.
   *
   * @param string $textgroup
   *   The locale textgroup.
   * @param string $search_label
   *   Label to search for.
   * @param string $missing_target_language
   *   Missing translation language.
   *
   * @return array
   *   List of i18n strings data.
   */
  function getStrings($textgroup, $search_label = NULL, $missing_target_language = NULL) {
    $osha = cache_get('osha:osha_tmgmt_i18n_string_list');
    if (empty($osha)) {
      $strings = module_invoke_all('osha_tmgmt_i18n_string_list');
      $strings = array_unique($strings);
      $osha = array();
      $all = db_select('locales_source', 'ls')
        ->fields('ls', array('lid', 'source'))
        ->condition('ls.textgroup', $textgroup)
        ->execute()->fetchAllAssoc('lid');
      foreach ($all as $id => $ob) {
        if (in_array($ob->source, $strings)) {
          $osha[] = $id;
        }
      }
      cache_set('osha:osha_tmgmt_i18n_string_list', $osha, 'cache', CACHE_TEMPORARY);
    }
    else {
      $osha = $osha->data;
    }
    $languages = drupal_map_assoc(array_keys(language_list()));
    $select = db_select('locales_source', 'ls')
      ->fields('ls', array('lid', 'source'))
      ->condition('ls.textgroup', $textgroup)
      ->condition('ls.lid', $osha, 'in')
      ->orderBy('source');
    if (!empty($search_label)) {
      $select->where('LOWER(CAST(ls.source AS CHAR)) LIKE :search',
        array(':search' => "%" . db_like(strtolower($search_label)) . "%"));
    }
    if (!empty($missing_target_language) && in_array($missing_target_language, $languages)) {
      $select->isNull("lt_$missing_target_language.language");
    }
    foreach ($languages as $langcode) {
      $langcode = str_replace('-', '', $langcode);
      $select->leftJoin('locales_target', "lt_$langcode", "ls.lid = %alias.lid AND %alias.language = '$langcode'");
      $select->addField("lt_$langcode", 'language', "lang_$langcode");
    }
    $select = $select->extend('PagerDefault')->limit(variable_get('tmgmt_source_list_limit', 20));
    return $select->execute()->fetchAll();
  }

  /**
   * Helper function to create translation data list for the sources page list.
   *
   * @param array $strings
   *   Result of the search query returned by tmgmt_i18n_string_get_strings().
   * @param string $type
   *   I18n object type.
   *
   * @return array
   *   Structured array with translation data.
   */
  protected function getTranslationData($strings, $type) {
    $objects = array();
    // Source language of locale strings is always english.
    $source_language = 'en';

    foreach ($strings as $string) {
      $id = $string->lid;
      // Get existing translations and current job items for the entity
      // to determine translation statuses
      $current_job_items = osha_tmgmt_job_item_load_latest('locale', $type, $id, $source_language);
      $objects[$id] = array(
        'id' => $id,
        'object' => $string
      );
      // Load entity translation specific data.
      foreach (language_list() as $langcode => $language) {
        $langcode = str_replace('-', '', $langcode);

        $translation_status = 'current';

        if ($langcode == $source_language) {
          $translation_status = 'original';
        }
        elseif ($string->{'lang_' . $langcode} === NULL) {
          $translation_status = 'missing';
        }

        $objects[$id]['current_job_items'][$langcode] = isset($current_job_items[$langcode]) ? $current_job_items[$langcode] : NULL;
        $objects[$id]['translation_statuses'][$langcode] = $translation_status;
      }
    }
    return $objects;
  }
}
