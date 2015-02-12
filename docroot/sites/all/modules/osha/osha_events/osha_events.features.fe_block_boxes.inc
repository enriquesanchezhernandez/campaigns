<?php
/**
 * @file
 * osha_events.features.fe_block_boxes.inc
 */

/**
 * Implements hook_default_fe_block_boxes().
 */
function osha_events_default_fe_block_boxes() {
  $export = array();

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Link on events content type to reference events page';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'events_back_to_events_link';
  $fe_block_boxes->body = '<p><a href="/tools-and-publications/oshevents">Back to events</a></p>';

  $export['events_back_to_events_link'] = $fe_block_boxes;

  return $export;
}
