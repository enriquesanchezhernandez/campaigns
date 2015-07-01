<?php
/**
 * @file
 * hwc_partner.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function hwc_partner_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'partner_public_profile';
  $page->task = 'page';
  $page->admin_title = 'Partner profile';
  $page->admin_description = '';
  $page->path = 'partner-profile/%node';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array(
    'node' => array(
      'id' => 1,
      'identifier' => 'Node: ID',
      'name' => 'entity_id:node',
      'settings' => array(),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_partner_public_profile__panel_context_9784121b-bc57-4d0b-915c-c11d738c0639';
  $handler->task = 'page';
  $handler->subtask = 'partner_public_profile';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Visitor',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'partner' => 'partner',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'flexible';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '536f07b4-59cc-4e7d-84b4-3635ebb5aa94';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-21193c9b-bdf0-46b9-8120-f1d3781f045d';
    $pane->panel = 'center';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:title_field';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'title_linked',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'title_style' => '_none',
        'title_link' => '',
        'title_class' => '',
      ),
      'context' => 'context_entity:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '21193c9b-bdf0-46b9-8120-f1d3781f045d';
    $display->content['new-21193c9b-bdf0-46b9-8120-f1d3781f045d'] = $pane;
    $display->panels['center'][0] = 'new-21193c9b-bdf0-46b9-8120-f1d3781f045d';
    $pane = new stdClass();
    $pane->pid = 'new-2f8ed0d0-aabd-40cc-8d5f-2dcd30d81957';
    $pane->panel = 'center';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_orgtype';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'title_linked',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'title_style' => '_none',
        'title_link' => '',
        'title_class' => '',
      ),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '2f8ed0d0-aabd-40cc-8d5f-2dcd30d81957';
    $display->content['new-2f8ed0d0-aabd-40cc-8d5f-2dcd30d81957'] = $pane;
    $display->panels['center'][1] = 'new-2f8ed0d0-aabd-40cc-8d5f-2dcd30d81957';
    $pane = new stdClass();
    $pane->pid = 'new-91027b2b-a9f8-4c30-84cf-608524bd44cd';
    $pane->panel = 'center';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_bussines_sector';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'title_linked',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'title_style' => '_none',
        'title_link' => '',
        'title_class' => '',
      ),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '91027b2b-a9f8-4c30-84cf-608524bd44cd';
    $display->content['new-91027b2b-a9f8-4c30-84cf-608524bd44cd'] = $pane;
    $display->panels['center'][2] = 'new-91027b2b-a9f8-4c30-84cf-608524bd44cd';
    $pane = new stdClass();
    $pane->pid = 'new-2c5384eb-8241-4cbf-a6b5-aeb3a1a40523';
    $pane->panel = 'center';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_website';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'link_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '2c5384eb-8241-4cbf-a6b5-aeb3a1a40523';
    $display->content['new-2c5384eb-8241-4cbf-a6b5-aeb3a1a40523'] = $pane;
    $display->panels['center'][3] = 'new-2c5384eb-8241-4cbf-a6b5-aeb3a1a40523';
    $pane = new stdClass();
    $pane->pid = 'new-644faa7b-274b-41e6-b1d0-f7df567e91b6';
    $pane->panel = 'center';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_ceo_photo';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'image',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'image_style' => 'medium',
        'image_link' => '',
      ),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = '644faa7b-274b-41e6-b1d0-f7df567e91b6';
    $display->content['new-644faa7b-274b-41e6-b1d0-f7df567e91b6'] = $pane;
    $display->panels['center'][4] = 'new-644faa7b-274b-41e6-b1d0-f7df567e91b6';
    $pane = new stdClass();
    $pane->pid = 'new-1ffdd101-4abb-456f-a821-37d48bea82a3';
    $pane->panel = 'center';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_ceo';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'title_linked',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'title_style' => '_none',
        'title_link' => '',
        'title_class' => '',
      ),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 5;
    $pane->locks = array();
    $pane->uuid = '1ffdd101-4abb-456f-a821-37d48bea82a3';
    $display->content['new-1ffdd101-4abb-456f-a821-37d48bea82a3'] = $pane;
    $display->panels['center'][5] = 'new-1ffdd101-4abb-456f-a821-37d48bea82a3';
    $pane = new stdClass();
    $pane->pid = 'new-77cc5bf8-5bbc-40ce-8d91-e31ff9f96577';
    $pane->panel = 'center';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_mission_statement';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'above',
      'formatter' => 'text_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 6;
    $pane->locks = array();
    $pane->uuid = '77cc5bf8-5bbc-40ce-8d91-e31ff9f96577';
    $display->content['new-77cc5bf8-5bbc-40ce-8d91-e31ff9f96577'] = $pane;
    $display->panels['center'][6] = 'new-77cc5bf8-5bbc-40ce-8d91-e31ff9f96577';
    $pane = new stdClass();
    $pane->pid = 'new-cb32a0f3-6862-4976-bc53-e63d63d63c4d';
    $pane->panel = 'center';
    $pane->type = 'views';
    $pane->subtype = 'news';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '4',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'oshnews_latest',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 7;
    $pane->locks = array();
    $pane->uuid = 'cb32a0f3-6862-4976-bc53-e63d63d63c4d';
    $display->content['new-cb32a0f3-6862-4976-bc53-e63d63d63c4d'] = $pane;
    $display->panels['center'][7] = 'new-cb32a0f3-6862-4976-bc53-e63d63d63c4d';
    $pane = new stdClass();
    $pane->pid = 'new-0b4279c4-f4de-431f-9738-30d53b5790f0';
    $pane->panel = 'center';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_logo';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'image',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'image_style' => 'medium',
        'image_link' => '',
      ),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 8;
    $pane->locks = array();
    $pane->uuid = '0b4279c4-f4de-431f-9738-30d53b5790f0';
    $display->content['new-0b4279c4-f4de-431f-9738-30d53b5790f0'] = $pane;
    $display->panels['center'][8] = 'new-0b4279c4-f4de-431f-9738-30d53b5790f0';
    $pane = new stdClass();
    $pane->pid = 'new-38975c5b-29c7-472e-b1eb-49c0ed4b9309';
    $pane->panel = 'center';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:title_field';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'title_linked',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'title_style' => '_none',
        'title_link' => '',
        'title_class' => '',
      ),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 9;
    $pane->locks = array();
    $pane->uuid = '38975c5b-29c7-472e-b1eb-49c0ed4b9309';
    $display->content['new-38975c5b-29c7-472e-b1eb-49c0ed4b9309'] = $pane;
    $display->panels['center'][9] = 'new-38975c5b-29c7-472e-b1eb-49c0ed4b9309';
    $pane = new stdClass();
    $pane->pid = 'new-d05c7360-62ae-4b57-a2fa-af756b871d17';
    $pane->panel = 'center';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_ph_address';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'title_linked',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'title_style' => '_none',
        'title_link' => '',
        'title_class' => '',
      ),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 10;
    $pane->locks = array();
    $pane->uuid = 'd05c7360-62ae-4b57-a2fa-af756b871d17';
    $display->content['new-d05c7360-62ae-4b57-a2fa-af756b871d17'] = $pane;
    $display->panels['center'][10] = 'new-d05c7360-62ae-4b57-a2fa-af756b871d17';
    $pane = new stdClass();
    $pane->pid = 'new-e36dcb73-9189-40e8-acaa-bdd2574c9377';
    $pane->panel = 'center';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_ph_cp';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'title_linked',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'title_style' => '_none',
        'title_link' => '',
        'title_class' => '',
      ),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 11;
    $pane->locks = array();
    $pane->uuid = 'e36dcb73-9189-40e8-acaa-bdd2574c9377';
    $display->content['new-e36dcb73-9189-40e8-acaa-bdd2574c9377'] = $pane;
    $display->panels['center'][11] = 'new-e36dcb73-9189-40e8-acaa-bdd2574c9377';
    $pane = new stdClass();
    $pane->pid = 'new-0c8ecff9-b7cd-4097-9147-ed11f1bf5f19';
    $pane->panel = 'center';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_country_code';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'i18n_list_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 12;
    $pane->locks = array();
    $pane->uuid = '0c8ecff9-b7cd-4097-9147-ed11f1bf5f19';
    $display->content['new-0c8ecff9-b7cd-4097-9147-ed11f1bf5f19'] = $pane;
    $display->panels['center'][12] = 'new-0c8ecff9-b7cd-4097-9147-ed11f1bf5f19';
    $pane = new stdClass();
    $pane->pid = 'new-375bdc33-e7fe-43ca-9957-64127c7264fb';
    $pane->panel = 'center';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_ph_address_extra';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'title_linked',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'title_style' => '_none',
        'title_link' => '',
        'title_class' => '',
      ),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 13;
    $pane->locks = array();
    $pane->uuid = '375bdc33-e7fe-43ca-9957-64127c7264fb';
    $display->content['new-375bdc33-e7fe-43ca-9957-64127c7264fb'] = $pane;
    $display->panels['center'][13] = 'new-375bdc33-e7fe-43ca-9957-64127c7264fb';
    $pane = new stdClass();
    $pane->pid = 'new-b4c58a13-6a77-4758-a4e7-522b788832e0';
    $pane->panel = 'center';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_general_email';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'email_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 14;
    $pane->locks = array();
    $pane->uuid = 'b4c58a13-6a77-4758-a4e7-522b788832e0';
    $display->content['new-b4c58a13-6a77-4758-a4e7-522b788832e0'] = $pane;
    $display->panels['center'][14] = 'new-b4c58a13-6a77-4758-a4e7-522b788832e0';
    $pane = new stdClass();
    $pane->pid = 'new-eb585847-4795-4b6d-9822-25da45177327';
    $pane->panel = 'center';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_website';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'link_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 15;
    $pane->locks = array();
    $pane->uuid = 'eb585847-4795-4b6d-9822-25da45177327';
    $display->content['new-eb585847-4795-4b6d-9822-25da45177327'] = $pane;
    $display->panels['center'][15] = 'new-eb585847-4795-4b6d-9822-25da45177327';
    $pane = new stdClass();
    $pane->pid = 'new-55e46dc6-cbe6-47b9-9228-2dbb98c6c582';
    $pane->panel = 'center';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_general_phone';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'title_linked',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'title_style' => '_none',
        'title_link' => '',
        'title_class' => '',
      ),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 16;
    $pane->locks = array();
    $pane->uuid = '55e46dc6-cbe6-47b9-9228-2dbb98c6c582';
    $display->content['new-55e46dc6-cbe6-47b9-9228-2dbb98c6c582'] = $pane;
    $display->panels['center'][16] = 'new-55e46dc6-cbe6-47b9-9228-2dbb98c6c582';
    $pane = new stdClass();
    $pane->pid = 'new-249112dd-020c-473e-87b5-653d3edd5346';
    $pane->panel = 'center';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_main_contact';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'above',
      'formatter' => 'title_linked',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'title_style' => '_none',
        'title_link' => '',
        'title_class' => '',
      ),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 17;
    $pane->locks = array();
    $pane->uuid = '249112dd-020c-473e-87b5-653d3edd5346';
    $display->content['new-249112dd-020c-473e-87b5-653d3edd5346'] = $pane;
    $display->panels['center'][17] = 'new-249112dd-020c-473e-87b5-653d3edd5346';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['partner_public_profile'] = $page;

  return $pages;

}
