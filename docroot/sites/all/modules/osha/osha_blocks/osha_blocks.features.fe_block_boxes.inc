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
  $fe_block_boxes->info = 'OSHWiki static block - link to OSHwiki';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'osha_wiki_link';
  $fe_block_boxes->body = '<div class="OSHWiki"><div class="separatorOsHWiki">&nbsp;</div><div id="OSHWikiDivTit"><div class="imgOSHWiki"><img src="/sites/all/themes/osha_frontend/images/OSHwiki.png" alt="" width="26" height="26"></div><div class="OSHWikiTitle">OSHwiki</div></div><div class="p2">Find OSHwiki articles<span><br></span></div><div class="p3"><a href="http://oshwiki.eu/wiki/Main_Page" target="_blank">Go to OSHwiki <img src="/sites/all/themes/osha_frontend/images/flecha.png" alt="Go to OSHwiki" width="19" height="11"></a></div></div>';

  $export['osha_wiki_link'] = $fe_block_boxes;

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
  $fe_block_boxes->body = '<div><a class="seminar_back-to-seminars back-to-link" href="/tools-and-publications/seminars">Back to seminars</a></div>';

  $export['seminar_back_to_seminars_link'] = $fe_block_boxes;

  return $export;
}
