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
  $strongarm->name = 'osha_search_ac_items_limit';
  $strongarm->value = '3';
  $export['osha_search_ac_items_limit'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'osha_search_bundles';
  $strongarm->value = array(
    'article' => 'article',
    'blog' => 'blog',
    'calls' => 'calls',
    'directive' => 'directive',
    'events' => 'events',
    'guideline' => 'guideline',
    'highlight' => 'highlight',
    'news' => 'news',
    'press_release' => 'press_release',
    'publication' => 'publication',
    'seminar' => 'seminar',
    'wiki_page' => 'wiki_page',
    'banner' => 0,
    'page' => 0,
    'external_url' => 0,
    'file' => 0,
    'flickr' => 0,
    'job_vacancies' => 0,
    'newsletter_article' => 0,
    'note_to_editor' => 0,
    'press_contact' => 0,
    'slideshare' => 0,
    'youtube' => 0,
  );
  $export['osha_search_bundles'] = $strongarm;

  return $export;
}
