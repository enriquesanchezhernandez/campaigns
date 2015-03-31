<?php
/**
 * @file
 * osha_blog.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function osha_blog_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function osha_blog_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function osha_blog_node_info() {
  $items = array(
    'blog' => array(
      'name' => 'Blog',
      'base' => 'node_content',
      'description' => 'Blog articles',
      'has_title' => '1',
      'title_label' => 'Title',
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
