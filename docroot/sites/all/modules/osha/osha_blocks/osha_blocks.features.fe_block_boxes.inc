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
  $fe_block_boxes->info = 'Job Vacancies Reserve List';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'osha_job_vacancies_reserve_block';
  $fe_block_boxes->body = '<p class="Textfo" style="text-align: justify;">Reserve lists are composed of the candidates who came for an interview at the time of the recruitment procedure for the posts listed and who obtained the best overall marks.</p><p class="Textfo" style="text-align: justify;">Candidates in the reserve list may be offered contracts at a later date without subsequent selection procedure.</p><p class="Textfo" style="text-align: justify;">For some Contract Agent positions, EU-OSHA may use the EPSO database.</p>';

  $export['osha_job_vacancies_reserve_block'] = $fe_block_boxes;

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Subscribe categories - static block';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'oshmail_subscribe_categories';
  $fe_block_boxes->body = '<div><ul><li>Latest <strong>news</strong> from <br>around the world</li><li>Forthcoming <br><strong>events</strong></li><li>Latest Agency <br><strong>publications</strong></li><li>Updates on EU <br><strong>legislation</strong></li><li>In 24 <br><strong>languages</strong></li><li><strong>Free</strong><br> subscriptions</li></ul></div>';

  $export['oshmail_subscribe_categories'] = $fe_block_boxes;

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Header for Publications page';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'publications_header';
  $fe_block_boxes->body = '<p>Our publications range from in-depth research reports to topical e-facts, designed for use in the workplace. All are free to download. You can search the library by publication type or keyword. You might also like to subscribe to our free monthly newsletter — it makes keeping up to date with OSH easy.</p>';

  $export['publications_header'] = $fe_block_boxes;

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Link on seminar content type to reference seminars page';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'seminar_back_to_seminars_link';
  $fe_block_boxes->body = '<div><a class="seminar_back-to-seminars back-to-link" href="/articles/seminars">Back to seminars</a></div>';

  $export['seminar_back_to_seminars_link'] = $fe_block_boxes;

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Link on careers page to closed vacancies';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'vacancies_link_to_closed';
  $fe_block_boxes->body = '<p><a href="/jobs_archive">Closed vacancies</a></p>';

  $export['vacancies_link_to_closed'] = $fe_block_boxes;

  return $export;
}
