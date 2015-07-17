<?php
/**
 * @file
 * hwc_homepage.features.inc
 */

/**
 * Implements hook_default_blockgroups().
 */
function hwc_homepage_default_blockgroups() {
  return array(
    'tools_and_resources_block_g' => 'Tools and resources block group',
  );
}

/**
 * Implements hook_ctools_plugin_api().
 */
function hwc_homepage_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function hwc_homepage_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_fe_nodequeue_export_fields().
 */
function hwc_homepage_fe_nodequeue_export_fields() {
  $nodequeues = array();

  // Exported nodequeues: featured_partner_frontpage
  $nodequeues['featured_partner_frontpage'] = array(
    'name' => 'featured_partner_frontpage',
    'title' => 'Featured Partner Frontpage',
    'subqueue_title' => '',
    'size' => 1,
    'link' => '',
    'link_remove' => '',
    'owner' => 'nodequeue',
    'show_in_ui' => 1,
    'show_in_tab' => 1,
    'show_in_links' => 0,
    'reference' => 0,
    'reverse' => 0,
    'i18n' => 0,
    'subqueues' => 1,
    'types' => array(
      0 => 'partner',
    ),
    'roles' => array(),
    'count' => 0,
  );

  return $nodequeues;
}

/**
 * Implements hook_node_info().
 */
function hwc_homepage_node_info() {
  $items = array(
    'frontpage_slider' => array(
      'name' => t('Frontpage Banner'),
      'base' => 'node_content',
      'description' => t('Frontpage slider content'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
