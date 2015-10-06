<?php
/**
 * @file
 * hwc.ds.inc
 */

/**
 * Implements hook_ds_custom_fields_info().
 */
function hwc_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'top_anchor';
  $ds_field->label = 'Top anchor';
  $ds_field->field_type = 3;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '*|*';
  $ds_field->properties = array();
  $export['top_anchor'] = $ds_field;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function hwc_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|flickr|osha_resources';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'flickr';
  $ds_layout->view_mode = 'osha_resources';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_flickr',
      ),
    ),
    'fields' => array(
      'field_flickr' => 'ds_content',
    ),
    'classes' => array(
      'layout_class' => array(
        '' => '',
      ),
    ),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|flickr|osha_resources'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|youtube|osha_resources';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'youtube';
  $ds_layout->view_mode = 'osha_resources';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_youtube',
        1 => 'title_field',
      ),
    ),
    'fields' => array(
      'field_youtube' => 'ds_content',
      'title_field' => 'ds_content',
    ),
    'classes' => array(
      'layout_class' => array(
        'col-sm-4' => 'col-sm-4',
      ),
    ),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|youtube|osha_resources'] = $ds_layout;

  return $export;
}
