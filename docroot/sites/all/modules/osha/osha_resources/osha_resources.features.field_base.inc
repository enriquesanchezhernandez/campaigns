<?php
/**
 * @file
 * osha_resources.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function osha_resources_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_external_url'.
  $field_bases['field_external_url'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_external_url',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'link',
    'settings' => array(
      'attributes' => array(
        'class' => '',
        'rel' => '',
        'target' => 'default',
      ),
      'display' => array(
        'url_cutoff' => 80,
      ),
      'enable_tokens' => 1,
      'entity_translation_sync' => FALSE,
      'title' => 'optional',
      'title_maxlength' => 128,
      'title_value' => '',
      'url' => 0,
    ),
    'translatable' => 0,
    'type' => 'link_field',
  );

  // Exported field_base: 'field_flickr'.
  $field_bases['field_flickr'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_flickr',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'flickrfield',
    'settings' => array(
      'entity_translation_sync' => FALSE,
    ),
    'translatable' => 1,
    'type' => 'flickrfield',
  );

  // Exported field_base: 'field_internal_contents'.
  $field_bases['field_internal_contents'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_internal_contents',
    'indexes' => array(
      'target_id' => array(
        0 => 'target_id',
      ),
    ),
    'locked' => 0,
    'module' => 'entityreference',
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'handler' => 'base',
      'handler_settings' => array(
        'behaviors' => array(
          'views-select-list' => array(
            'status' => 0,
          ),
        ),
        'sort' => array(
          'type' => 'none',
        ),
        'target_bundles' => array(
          'article' => 'article',
          'calls' => 'calls',
          'news' => 'news',
          'press_release' => 'press_release',
          'publication' => 'publication',
        ),
      ),
      'target_type' => 'node',
    ),
    'translatable' => 1,
    'type' => 'entityreference',
  );

  // Exported field_base: 'field_slideshare'.
  $field_bases['field_slideshare'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_slideshare',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'osha_slideshare',
    'settings' => array(
      'api_key' => '6WKMTITI',
      'entity_translation_sync' => FALSE,
      'secret_key' => 'v1HYiYhg',
    ),
    'translatable' => 1,
    'type' => 'slideshare',
  );

  // Exported field_base: 'field_youtube'.
  $field_bases['field_youtube'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_youtube',
    'indexes' => array(
      'video_id' => array(
        0 => 'video_id',
      ),
    ),
    'locked' => 0,
    'module' => 'youtube',
    'settings' => array(
      'entity_translation_sync' => FALSE,
    ),
    'translatable' => 1,
    'type' => 'youtube',
  );

  return $field_bases;
}
