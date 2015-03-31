<?php
/**
 * @file
 * osha_fop_page.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function osha_fop_page_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function osha_fop_page_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function osha_fop_page_node_info() {
  $items = array(
    'fop_page' => array(
      'name' => 'Focal Point Page',
      'base' => 'node_content',
      'description' => 'Pages that show a country, it\'s focal points and other details',
      'has_title' => '1',
      'title_label' => 'Title',
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
