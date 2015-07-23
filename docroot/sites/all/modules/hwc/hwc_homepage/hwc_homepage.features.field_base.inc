<?php
/**
 * @file
 * hwc_homepage.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function hwc_homepage_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'eq_node'
  $field_bases['eq_node'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'entityqueue_subqueue',
    ),
    'field_name' => 'eq_node',
    'indexes' => array(
      'target_id' => array(
        0 => 'target_id',
      ),
    ),
    'locked' => 1,
    'module' => 'entityreference',
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'handler' => 'entityqueue',
      'handler_settings' => array(
        'behaviors' => array(
          'entityqueue' => array(
            'status' => 1,
          ),
        ),
      ),
      'target_type' => 'node',
    ),
    'translatable' => 0,
    'type' => 'entityreference',
  );

  // Exported field_base: 'field_find_out_more_link'
  $field_bases['field_find_out_more_link'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_find_out_more_link',
    'indexes' => array(
      'tid' => array(
        0 => 'tid',
      ),
    ),
    'locked' => 0,
    'module' => 'taxonomy',
    'settings' => array(
      'allowed_values' => array(
        0 => array(
          'vocabulary' => 'frontpage_banner_links',
          'parent' => 0,
        ),
      ),
      'entity_translation_sync' => FALSE,
      'options_list_callback' => 'i18n_taxonomy_allowed_values',
    ),
    'translatable' => 0,
    'type' => 'taxonomy_term_reference',
  );

  return $field_bases;
}
