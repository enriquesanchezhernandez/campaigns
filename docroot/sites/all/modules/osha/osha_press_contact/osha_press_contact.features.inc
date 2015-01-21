<?php
/**
 * @file
 * osha_press_contact.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function osha_press_contact_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function osha_press_contact_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_fe_nodequeue_export_fields().
 */
function osha_press_contact_fe_nodequeue_export_fields() {
  $nodequeues = array();

  // Exported nodequeues: press_contacts_queue
  $nodequeues['press_contacts_queue'] = array(
    'name' => 'press_contacts_queue',
    'title' => 'Press Contacts',
    'subqueue_title' => '',
    'size' => 0,
    'link' => '',
    'link_remove' => '',
    'owner' => 'nodequeue',
    'show_in_ui' => 1,
    'show_in_tab' => 1,
    'show_in_links' => 0,
    'reference' => 0,
    'reverse' => 0,
    'i18n' => 1,
    'subqueues' => 1,
    'types' => array(
      0 => 'press_contact',
    ),
    'roles' => array(),
    'count' => 0,
  );

  return $nodequeues;
}

/**
 * Implements hook_node_info().
 */
function osha_press_contact_node_info() {
  $items = array(
    'press_contact' => array(
      'name' => t('Press contact'),
      'base' => 'node_content',
      'description' => t('Press contacts (used by press releases)'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
