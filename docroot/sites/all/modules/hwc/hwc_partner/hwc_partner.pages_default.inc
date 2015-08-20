<?php
/**
 * @file
 * hwc_partner.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function hwc_partner_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__panel_context_d109f4e3-27a8-4bfa-922c-690f8fc7a2eb';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 1;
  $handler->conf = array(
    'title' => 'Partner profile',
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
  $display->layout_settings = array(
    'items' => array(
      'canvas' => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 'main',
        ),
        'parent' => NULL,
      ),
      'main' => array(
        'type' => 'column',
        'width' => 100,
        'width_type' => '%',
        'children' => array(
          0 => 6,
          1 => 5,
          2 => 4,
          3 => 'main-row',
          4 => 1,
          5 => 2,
          6 => 3,
        ),
        'parent' => 'canvas',
      ),
      'main-row' => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'center',
        ),
        'parent' => 'main',
        'class' => 'profile-ceo-container',
        'hide_empty' => 0,
      ),
      'center' => array(
        'type' => 'region',
        'title' => 'Center',
        'width' => 100,
        'width_type' => '%',
        'parent' => 'main-row',
        'class' => 'container',
        'hide_empty' => 0,
      ),
      1 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'left',
          1 => 'right',
        ),
        'parent' => 'main',
        'class' => 'container profile-2-cols-container-1',
        'hide_empty' => 0,
      ),
      'left' => array(
        'type' => 'region',
        'title' => 'Left',
        'width' => 50,
        'width_type' => '%',
        'parent' => '1',
        'class' => 'col-sm-6 profile-col-left-1',
        'hide_empty' => 0,
      ),
      'right' => array(
        'type' => 'region',
        'title' => 'Right',
        'width' => 50,
        'width_type' => '%',
        'parent' => '1',
        'class' => 'col-sm-6 profile-col-right-1',
        'hide_empty' => 0,
      ),
      2 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'left___',
          1 => 'left_',
          2 => 'right_',
          3 => 'right___',
        ),
        'parent' => 'main',
        'class' => 'container profile-4-cols-container-2',
        'hide_empty' => 0,
      ),
      'left_' => array(
        'type' => 'region',
        'title' => 'Middle Left',
        'width' => 25,
        'width_type' => '%',
        'parent' => '2',
        'class' => 'col-sm-3 profile-col-left-middle-2',
        'hide_empty' => 0,
      ),
      'right_' => array(
        'type' => 'region',
        'title' => 'Middle Right',
        'width' => 25,
        'width_type' => '%',
        'parent' => '2',
        'class' => 'col-sm-3 profile-col-middle-right-2',
        'hide_empty' => 0,
      ),
      3 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'left__',
          1 => 'right__',
        ),
        'parent' => 'main',
        'class' => 'container profile-2-cols-container-3',
        'hide_empty' => 0,
      ),
      'left__' => array(
        'type' => 'region',
        'title' => 'Left',
        'width' => '25.091027461588755',
        'width_type' => '%',
        'parent' => '3',
        'class' => 'col-sm-6 profile-col-left-3',
        'hide_empty' => 0,
      ),
      'right__' => array(
        'type' => 'region',
        'title' => 'Right',
        'width' => '24.908972538411245',
        'width_type' => '%',
        'parent' => '3',
        'class' => 'col-sm-6 profile-col-right-3',
        'hide_empty' => 0,
      ),
      4 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'center_',
        ),
        'parent' => 'main',
        'class' => 'container profile-title-type-container',
        'hide_empty' => 0,
      ),
      'center_' => array(
        'type' => 'region',
        'title' => 'Center',
        'width' => 100,
        'width_type' => '%',
        'parent' => '4',
        'class' => 'col-md-12',
        'hide_empty' => 0,
      ),
      5 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'center__',
        ),
        'parent' => 'main',
        'class' => '',
        'hide_empty' => 0,
      ),
      'center__' => array(
        'type' => 'region',
        'title' => 'Center',
        'width' => 100,
        'width_type' => '%',
        'parent' => '5',
        'class' => '',
        'hide_empty' => 0,
      ),
      'left___' => array(
        'type' => 'region',
        'title' => 'Left',
        'width' => 25,
        'width_type' => '%',
        'parent' => '2',
        'class' => 'col-sm-3 profile-col-left-2',
        'hide_empty' => 0,
      ),
      'right___' => array(
        'type' => 'region',
        'title' => 'Right',
        'width' => 25,
        'width_type' => '%',
        'parent' => '2',
        'class' => 'col-sm-3 profile-col-right-2',
        'hide_empty' => 0,
      ),
      6 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'my_title',
        ),
        'parent' => 'main',
        'class' => 'profile-edit-links-container',
        'hide_empty' => 0,
      ),
      'my_title' => array(
        'type' => 'region',
        'title' => 'Center',
        'width' => 100,
        'width_type' => '%',
        'parent' => '6',
        'class' => '',
        'hide_empty' => 0,
      ),
    ),
  );
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
      'left' => NULL,
      'right' => NULL,
      'left_' => NULL,
      'right_' => NULL,
      'left__' => NULL,
      'right__' => NULL,
      'center_' => NULL,
      'center__' => NULL,
      'left___' => NULL,
      'right___' => NULL,
      'my_title' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '536f07b4-59cc-4e7d-84b4-3635ebb5aa94';
  $display->content = array();
  $display->panels = array();
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
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '644faa7b-274b-41e6-b1d0-f7df567e91b6';
    $display->content['new-644faa7b-274b-41e6-b1d0-f7df567e91b6'] = $pane;
    $display->panels['center'][0] = 'new-644faa7b-274b-41e6-b1d0-f7df567e91b6';
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '1ffdd101-4abb-456f-a821-37d48bea82a3';
    $display->content['new-1ffdd101-4abb-456f-a821-37d48bea82a3'] = $pane;
    $display->panels['center'][1] = 'new-1ffdd101-4abb-456f-a821-37d48bea82a3';
    $pane = new stdClass();
    $pane->pid = 'new-9dca80f0-8993-49f6-aa29-a8c69d918778';
    $pane->panel = 'center';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_quote';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
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
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '9dca80f0-8993-49f6-aa29-a8c69d918778';
    $display->content['new-9dca80f0-8993-49f6-aa29-a8c69d918778'] = $pane;
    $display->panels['center'][2] = 'new-9dca80f0-8993-49f6-aa29-a8c69d918778';
    $pane = new stdClass();
    $pane->pid = 'new-21193c9b-bdf0-46b9-8120-f1d3781f045d';
    $pane->panel = 'center_';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:title_field';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(),
    );
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'title_linked',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'title_style' => 'h1',
        'title_link' => '',
        'title_class' => '',
        'field_formatter_class' => '',
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
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '21193c9b-bdf0-46b9-8120-f1d3781f045d';
    $display->content['new-21193c9b-bdf0-46b9-8120-f1d3781f045d'] = $pane;
    $display->panels['center_'][0] = 'new-21193c9b-bdf0-46b9-8120-f1d3781f045d';
    $pane = new stdClass();
    $pane->pid = 'new-2f8ed0d0-aabd-40cc-8d5f-2dcd30d81957';
    $pane->panel = 'center_';
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
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'profile-inline-field',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '2f8ed0d0-aabd-40cc-8d5f-2dcd30d81957';
    $display->content['new-2f8ed0d0-aabd-40cc-8d5f-2dcd30d81957'] = $pane;
    $display->panels['center_'][1] = 'new-2f8ed0d0-aabd-40cc-8d5f-2dcd30d81957';
    $pane = new stdClass();
    $pane->pid = 'new-91027b2b-a9f8-4c30-84cf-608524bd44cd';
    $pane->panel = 'center_';
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
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'profile-inline-field',
    );
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '91027b2b-a9f8-4c30-84cf-608524bd44cd';
    $display->content['new-91027b2b-a9f8-4c30-84cf-608524bd44cd'] = $pane;
    $display->panels['center_'][2] = 'new-91027b2b-a9f8-4c30-84cf-608524bd44cd';
    $pane = new stdClass();
    $pane->pid = 'new-2c5384eb-8241-4cbf-a6b5-aeb3a1a40523';
    $pane->panel = 'center_';
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
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'profile-inline-field',
    );
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '2c5384eb-8241-4cbf-a6b5-aeb3a1a40523';
    $display->content['new-2c5384eb-8241-4cbf-a6b5-aeb3a1a40523'] = $pane;
    $display->panels['center_'][3] = 'new-2c5384eb-8241-4cbf-a6b5-aeb3a1a40523';
    $pane = new stdClass();
    $pane->pid = 'new-01df3ff6-7648-4eb2-a42a-6d35973b8301';
    $pane->panel = 'center__';
    $pane->type = 'block';
    $pane->subtype = 'hwc_partner-hwc_partner_profile_title';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'php',
          'settings' => array(
            'description' => 'Page belongs to partner',
            'php' => '$node=menu_get_object(); return hwc_partner_match_user_partner($node);',
          ),
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
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
    $pane->uuid = '01df3ff6-7648-4eb2-a42a-6d35973b8301';
    $display->content['new-01df3ff6-7648-4eb2-a42a-6d35973b8301'] = $pane;
    $display->panels['center__'][0] = 'new-01df3ff6-7648-4eb2-a42a-6d35973b8301';
    $pane = new stdClass();
    $pane->pid = 'new-77cc5bf8-5bbc-40ce-8d91-e31ff9f96577';
    $pane->panel = 'left';
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
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '77cc5bf8-5bbc-40ce-8d91-e31ff9f96577';
    $display->content['new-77cc5bf8-5bbc-40ce-8d91-e31ff9f96577'] = $pane;
    $display->panels['left'][0] = 'new-77cc5bf8-5bbc-40ce-8d91-e31ff9f96577';
    $pane = new stdClass();
    $pane->pid = 'new-ac9c93c6-d4fe-44bb-9888-a4551b9c5af2';
    $pane->panel = 'left_';
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
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'ac9c93c6-d4fe-44bb-9888-a4551b9c5af2';
    $display->content['new-ac9c93c6-d4fe-44bb-9888-a4551b9c5af2'] = $pane;
    $display->panels['left_'][0] = 'new-ac9c93c6-d4fe-44bb-9888-a4551b9c5af2';
    $pane = new stdClass();
    $pane->pid = 'new-d05c7360-62ae-4b57-a2fa-af756b871d17';
    $pane->panel = 'left_';
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'd05c7360-62ae-4b57-a2fa-af756b871d17';
    $display->content['new-d05c7360-62ae-4b57-a2fa-af756b871d17'] = $pane;
    $display->panels['left_'][1] = 'new-d05c7360-62ae-4b57-a2fa-af756b871d17';
    $pane = new stdClass();
    $pane->pid = 'new-375bdc33-e7fe-43ca-9957-64127c7264fb';
    $pane->panel = 'left_';
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
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '375bdc33-e7fe-43ca-9957-64127c7264fb';
    $display->content['new-375bdc33-e7fe-43ca-9957-64127c7264fb'] = $pane;
    $display->panels['left_'][2] = 'new-375bdc33-e7fe-43ca-9957-64127c7264fb';
    $pane = new stdClass();
    $pane->pid = 'new-e36dcb73-9189-40e8-acaa-bdd2574c9377';
    $pane->panel = 'left_';
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
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = 'e36dcb73-9189-40e8-acaa-bdd2574c9377';
    $display->content['new-e36dcb73-9189-40e8-acaa-bdd2574c9377'] = $pane;
    $display->panels['left_'][3] = 'new-e36dcb73-9189-40e8-acaa-bdd2574c9377';
    $pane = new stdClass();
    $pane->pid = 'new-0c8ecff9-b7cd-4097-9147-ed11f1bf5f19';
    $pane->panel = 'left_';
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
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = '0c8ecff9-b7cd-4097-9147-ed11f1bf5f19';
    $display->content['new-0c8ecff9-b7cd-4097-9147-ed11f1bf5f19'] = $pane;
    $display->panels['left_'][4] = 'new-0c8ecff9-b7cd-4097-9147-ed11f1bf5f19';
    $pane = new stdClass();
    $pane->pid = 'new-58094813-4281-4753-b1e0-5e58a26999fb';
    $pane->panel = 'left__';
    $pane->type = 'views';
    $pane->subtype = 'partner_content';
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
      'display' => 'latest_partner_news',
      'context' => array(
        0 => '',
      ),
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
    $pane->uuid = '58094813-4281-4753-b1e0-5e58a26999fb';
    $display->content['new-58094813-4281-4753-b1e0-5e58a26999fb'] = $pane;
    $display->panels['left__'][0] = 'new-58094813-4281-4753-b1e0-5e58a26999fb';
    $pane = new stdClass();
    $pane->pid = 'new-0b4279c4-f4de-431f-9738-30d53b5790f0';
    $pane->panel = 'left___';
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
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '0b4279c4-f4de-431f-9738-30d53b5790f0';
    $display->content['new-0b4279c4-f4de-431f-9738-30d53b5790f0'] = $pane;
    $display->panels['left___'][0] = 'new-0b4279c4-f4de-431f-9738-30d53b5790f0';
    $pane = new stdClass();
    $pane->pid = 'new-073236e5-2fb2-4d90-b25f-72c03c3545bc';
    $pane->panel = 'my_title';
    $pane->type = 'block';
    $pane->subtype = 'hwc_partner-hwc_partner_private_link_0';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(),
    );
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'span',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'col-sm-3',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '073236e5-2fb2-4d90-b25f-72c03c3545bc';
    $display->content['new-073236e5-2fb2-4d90-b25f-72c03c3545bc'] = $pane;
    $display->panels['my_title'][0] = 'new-073236e5-2fb2-4d90-b25f-72c03c3545bc';
    $pane = new stdClass();
    $pane->pid = 'new-5bbbdd62-a5ac-4873-88f9-e44dca3b7ff8';
    $pane->panel = 'my_title';
    $pane->type = 'block';
    $pane->subtype = 'hwc_partner-hwc_partner_private_link_1';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(),
    );
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'span',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'col-sm-3',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '5bbbdd62-a5ac-4873-88f9-e44dca3b7ff8';
    $display->content['new-5bbbdd62-a5ac-4873-88f9-e44dca3b7ff8'] = $pane;
    $display->panels['my_title'][1] = 'new-5bbbdd62-a5ac-4873-88f9-e44dca3b7ff8';
    $pane = new stdClass();
    $pane->pid = 'new-b441ca28-52c6-4cff-b30f-9c6d75feccf3';
    $pane->panel = 'my_title';
    $pane->type = 'block';
    $pane->subtype = 'hwc_partner-hwc_partner_private_link_2';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(),
    );
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'span',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'col-sm-3',
    );
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'b441ca28-52c6-4cff-b30f-9c6d75feccf3';
    $display->content['new-b441ca28-52c6-4cff-b30f-9c6d75feccf3'] = $pane;
    $display->panels['my_title'][2] = 'new-b441ca28-52c6-4cff-b30f-9c6d75feccf3';
    $pane = new stdClass();
    $pane->pid = 'new-d1910e7b-4e97-4602-b684-7bf4508801fc';
    $pane->panel = 'my_title';
    $pane->type = 'entity_field_extra';
    $pane->subtype = 'node:profile_update_link';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'view_mode' => 'full',
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'col-sm-3',
    );
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = 'd1910e7b-4e97-4602-b684-7bf4508801fc';
    $display->content['new-d1910e7b-4e97-4602-b684-7bf4508801fc'] = $pane;
    $display->panels['my_title'][3] = 'new-d1910e7b-4e97-4602-b684-7bf4508801fc';
    $pane = new stdClass();
    $pane->pid = 'new-b4c58a13-6a77-4758-a4e7-522b788832e0';
    $pane->panel = 'right_';
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
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'b4c58a13-6a77-4758-a4e7-522b788832e0';
    $display->content['new-b4c58a13-6a77-4758-a4e7-522b788832e0'] = $pane;
    $display->panels['right_'][0] = 'new-b4c58a13-6a77-4758-a4e7-522b788832e0';
    $pane = new stdClass();
    $pane->pid = 'new-eb585847-4795-4b6d-9822-25da45177327';
    $pane->panel = 'right_';
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'eb585847-4795-4b6d-9822-25da45177327';
    $display->content['new-eb585847-4795-4b6d-9822-25da45177327'] = $pane;
    $display->panels['right_'][1] = 'new-eb585847-4795-4b6d-9822-25da45177327';
    $pane = new stdClass();
    $pane->pid = 'new-55e46dc6-cbe6-47b9-9228-2dbb98c6c582';
    $pane->panel = 'right_';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_general_phone';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'inline',
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
    $pane->uuid = '55e46dc6-cbe6-47b9-9228-2dbb98c6c582';
    $display->content['new-55e46dc6-cbe6-47b9-9228-2dbb98c6c582'] = $pane;
    $display->panels['right_'][2] = 'new-55e46dc6-cbe6-47b9-9228-2dbb98c6c582';
    $pane = new stdClass();
    $pane->pid = 'new-249112dd-020c-473e-87b5-653d3edd5346';
    $pane->panel = 'right_';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_main_contact';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'inline',
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
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '249112dd-020c-473e-87b5-653d3edd5346';
    $display->content['new-249112dd-020c-473e-87b5-653d3edd5346'] = $pane;
    $display->panels['right_'][3] = 'new-249112dd-020c-473e-87b5-653d3edd5346';
    $pane = new stdClass();
    $pane->pid = 'new-22050c50-2a04-49d6-b147-ee7e3f0b7183';
    $pane->panel = 'right__';
    $pane->type = 'views';
    $pane->subtype = 'partner_content';
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
      'display' => 'latest_partner_events',
      'context' => array(
        0 => '',
      ),
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
    $pane->uuid = '22050c50-2a04-49d6-b147-ee7e3f0b7183';
    $display->content['new-22050c50-2a04-49d6-b147-ee7e3f0b7183'] = $pane;
    $display->panels['right__'][0] = 'new-22050c50-2a04-49d6-b147-ee7e3f0b7183';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['node_view__panel_context_d109f4e3-27a8-4bfa-922c-690f8fc7a2eb'] = $handler;

  return $export;
}

/**
 * Implements hook_default_page_manager_pages().
 */
