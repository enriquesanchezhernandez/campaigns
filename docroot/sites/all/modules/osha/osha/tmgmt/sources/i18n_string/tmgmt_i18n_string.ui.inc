<?php

/**
 * Class OSHATMGMTI18nStringDefaultSourceUIController overrides in order to remove from screen the menu links already
 * present inside the translation cart.
 */
class OSHATMGMTI18nStringDefaultSourceUIController extends TMGMTI18nStringDefaultSourceUIController {

  /**
   * {@inheritdoc}
   */
  public function overviewForm($form, &$form_state, $type) {
    $form += $this->overviewSearchFormPart($form, $form_state, $type);

    $form['items'] = array(
      '#type' => 'tableselect',
      '#header' => $this->overviewFormHeader($type),
      '#empty' => t('No strings matching given criteria have been found.')
    );

    $search_data = $this->getSearchFormSubmittedParams();

    $i18n_strings = osha_tmgmt_i18n_string_get_strings($type, $search_data['label'], $search_data['target_language'], $search_data['target_status']);

    foreach ($this->getTranslationData($i18n_strings, $form_state['item_type']) as $id => $data) {
      $form['items']['#options'][$id] = $this->overviewRow($type, $data);
    }

    $form['pager'] = array('#markup' => theme('pager', array('tags' => NULL)));

    return $form;
  }

}

/**
 * Gets i18n strings for given type and label. We override this to intersect with cart items.
 *
 * @param string $type
 *   i18n object type.
 * @param string $search_label
 *   Label to search for.
 * @param string $target_language
 *   Target language.
 * @param string $target_status
 *   Target status.
 *
 * @return array
 *   List of i18n strings data.
 */
function osha_tmgmt_i18n_string_get_strings($type, $search_label = NULL, $target_language = NULL, $target_status = 'untranslated_or_outdated') {
  $info = i18n_object_info($type);

  $languages = drupal_map_assoc(array_keys(language_list()));
  $select = db_select('i18n_string', 'i18n_s');

  $select->condition('i18n_s.textgroup', $info['string translation']['textgroup']);

  if (!empty($target_language) && in_array($target_language, $languages)) {
    if ($target_status == 'untranslated_or_outdated') {
      $or = db_or();
      $or->isNull("lt_$target_language.language");
      $or->condition("lt_$target_language.i18n_status", I18N_STRING_STATUS_UPDATE);
      $select->condition($or);
    }
    elseif ($target_status == 'outdated') {
      $select->condition("lt_$target_language.i18n_status", I18N_STRING_STATUS_UPDATE);
    }
    elseif ($target_status == 'untranslated') {
      $select->isNull("lt_$target_language.language");
    }
  }

  if (isset($info['string translation']['type'])) {
    $select->condition('i18n_s.type', $info['string translation']['type']);
  }
  elseif ($type == 'field' || $type == 'field_instance') {
    // Fields and field instances share the same textgroup. Use list of bundles
    // to include/exclude field_instances.
    $bundles = array();
    foreach (entity_get_info() as $entity_info) {
      $bundles = array_merge($bundles, array_keys($entity_info['bundles']));
    }
    $select->condition('i18n_s.objectid', $bundles, $type == 'field_instance' ? 'IN' : 'NOT IN');
  }

  $select->join('locales_source', 'ls', 'ls.lid = i18n_s.lid');
  $select->addField('ls', 'source');
  if (!empty($search_label)) {
    $select->where('LOWER(CAST(ls.source AS CHAR)) LIKE :search',
      array(':search' => "%" . db_like(strtolower($search_label)) . "%"));
  }

  foreach ($languages as $langcode) {
    $langcode = str_replace('-', '', $langcode);
    $select->leftJoin('locales_target', "lt_$langcode", "i18n_s.lid = %alias.lid AND %alias.language = '$langcode'");
    $select->addField("lt_$langcode", 'language', "lang_$langcode");
  }
  $select->fields("i18n_s", array('lid', 'textgroup', 'context', 'type', 'objectid'));

  $select->addExpression("concat(i18n_s.textgroup, ':', i18n_s.type, ':', i18n_s.objectid)", 'job_item_id');

  // Intersect with the cart and remove items already added to the cart
  $cart = tmgmt_ui_cart_get();
  $job_items = $cart->getJobItemsFromCart();
  $cart_ids = array();
  foreach ($job_items as $job_item) {
    if ($job_item->item_type == 'menu_link') {
      $cart_ids[] = "'" . $job_item->item_id . "'";
    }
  }
  if (!empty($cart_ids)) {
    $select->where(sprintf("concat(i18n_s.textgroup, ':', i18n_s.type, ':', i18n_s.objectid) NOT IN (%s)", implode(',', $cart_ids)));
  }
  $select->orderBy('i18n_s.context');

  $select->groupBy('type');
  $select->groupBy('objectid');

  $select = $select->extend('PagerDefault')->limit(variable_get('tmgmt_source_list_limit', 20));

  return $select->execute()->fetchAll();
}