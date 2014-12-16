<?php
/**
 * @file
 * osha_calls.quicktabs.inc
 */

/**
 * Implements hook_quicktabs_default_quicktabs().
 */
function osha_calls_quicktabs_default_quicktabs() {
  $export = array();

  $quicktabs = new stdClass();
  $quicktabs->disabled = FALSE; /* Edit this to true to make a default quicktabs disabled initially */
  $quicktabs->api_version = 1;
  $quicktabs->machine_name = 'calls_quicktab';
  $quicktabs->ajax = 0;
  $quicktabs->hide_empty_tabs = FALSE;
  $quicktabs->default_tab = 0;
  $quicktabs->title = 'Calls quicktab';
  $quicktabs->tabs = array(
    0 => array(
      'bid' => 'views_delta_calls-block_open_calls',
      'hide_title' => 1,
      'title' => 'Open calls',
      'weight' => '0',
      'type' => 'block',
    ),
    1 => array(
      'bid' => 'views_delta_calls-block_ongoing_calls',
      'hide_title' => 1,
      'title' => 'Ongoing calls',
      'weight' => '1',
      'type' => 'block',
    ),
    2 => array(
      'bid' => 'views_delta_calls-block_archived_calls',
      'hide_title' => 1,
      'title' => 'Archived calls',
      'weight' => '2',
      'type' => 'block',
    ),
  );
  $quicktabs->renderer = 'accordion';
  $quicktabs->style = 'nostyle';
  $quicktabs->options = array(
    'history' => 0,
    'jquery_ui' => array(
      'autoHeight' => 1,
      'collapsible' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Archived calls');
  t('Calls quicktab');
  t('Ongoing calls');
  t('Open calls');

  $export['calls_quicktab'] = $quicktabs;

  return $export;
}
