<?php
/**
 * @file
 * osha_legislation.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function osha_legislation_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function osha_legislation_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function osha_legislation_node_info() {
  $items = array(
    'directive' => array(
      'name' => 'Directive',
      'base' => 'node_content',
      'description' => 'Legislation directives',
      'has_title' => '1',
      'title_label' => 'Title',
      'help' => '',
    ),
    'guideline' => array(
      'name' => 'Guideline',
      'base' => 'node_content',
      'description' => 'Legislation guidelines',
      'has_title' => '1',
      'title_label' => 'Title',
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
