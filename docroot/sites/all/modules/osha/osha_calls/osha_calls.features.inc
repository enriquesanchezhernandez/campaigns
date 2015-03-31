<?php
/**
 * @file
 * osha_calls.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function osha_calls_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "quicktabs" && $api == "quicktabs") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function osha_calls_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function osha_calls_node_info() {
  $items = array(
    'calls' => array(
      'name' => 'Calls',
      'base' => 'node_content',
      'description' => 'Calls for proposals',
      'has_title' => '1',
      'title_label' => 'Title',
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
