<?php
/**
 * @file
 * hwc_partner.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function hwc_partner_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_category|node|partner|form';
  $field_group->group_name = 'group_category';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'partner';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Category',
    'weight' => '6',
    'children' => array(
      0 => 'field_category',
      1 => 'field_social_dialog_partner',
      2 => 'field_quote',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-category field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_category|node|partner|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ceo|node|partner|form';
  $field_group->group_name = 'group_ceo';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'partner';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'CEO',
    'weight' => '5',
    'children' => array(
      0 => 'field_ceo_photo',
      1 => 'field_ceo',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-ceo field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_ceo|node|partner|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_guid_main_contact|node|partner|form';
  $field_group->group_name = 'group_guid_main_contact';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'partner';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Main Contact',
    'weight' => '4',
    'children' => array(
      0 => 'field_main_contact',
      1 => 'field_main_contact_email',
      2 => 'field_guid_main_contact',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Main Contact',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-main-contact field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_guid_main_contact|node|partner|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_guid_organisation|node|partner|form';
  $field_group->group_name = 'group_guid_organisation';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'partner';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Guid organisation',
    'weight' => '2',
    'children' => array(
      0 => 'title_field',
      1 => 'field_general_email',
      2 => 'field_general_phone',
      3 => 'field_website',
      4 => 'field_orgtype',
      5 => 'field_bussines_sector',
      6 => 'field_mission_statement',
      7 => 'field_logo',
      8 => 'field_campaign_website',
      9 => 'field_guid_organisation',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-guid-organisation field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_guid_organisation|node|partner|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ph_address|node|partner|form';
  $field_group->group_name = 'group_ph_address';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'partner';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Ph Address',
    'weight' => '3',
    'children' => array(
      0 => 'field_ph_cp',
      1 => 'field_country_code',
      2 => 'field_ph_address_extra',
      3 => 'field_ph_address',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-ph-address field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_ph_address|node|partner|form'] = $field_group;

  return $export;
}
