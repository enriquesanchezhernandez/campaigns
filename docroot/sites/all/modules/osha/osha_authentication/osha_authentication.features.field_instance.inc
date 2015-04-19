<?php
/**
 * @file
 * osha_authentication.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function osha_authentication_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'user-user-field_ldap_homedirectory'
  $field_instances['user-user-field_ldap_homedirectory'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 13,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_ldap_homedirectory',
    'label' => 'homeDirectory LDAP attribute',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'linkit' => array(
        'button_text' => 'Search',
        'enable' => 0,
        'profile' => '',
      ),
      'text_processing' => 0,
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 49,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('homeDirectory LDAP attribute');

  return $field_instances;
}