function hwc_partner_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'official_campaign_partners';
  $page->task = 'page';
  $page->admin_title = 'Official campaign partners';
  $page->admin_description = '';
  $page->path = 'official-campaign-partners';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_official_campaign_partners__panel_context_63e3852f-e4af-4bad-b681-7f57793dc362';
  $handler->task = 'page';
  $handler->subtask = 'official_campaign_partners';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Official campaign partners',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
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
  $display->uuid = '95b72608-23a5-4cbb-9515-c9630ab46b6d';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-de95302f-4ecf-4b9a-a105-e3a74864b930';
    $pane->panel = 'center';
    $pane->type = 'node';
    $pane->subtype = 'node';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'nid' => '145',
      'links' => 0,
      'leave_node_title' => 0,
      'identifier' => '',
      'build_mode' => 'body',
      'link_node_title' => 0,
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h1',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'section-introduction',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'de95302f-4ecf-4b9a-a105-e3a74864b930';
    $display->content['new-de95302f-4ecf-4b9a-a105-e3a74864b930'] = $pane;
    $display->panels['center'][0] = 'new-de95302f-4ecf-4b9a-a105-e3a74864b930';
    $pane = new stdClass();
    $pane->pid = 'new-e74c6e69-67c7-41d8-8206-046d8e5dda78';
    $pane->panel = 'center';
    $pane->type = 'views';
    $pane->subtype = 'partners_list';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '0',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'block',
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => 'block-views-partners-list-block',
      'css_class' => '',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'e74c6e69-67c7-41d8-8206-046d8e5dda78';
    $display->content['new-e74c6e69-67c7-41d8-8206-046d8e5dda78'] = $pane;
    $display->panels['center'][1] = 'new-e74c6e69-67c7-41d8-8206-046d8e5dda78';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = 'new-de95302f-4ecf-4b9a-a105-e3a74864b930';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['official_campaign_partners'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'partner_private_area';
  $page->task = 'page';
  $page->admin_title = 'Partner private area';
  $page->admin_description = '';
  $page->path = 'partner-private-area';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_partner_private_area__panel_context_912ffcf8-bbee-4af1-ac2a-13bd4c8b9a39';
  $handler->task = 'page';
  $handler->subtask = 'partner_private_area';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
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
  $display->title = 'Private area for Partners';
  $display->uuid = '4b43886a-a2f0-48cd-be03-5def9eac6bc0';
  $display->content = array();
  $display->panels = array();
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['partner_private_area'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'partner_public_profile';
  $page->task = 'page';
  $page->admin_title = 'Partner profile';
  $page->admin_description = '';
  $page->path = 'partner-profile/%node';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
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
    'title' => 'Profile',
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
    $pane->pid = 'new-7cd8edd0-19f2-4250-84a6-6e113567d2d8';
    $pane->panel = 'center';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'role',
          'settings' => array(
            'rids' => array(
              0 => 2,
            ),
          ),
          'context' => 'logged-in-user',
          'not' => FALSE,
        ),
        1 => array(
          'name' => 'php',
          'settings' => array(
            'description' => 'Logged user in Partner users (not finished)',
            'php' => 'return TRUE;
foreach( $contexts[\'argument_entity_id:node_1\']->data->field_users[\'und\'] as $key => $value) { $array []= $value[\'target_id\']; } return in_array($contexts[\'logged-in-user\']->data->uid ,$array);
',
          ),
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
      'admin_title' => 'Private links',
      'title' => '',
      'body' => '<div class="row"><div class="col-xs-4 text-center"><a href="#">Create an event</a> <br> <span>Do you want to propose an event in the context of our current Healthy Workplaces Campaign? <a href="#">Click here</a></span></div><div class="col-xs-4 text-center"><a href="#">Create news</a> <br> <span>Do you want to share with us the latest news about our organisation in the context of our current Healthy Workplaces Campaign? <a href="#">Click here</a></span></div><div class="col-xs-4 text-center"><a href="partner-private-area">Private area</a> <br> <span>Find the latest files to help you engage in the Campaign.</span></div></div><div class="row"><div class="col-xs-12"><h2>Your public profile</h2><span class="pull-right"><a href="#">Update</a></span></div></div>',
      'format' => 'full_html',
      'substitute' => 0,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '7cd8edd0-19f2-4250-84a6-6e113567d2d8';
    $display->content['new-7cd8edd0-19f2-4250-84a6-6e113567d2d8'] = $pane;
    $display->panels['center'][0] = 'new-7cd8edd0-19f2-4250-84a6-6e113567d2d8';
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '21193c9b-bdf0-46b9-8120-f1d3781f045d';
    $display->content['new-21193c9b-bdf0-46b9-8120-f1d3781f045d'] = $pane;
    $display->panels['center'][1] = 'new-21193c9b-bdf0-46b9-8120-f1d3781f045d';
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
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '2f8ed0d0-aabd-40cc-8d5f-2dcd30d81957';
    $display->content['new-2f8ed0d0-aabd-40cc-8d5f-2dcd30d81957'] = $pane;
    $display->panels['center'][2] = 'new-2f8ed0d0-aabd-40cc-8d5f-2dcd30d81957';
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
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '91027b2b-a9f8-4c30-84cf-608524bd44cd';
    $display->content['new-91027b2b-a9f8-4c30-84cf-608524bd44cd'] = $pane;
    $display->panels['center'][3] = 'new-91027b2b-a9f8-4c30-84cf-608524bd44cd';
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
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = '2c5384eb-8241-4cbf-a6b5-aeb3a1a40523';
    $display->content['new-2c5384eb-8241-4cbf-a6b5-aeb3a1a40523'] = $pane;
    $display->panels['center'][4] = 'new-2c5384eb-8241-4cbf-a6b5-aeb3a1a40523';
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
    $pane->position = 5;
    $pane->locks = array();
    $pane->uuid = '644faa7b-274b-41e6-b1d0-f7df567e91b6';
    $display->content['new-644faa7b-274b-41e6-b1d0-f7df567e91b6'] = $pane;
    $display->panels['center'][5] = 'new-644faa7b-274b-41e6-b1d0-f7df567e91b6';
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
    $pane->position = 6;
    $pane->locks = array();
    $pane->uuid = '1ffdd101-4abb-456f-a821-37d48bea82a3';
    $display->content['new-1ffdd101-4abb-456f-a821-37d48bea82a3'] = $pane;
    $display->panels['center'][6] = 'new-1ffdd101-4abb-456f-a821-37d48bea82a3';
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
    $pane->position = 7;
    $pane->locks = array();
    $pane->uuid = '77cc5bf8-5bbc-40ce-8d91-e31ff9f96577';
    $display->content['new-77cc5bf8-5bbc-40ce-8d91-e31ff9f96577'] = $pane;
    $display->panels['center'][7] = 'new-77cc5bf8-5bbc-40ce-8d91-e31ff9f96577';
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
    $pane->position = 8;
    $pane->locks = array();
    $pane->uuid = 'cb32a0f3-6862-4976-bc53-e63d63d63c4d';
    $display->content['new-cb32a0f3-6862-4976-bc53-e63d63d63c4d'] = $pane;
    $display->panels['center'][8] = 'new-cb32a0f3-6862-4976-bc53-e63d63d63c4d';
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
    $pane->position = 9;
    $pane->locks = array();
    $pane->uuid = '0b4279c4-f4de-431f-9738-30d53b5790f0';
    $display->content['new-0b4279c4-f4de-431f-9738-30d53b5790f0'] = $pane;
    $display->panels['center'][9] = 'new-0b4279c4-f4de-431f-9738-30d53b5790f0';
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
    $pane->position = 10;
    $pane->locks = array();
    $pane->uuid = '38975c5b-29c7-472e-b1eb-49c0ed4b9309';
    $display->content['new-38975c5b-29c7-472e-b1eb-49c0ed4b9309'] = $pane;
    $display->panels['center'][10] = 'new-38975c5b-29c7-472e-b1eb-49c0ed4b9309';
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
    $pane->position = 11;
    $pane->locks = array();
    $pane->uuid = 'd05c7360-62ae-4b57-a2fa-af756b871d17';
    $display->content['new-d05c7360-62ae-4b57-a2fa-af756b871d17'] = $pane;
    $display->panels['center'][11] = 'new-d05c7360-62ae-4b57-a2fa-af756b871d17';
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
    $pane->position = 12;
    $pane->locks = array();
    $pane->uuid = 'e36dcb73-9189-40e8-acaa-bdd2574c9377';
    $display->content['new-e36dcb73-9189-40e8-acaa-bdd2574c9377'] = $pane;
    $display->panels['center'][12] = 'new-e36dcb73-9189-40e8-acaa-bdd2574c9377';
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
    $pane->position = 13;
    $pane->locks = array();
    $pane->uuid = '0c8ecff9-b7cd-4097-9147-ed11f1bf5f19';
    $display->content['new-0c8ecff9-b7cd-4097-9147-ed11f1bf5f19'] = $pane;
    $display->panels['center'][13] = 'new-0c8ecff9-b7cd-4097-9147-ed11f1bf5f19';
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
    $pane->position = 14;
    $pane->locks = array();
    $pane->uuid = '375bdc33-e7fe-43ca-9957-64127c7264fb';
    $display->content['new-375bdc33-e7fe-43ca-9957-64127c7264fb'] = $pane;
    $display->panels['center'][14] = 'new-375bdc33-e7fe-43ca-9957-64127c7264fb';
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
    $pane->position = 15;
    $pane->locks = array();
    $pane->uuid = 'b4c58a13-6a77-4758-a4e7-522b788832e0';
    $display->content['new-b4c58a13-6a77-4758-a4e7-522b788832e0'] = $pane;
    $display->panels['center'][15] = 'new-b4c58a13-6a77-4758-a4e7-522b788832e0';
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
    $pane->position = 16;
    $pane->locks = array();
    $pane->uuid = 'eb585847-4795-4b6d-9822-25da45177327';
    $display->content['new-eb585847-4795-4b6d-9822-25da45177327'] = $pane;
    $display->panels['center'][16] = 'new-eb585847-4795-4b6d-9822-25da45177327';
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
    $pane->position = 17;
    $pane->locks = array();
    $pane->uuid = '55e46dc6-cbe6-47b9-9228-2dbb98c6c582';
    $display->content['new-55e46dc6-cbe6-47b9-9228-2dbb98c6c582'] = $pane;
    $display->panels['center'][17] = 'new-55e46dc6-cbe6-47b9-9228-2dbb98c6c582';
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
    $pane->position = 18;
    $pane->locks = array();
    $pane->uuid = '249112dd-020c-473e-87b5-653d3edd5346';
    $display->content['new-249112dd-020c-473e-87b5-653d3edd5346'] = $pane;
    $display->panels['center'][18] = 'new-249112dd-020c-473e-87b5-653d3edd5346';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_partner_public_profile__test';
  $handler->task = 'page';
  $handler->subtask = 'partner_public_profile';
  $handler->handler = 'panel_context';
  $handler->weight = 1;
  $handler->conf = array(
    'title' => 'test',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => 'test',
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
  $display->uuid = '93d8cead-c2ca-480c-bca7-777938c2c731';
  $display->content = array();
  $display->panels = array();
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['partner_public_profile'] = $page;

  return $pages;

}
