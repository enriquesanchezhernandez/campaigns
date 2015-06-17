<?php
/**
 * @file
 * osha_publication.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function osha_publication_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__publication_detail';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Publication detail',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => 'publication_detail',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'publication' => 'publication',
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
  $display->layout = 'twocol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'left' => NULL,
      'right' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = '6e25d777-3a5d-4043-8d80-fcd57f19c458';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-591e90db-25af-449e-a621-b9b57508ccaa';
    $pane->panel = 'left';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_cover_image';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'image',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'image_style' => 'large',
        'image_link' => 'file',
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
    $pane->uuid = '591e90db-25af-449e-a621-b9b57508ccaa';
    $display->content['new-591e90db-25af-449e-a621-b9b57508ccaa'] = $pane;
    $display->panels['left'][0] = 'new-591e90db-25af-449e-a621-b9b57508ccaa';
    $pane = new stdClass();
    $pane->pid = 'new-ca8d0cda-8c56-4d8c-a00f-579070d4cd5a';
    $pane->panel = 'right';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:body';
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
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'ca8d0cda-8c56-4d8c-a00f-579070d4cd5a';
    $display->content['new-ca8d0cda-8c56-4d8c-a00f-579070d4cd5a'] = $pane;
    $display->panels['right'][0] = 'new-ca8d0cda-8c56-4d8c-a00f-579070d4cd5a';
    $pane = new stdClass();
    $pane->pid = 'new-c45d4b5a-33fa-4f5a-9759-b17183eb9d1e';
    $pane->panel = 'right';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_file';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'file_table',
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
    $pane->uuid = 'c45d4b5a-33fa-4f5a-9759-b17183eb9d1e';
    $display->content['new-c45d4b5a-33fa-4f5a-9759-b17183eb9d1e'] = $pane;
    $display->panels['right'][1] = 'new-c45d4b5a-33fa-4f5a-9759-b17183eb9d1e';
    $pane = new stdClass();
    $pane->pid = 'new-282b4a45-002d-45fb-924b-2e48fdf50bd1';
    $pane->panel = 'right';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_related_publications';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'above',
      'formatter' => 'publication_twin_publications',
      'delta_limit' => '0',
      'delta_offset' => '0',
      'delta_reversed' => 0,
      'formatter_settings' => array(
        'view_mode' => 'teaser',
        'links' => 1,
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
    $pane->uuid = '282b4a45-002d-45fb-924b-2e48fdf50bd1';
    $display->content['new-282b4a45-002d-45fb-924b-2e48fdf50bd1'] = $pane;
    $display->panels['right'][2] = 'new-282b4a45-002d-45fb-924b-2e48fdf50bd1';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-591e90db-25af-449e-a621-b9b57508ccaa';
  $handler->conf['display'] = $display;
  $export['node_view__publication_detail'] = $handler;

  return $export;
}
