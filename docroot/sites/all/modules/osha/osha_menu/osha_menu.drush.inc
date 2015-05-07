<?php

/**
 * Implements COMMANDFILE_drush_command().
 */
function osha_menu_drush_command() {
  $items = array();
  $items['osha-menu-import-translations'] = array(
    'description' => 'Import menu translations from files',
    'aliases' => array('oshmitran'),
    'examples' => array(),
  );
  return $items;
}


function drush_osha_menu_import_translations() {
  $languages = osha_language_list();
  $module_path = drupal_realpath(drupal_get_path('module', 'osha_menu'));
  $translation_folder_path = $module_path . '/' . 'translations';
  $updated_count = 0;
  $created_count = 0;
  $failed_count = 0;
  $unchanged_count = 0;
  foreach (array_keys($languages) as $lang) {
    $file_path = $translation_folder_path . '/menus_' . $lang . '.csv';
    if (file_exists($file_path)) {
      $handle = fopen($file_path, 'r');
      while (($raw_data = fgetcsv($handle)) !== FALSE) {
        // Get the source string.
        $lid = db_select('locales_source', 'ls')
          ->fields('ls', array('lid'))
          ->condition('location', $raw_data[0])
          ->execute()
          ->fetchField(0);

        // Collect info if is unchanged.
        $target = db_select('locales_target', 'lt')
          ->fields('lt', array('lid', 'translation'))
          ->condition('lid', $lid)
          ->condition('language', $lang)
          ->execute()
          ->fetchField(1);
        if (!empty($target)) {
          if (strcmp($raw_data[2], $target) === 0) {
            $unchanged_count++;
          }
        }

        // Insert/update the record.
        $translation = array(
          'lid' => $lid,
          'language' => $lang,
          'plural' => 0,
          'translation' => $raw_data[2],
        );
        $write = drupal_write_record('locales_target', $translation,
          array('language', 'lid', 'plural'));
        if ($write == SAVED_NEW) {
          $created_count++;
        }
        elseif ($write == SAVED_UPDATED) {
          $updated_count++;
        }
        else {
          $failed_count++;
        }
      }
    }
  }
  drupal_set_message(strtr('Parsed @no menus translations',
    array('@no' => $created_count + $updated_count + $failed_count)),
    'success');
  drupal_set_message(strtr('- Created @no menus translations', array('@no' => $created_count)));
  drupal_set_message(strtr('- Updated @no menus translations', array('@no' => $updated_count)));
  if ($failed_count) {
    drupal_set_message(strtr('- Failed @no menus translations', array('@no' => $failed_count)), 'warning');
  }
  drupal_set_message(strtr('-- Unchanged @no menus translations', array('@no' => $unchanged_count)));
}