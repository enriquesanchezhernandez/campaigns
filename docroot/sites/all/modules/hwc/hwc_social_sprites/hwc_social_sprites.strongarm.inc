<?php
/**
 * @file
 * hwc_social_sprites.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function hwc_social_sprites_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_block_3_admin_title';
  $strongarm->value = 'Footer links';
  $export['menu_block_3_admin_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_block_3_depth';
  $strongarm->value = '1';
  $export['menu_block_3_depth'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_block_3_expanded';
  $strongarm->value = 0;
  $export['menu_block_3_expanded'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_block_3_follow';
  $strongarm->value = 0;
  $export['menu_block_3_follow'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_block_3_level';
  $strongarm->value = '1';
  $export['menu_block_3_level'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_block_3_parent';
  $strongarm->value = 'menu-footer-menu:2151';
  $export['menu_block_3_parent'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_block_3_render_menu_image';
  $strongarm->value = 0;
  $export['menu_block_3_render_menu_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_block_3_sort';
  $strongarm->value = 0;
  $export['menu_block_3_sort'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_block_3_title_link';
  $strongarm->value = 0;
  $export['menu_block_3_title_link'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_block_4_admin_title';
  $strongarm->value = 'Footer social menu block';
  $export['menu_block_4_admin_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_block_4_depth';
  $strongarm->value = '1';
  $export['menu_block_4_depth'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_block_4_expanded';
  $strongarm->value = 0;
  $export['menu_block_4_expanded'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_block_4_follow';
  $strongarm->value = 0;
  $export['menu_block_4_follow'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_block_4_level';
  $strongarm->value = '1';
  $export['menu_block_4_level'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_block_4_parent';
  $strongarm->value = 'menu-footer-menu:2150';
  $export['menu_block_4_parent'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_block_4_render_menu_image';
  $strongarm->value = 1;
  $export['menu_block_4_render_menu_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_block_4_sort';
  $strongarm->value = 0;
  $export['menu_block_4_sort'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_block_4_title_link';
  $strongarm->value = 0;
  $export['menu_block_4_title_link'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'on_the_web_delicious_page';
  $strongarm->value = '';
  $export['on_the_web_delicious_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'on_the_web_facebook_page';
  $strongarm->value = 'https://www.facebook.com/EuropeanAgencyforSafetyandHealthatWork';
  $export['on_the_web_facebook_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'on_the_web_flickr_page';
  $strongarm->value = '';
  $export['on_the_web_flickr_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'on_the_web_friendfeed_page';
  $strongarm->value = '';
  $export['on_the_web_friendfeed_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'on_the_web_google_page';
  $strongarm->value = '';
  $export['on_the_web_google_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'on_the_web_itunes_page';
  $strongarm->value = '';
  $export['on_the_web_itunes_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'on_the_web_linkedin_page';
  $strongarm->value = 'https://www.linkedin.com/company/european-agency-for-safety-and-health-at-work';
  $export['on_the_web_linkedin_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'on_the_web_myspace_page';
  $strongarm->value = '';
  $export['on_the_web_myspace_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'on_the_web_pinterest_page';
  $strongarm->value = '';
  $export['on_the_web_pinterest_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'on_the_web_rss_page';
  $strongarm->value = '';
  $export['on_the_web_rss_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'on_the_web_sitename';
  $strongarm->value = 1;
  $export['on_the_web_sitename'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'on_the_web_size';
  $strongarm->value = 'sm';
  $export['on_the_web_size'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'on_the_web_target';
  $strongarm->value = 1;
  $export['on_the_web_target'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'on_the_web_twitter_page';
  $strongarm->value = 'https://twitter.com/eu_osha';
  $export['on_the_web_twitter_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'on_the_web_youtube_page';
  $strongarm->value = 'https://www.youtube.com/user/EUOSHA';
  $export['on_the_web_youtube_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'text_resize_line_height_allow';
  $strongarm->value = 0;
  $export['text_resize_line_height_allow'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'text_resize_line_height_max';
  $strongarm->value = '36';
  $export['text_resize_line_height_max'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'text_resize_line_height_min';
  $strongarm->value = '16';
  $export['text_resize_line_height_min'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'text_resize_maximum';
  $strongarm->value = '25';
  $export['text_resize_maximum'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'text_resize_minimum';
  $strongarm->value = '12';
  $export['text_resize_minimum'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'text_resize_reset_button';
  $strongarm->value = 0;
  $export['text_resize_reset_button'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'text_resize_scope';
  $strongarm->value = 'main-container';
  $export['text_resize_scope'] = $strongarm;

  return $export;
}
