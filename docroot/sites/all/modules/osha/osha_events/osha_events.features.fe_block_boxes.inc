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
  $fe_block_boxes->info = 'Block for events';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'event_block_header';
  $fe_block_boxes->body = '<div class="event_header_block"><div class="events_summary"><p class="summary">Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</p></div><div class="image_events">[[{"fid":"32949","view_mode":"default","fields":{"format":"default","field_file_image_alt_text[und][0][value]":"","field_file_image_title_text[und][0][value]":"","field_file_description[und][0][value]":"","field_nace_codes[und][0][tid]":"_none","field_nace_codes[und][0][_weight]":"0","field_thesaurus[und][0][tid]":"_none","field_thesaurus[und][0][_weight]":"0","field_language[und]":"en"},"type":"media","attributes":{"class":"media-element file-default"}}]]</div></div>';

  $export['event_block_header'] = $fe_block_boxes;

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Link on events content type to reference events page';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'events_back_to_events_link';
  $fe_block_boxes->body = '<p><a href="/events">Back to events</a></p>';

  $export['events_back_to_events_link'] = $fe_block_boxes;

  return $export;
}
