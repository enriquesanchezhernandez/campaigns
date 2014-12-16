<?php
/**
 * @file
 * osha_infographics.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function osha_infographics_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function osha_infographics_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function osha_infographics_node_info() {
  $items = array(
    'infographic' => array(
      'name' => t('Infographic'),
      'base' => 'node_content',
      'description' => t('Infographic content type'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
