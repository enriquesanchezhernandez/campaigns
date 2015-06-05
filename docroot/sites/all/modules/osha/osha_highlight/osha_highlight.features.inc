<?php
/**
 * @file
 * osha_highlight.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function osha_highlight_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function osha_highlight_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function osha_highlight_node_info() {
  $items = array(
    'highlight' => array(
      'name' => 'Highlight',
      'base' => 'node_content',
      'description' => 'EU-OSHA news',
      'has_title' => '1',
      'title_label' => 'Title',
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
