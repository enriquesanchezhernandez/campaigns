<?php
/**
 * @file
 * osha_authentication.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function osha_authentication_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_ldap_homedirectory'
  $field_bases['field_ldap_homedirectory'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_ldap_homedirectory',
    'foreign keys' => array(
      'format' => array(
        'columns' => array(
          'format' => 'format',
        ),
        'table' => 'filter_format',
      ),
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  return $field_bases;
}
