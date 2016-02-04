<?php
/**
 * @file
 * osha_search.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function osha_search_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'osha_search_ac_categ_limit';
  $strongarm->value = '3';
  $export['osha_search_ac_categ_limit'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'osha_search_ac_fields';
  $strongarm->value = array(
    'attachments_field_file' => 'attachments_field_file',
    'attachments_field_publication_related_res' => 'attachments_field_publication_related_res',
    'attachments_field_related_documents' => 'attachments_field_related_documents',
    'body:summary' => 'body:summary',
    'body:value' => 'body:value',
    'field_summary' => 'field_summary',
    'title_field' => 'title_field',
  );
  $export['osha_search_ac_fields'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'osha_search_ac_index';
  $strongarm->value = 'default_multilingual_node_index';
  $export['osha_search_ac_index'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'osha_search_ac_items_limit';
  $strongarm->value = '3';
  $export['osha_search_ac_items_limit'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'osha_search_bundles';
  $strongarm->value = array(
    'article' => 'article',
    'campaign_materials' => 'campaign_materials',
    'press_contact' => 'press_contact',
    'events' => 'events',
    'infographic' => 'infographic',
    'news' => 'news',
    'partner' => 'partner',
    'practical_tool' => 'practical_tool',
    'press_release' => 'press_release',
    'publication' => 'publication',
    'event_speaker' => 0,
    'external_url' => 0,
    'file' => 0,
    'flickr' => 0,
    'frontpage_slider' => 0,
    'internal_url' => 0,
    'note_to_editor' => 0,
    'slideshare' => 0,
    'webform' => 0,
    'youtube' => 0,
  );
  $export['osha_search_bundles'] = $strongarm;

  return $export;
}
