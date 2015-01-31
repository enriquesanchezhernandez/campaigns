<?php
/**
 * @file
 * osha_blocks.features.fe_block_boxes.inc
 */

/**
 * Implements hook_default_fe_block_boxes().
 */
function osha_blocks_default_fe_block_boxes() {
  $export = array();

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Link on seminar content type to reference seminars page';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'seminar_back_to_seminars_link';
  $fe_block_boxes->body = '<div><a class="seminar_back-to-seminars back-to-link" href="/tools-and-publications/seminars">Back to seminars</a></div>';

  $export['seminar_back_to_seminars_link'] = $fe_block_boxes;

  return $export;
}
