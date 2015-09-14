<?php
/**
 * @file
 * osha_news.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function osha_news_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|news|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'news';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'hwc_2col_stacked_2col';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'metatags',
        1 => 'path',
        2 => 'redirect',
        3 => 'workbench_access',
      ),
      'center' => array(
        4 => 'title_field',
        5 => 'field_summary',
        6 => 'field_image',
        7 => 'field_image_caption',
        8 => 'body',
        9 => 'field_publication_date',
        10 => 'field_expiration_date',
        11 => 'field_aditional_resources',
      ),
      'footer' => array(
        12 => 'field_activity',
        13 => 'field_tags',
        14 => 'field_page_count',
        15 => 'field_character_count',
        16 => 'field_archived',
      ),
      'hidden' => array(
        17 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'metatags' => 'header',
      'path' => 'header',
      'redirect' => 'header',
      'workbench_access' => 'header',
      'title_field' => 'center',
      'field_summary' => 'center',
      'field_image' => 'center',
      'field_image_caption' => 'center',
      'body' => 'center',
      'field_publication_date' => 'center',
      'field_expiration_date' => 'center',
      'field_aditional_resources' => 'center',
      'field_activity' => 'footer',
      'field_tags' => 'footer',
      'field_page_count' => 'footer',
      'field_character_count' => 'footer',
      'field_archived' => 'footer',
      '_add_existing_field' => 'hidden',
    ),
    'classes' => array(
      'layout_class' => array(
        'container' => 'container',
      ),
      'header' => array(
        'col-md-12' => 'col-md-12',
      ),
      'left' => array(
        'col-sm-6' => 'col-sm-6',
      ),
      'right' => array(
        'col-sm-6' => 'col-sm-6',
      ),
      'center' => array(
        'col-md-12' => 'col-md-12',
      ),
      'left2' => array(
        'col-sm-6' => 'col-sm-6',
      ),
      'right2' => array(
        'col-sm-6' => 'col-sm-6',
      ),
      'footer' => array(
        'col-md-12' => 'col-md-12',
      ),
    ),
    'wrappers' => array(
      'header' => 'div',
      'left' => 'div',
      'right' => 'div',
      'center' => 'div',
      'left2' => 'div',
      'right2' => 'div',
      'footer' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|news|form'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|news|teaser';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'news';
  $ds_layout->view_mode = 'teaser';
  $ds_layout->layout = 'ds_2col';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'field_image',
      ),
      'right' => array(
        1 => 'title_field',
        2 => 'field_summary',
        3 => 'field_publication_date',
        4 => 'body',
      ),
    ),
    'fields' => array(
      'field_image' => 'left',
      'title_field' => 'right',
      'field_summary' => 'right',
      'field_publication_date' => 'right',
      'body' => 'right',
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
  $export['node|news|teaser'] = $ds_layout;

  return $export;
}
