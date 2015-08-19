<?php
/**
 * @file
 * campaign_materials.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function campaign_materials_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|campaign_materials|teaser';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'campaign_materials';
  $ds_layout->view_mode = 'teaser';
  $ds_layout->layout = 'ds_2col';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'field_image',
      ),
      'right' => array(
        1 => 'title_field',
        2 => 'field_publication_date',
        3 => 'body',
        4 => 'field_related_documents',
      ),
    ),
    'fields' => array(
      'field_image' => 'left',
      'title_field' => 'right',
      'field_publication_date' => 'right',
      'body' => 'right',
      'field_related_documents' => 'right',
    ),
    'classes' => array(
      'layout_class' => array(
        'row' => 'row',
      ),
      'left' => array(
        'col-md-2' => 'col-md-2',
      ),
      'right' => array(
        'col-md-10' => 'col-md-10',
      ),
    ),
    'wrappers' => array(
      'left' => 'div',
      'right' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'layout_disable_css' => 1,
  );
  $export['node|campaign_materials|teaser'] = $ds_layout;

  return $export;
}
