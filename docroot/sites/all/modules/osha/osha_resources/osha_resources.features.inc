<?php
/**
 * @file
 * osha_resources.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function osha_resources_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function osha_resources_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function osha_resources_image_default_styles() {
  $styles = array();

  // Exported image style: youtube_thumbnail.
  $styles['youtube_thumbnail'] = array(
    'label' => 'Youtube Thumbnail',
    'effects' => array(
      1 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 75,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function osha_resources_node_info() {
  $items = array(
    'external_url' => array(
      'name' => t('External URL'),
      'base' => 'node_content',
      'description' => t('Additional resources - external URL'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'file' => array(
      'name' => t('File'),
      'base' => 'node_content',
      'description' => t('Additional resources - internal files'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'flickr' => array(
      'name' => t('Flickr'),
      'base' => 'node_content',
      'description' => t('Additional resources - Flickr photos'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'slideshare' => array(
      'name' => t('Slideshare'),
      'base' => 'node_content',
      'description' => t('Additional resources - Slideshare presentations'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'youtube' => array(
      'name' => t('Youtube'),
      'base' => 'node_content',
      'description' => t('Additional resources - Youtube videos'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
