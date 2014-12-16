<?php
/**
 * @file
 * osha_newsletter.features.fe_block_boxes.inc
 */

/**
 * Implements hook_default_fe_block_boxes().
 */
function osha_newsletter_default_fe_block_boxes() {
  $export = array();

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Join OSHMail subscribers';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'join_oshmail_subscribers';
  $fe_block_boxes->body = '<div id="join_subscribers"><img src="/sites/all/themes/osha_frontend/images/content/blocks/join_65000_subscribers.png" alt="Join OSHMail Subscribers" /></div>';

  $export['join_oshmail_subscribers'] = $fe_block_boxes;

  return $export;
}
