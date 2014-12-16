<?php
/**
 * @file
 * osha_newsletter.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function osha_newsletter_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_newsletter_article';
  $strongarm->value = 0;
  $export['comment_anonymous_newsletter_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_newsletter_article';
  $strongarm->value = 1;
  $export['comment_default_mode_newsletter_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_newsletter_article';
  $strongarm->value = '50';
  $export['comment_default_per_page_newsletter_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_newsletter_article';
  $strongarm->value = 1;
  $export['comment_form_location_newsletter_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_newsletter_article';
  $strongarm->value = '1';
  $export['comment_newsletter_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_newsletter_article';
  $strongarm->value = '1';
  $export['comment_preview_newsletter_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_newsletter_article';
  $strongarm->value = 1;
  $export['comment_subject_field_newsletter_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'entity_translation_comment_filter_newsletter_article';
  $strongarm->value = 0;
  $export['entity_translation_comment_filter_newsletter_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'entity_translation_hide_translation_links_newsletter_article';
  $strongarm->value = 0;
  $export['entity_translation_hide_translation_links_newsletter_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'entity_translation_node_metadata_newsletter_article';
  $strongarm->value = '0';
  $export['entity_translation_node_metadata_newsletter_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_entity_collection__newsletter_content_collection';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_entity_collection__newsletter_content_collection'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__newsletter_article';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__newsletter_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_taxonomy_term__newsletter_sections';
  $strongarm->value = array(
    'view_modes' => array(
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => TRUE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'metatags' => array(
          'weight' => '5',
        ),
        'path' => array(
          'weight' => '4',
        ),
        'redirect' => array(
          'weight' => '3',
        ),
      ),
      'display' => array(
        'description' => array(
          'default' => array(
            'weight' => '0',
            'visible' => TRUE,
          ),
          'full' => array(
            'weight' => '0',
            'visible' => TRUE,
          ),
          'token' => array(
            'weight' => '0',
            'visible' => TRUE,
          ),
        ),
      ),
    ),
  );
  $export['field_bundle_settings_taxonomy_term__newsletter_sections'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_newsletter_article';
  $strongarm->value = '0';
  $export['language_content_type_newsletter_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_newsletter_article';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_newsletter_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_newsletter_article';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_newsletter_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_newsletter_article';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_newsletter_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_newsletter_article';
  $strongarm->value = '0';
  $export['node_preview_newsletter_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_newsletter_article';
  $strongarm->value = 0;
  $export['node_submitted_newsletter_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'osha_newsletter_after_max_nodes';
  $strongarm->value = '30';
  $export['osha_newsletter_after_max_nodes'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'osha_newsletter_allowed_bundles';
  $strongarm->value = array(
    'article' => 'article',
    'blog' => 'blog',
    'highlight' => 'highlight',
    'news' => 'news',
    'newsletter_article' => 'newsletter_article',
    'press_release' => 'press_release',
    'publication' => 'publication',
    'page' => 0,
    'calls' => 0,
    'job_vacancies' => 0,
    'wiki_page' => 0,
  );
  $export['osha_newsletter_allowed_bundles'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'osha_newsletter_coming_soon_tid';
  $strongarm->value = '4';
  $export['osha_newsletter_coming_soon_tid'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'osha_newsletter_listserv';
  $strongarm->value = 'listserv@list.osha.europa.eu';
  $export['osha_newsletter_listserv'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'osha_newsletter_listserv_from';
  $strongarm->value = 'oshmail@osha.europa.eu';
  $export['osha_newsletter_listserv_from'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'osha_newsletter_list_name';
  $strongarm->value = 'OSHMail-Test';
  $export['osha_newsletter_list_name'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'osha_newsletter_node_view_mode';
  $strongarm->value = 'newsletter_item';
  $export['osha_newsletter_node_view_mode'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'osha_newsletter_term_ct_map';
  $strongarm->value = array(
    'article' => 'c6feccca-fa35-4655-b048-39849aef6ab2',
    'view_mode_article' => 'newsletter_item',
    'page' => '',
    'view_mode_page' => 'newsletter_item',
    'blog' => '798b75d1-a135-495f-805d-fb3293be88c3',
    'view_mode_blog' => 'newsletter_item',
    'calls' => '',
    'view_mode_calls' => 'newsletter_item',
    'highlight' => '4edd574b-8dbd-4af8-b82c-6e85eeb5be99',
    'view_mode_highlight' => 'highlights_item',
    'job_vacancies' => '',
    'view_mode_job_vacancies' => 'newsletter_item',
    'news' => '04648f6e-d60f-4ce7-b800-e7842ad4f320',
    'view_mode_news' => 'newsletter_item',
    'newsletter_article' => '6255c5ce-9b1f-4be1-85f2-79199e789e3f',
    'view_mode_newsletter_article' => 'newsletter_item',
    'press_release' => '',
    'view_mode_press_release' => 'newsletter_item',
    'publication' => 'ad8da6ba-1101-4181-bba2-1b7094cabab3',
    'view_mode_publication' => 'newsletter_item',
    'wiki_page' => '',
    'view_mode_wiki_page' => 'newsletter_item',
  );
  $export['osha_newsletter_term_ct_map'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'subscribe_block_details_link_label';
  $strongarm->value = 'Privacy policy';
  $export['subscribe_block_details_link_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'subscribe_block_details_link_url';
  $strongarm->value = 'articles/privacy-statement-oshmail';
  $export['subscribe_block_details_link_url'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'subscribe_block_intro_text';
  $strongarm->value = 'Once our monthly update on safety and health at work. <a href="@newsletter_page_url">See more info</a><br/><p style="color : #dc2f82;">Join 65.000 subscribers!</p>';
  $export['subscribe_block_intro_text'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'subscribe_block_newsletter_page_url';
  $strongarm->value = 'pages/oshmail-newsletter';
  $export['subscribe_block_newsletter_page_url'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'subscribe_extra_block_details_link_label';
  $strongarm->value = 'How will EU-OSHA use my details?';
  $export['subscribe_extra_block_details_link_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'subscribe_extra_block_details_link_url';
  $strongarm->value = 'articles/privacy-statement-oshmail';
  $export['subscribe_extra_block_details_link_url'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'subscribe_extra_block_intro_text';
  $strongarm->value = 'Once a month, OSHmail keeps you updated on ocupational safety and health.<br/> You can sign up below:';
  $export['subscribe_extra_block_intro_text'] = $strongarm;

  return $export;
}
