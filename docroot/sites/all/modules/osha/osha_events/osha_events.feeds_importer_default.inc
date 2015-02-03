<?php
/**
 * @file
 * osha_events.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function osha_events_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'import_events';
  $feeds_importer->config = array(
    'name' => 'Import Events',
    'description' => 'Import Events',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'allowed_extensions' => 'txt csv tsv xml opml',
        'direct' => 1,
        'directory' => 'public://feeds',
        'allowed_schemes' => array(
          'public' => 'public',
        ),
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => ';',
        'no_headers' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => 0,
        'authorize' => 1,
        'mappings' => array(
          0 => array(
            'source' => 'Title of the event',
            'target' => 'title',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'Organization',
            'target' => 'field_organization',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'Country code',
            'target' => 'field_country_code',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'City',
            'target' => 'field_city',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'Start date',
            'target' => 'field_start_date:start',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'End date',
            'target' => 'field_start_date:end',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'Theme',
            'target' => 'field_tags',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'Title of website',
            'target' => 'field_website_of_event:title',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'Website of event',
            'target' => 'field_website_of_event:url',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'Adonis',
            'target' => 'field_adonis',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'Unit ref',
            'target' => 'field_unit_ref',
            'unique' => FALSE,
          ),
          11 => array(
            'source' => 'Activity',
            'target' => 'field_activity',
            'term_search' => '0',
            'autocreate' => 0,
          ),
          12 => array(
            'source' => 'Agency role',
            'target' => 'field_agency_role',
            'unique' => FALSE,
          ),
          13 => array(
            'source' => 'Agency initial contact',
            'target' => 'field_agency_initial_contact',
            'unique' => FALSE,
          ),
          14 => array(
            'source' => 'Agency rep confirmed',
            'target' => 'field_agency_rep_confirmed',
            'unique' => FALSE,
          ),
          15 => array(
            'source' => 'Agency contact',
            'target' => 'field_agency_contact_reply',
            'unique' => FALSE,
          ),
          16 => array(
            'source' => 'Comments',
            'target' => 'field_comments_summary_after_eve',
            'unique' => FALSE,
          ),
          17 => array(
            'source' => 'Number of attendees',
            'target' => 'field_number_of_attendees',
            'unique' => FALSE,
          ),
          18 => array(
            'source' => 'Description',
            'target' => 'body',
            'unique' => FALSE,
          ),
          19 => array(
            'source' => 'Language',
            'target' => 'language',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'full_html',
        'skip_hash_check' => 0,
        'bundle' => 'events',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['import_events'] = $feeds_importer;

  return $export;
}
