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
    $pane->pid = 'new-3c002ad1-74fe-4ad1-9a02-a6a97b5f53ce';
    $pane->panel = 'right';
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
        'title_style' => 'h2',
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
    $pane->uuid = '3c002ad1-74fe-4ad1-9a02-a6a97b5f53ce';
    $display->content['new-3c002ad1-74fe-4ad1-9a02-a6a97b5f53ce'] = $pane;
    $display->panels['right'][0] = 'new-3c002ad1-74fe-4ad1-9a02-a6a97b5f53ce';
    $pane = new stdClass();
    $pane->pid = 'new-b06a0bea-1c65-46a2-9e97-a27764fa2bb7';
    $pane->panel = 'right';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_publication_date';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'inline',
      'formatter' => 'date_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'format_type' => 'osha_day_only',
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_to' => '',
        'fromto' => 'both',
        'osha_date_theme' => '',
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
    $pane->uuid = 'b06a0bea-1c65-46a2-9e97-a27764fa2bb7';
    $display->content['new-b06a0bea-1c65-46a2-9e97-a27764fa2bb7'] = $pane;
    $display->panels['right'][1] = 'new-b06a0bea-1c65-46a2-9e97-a27764fa2bb7';
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
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'ca8d0cda-8c56-4d8c-a00f-579070d4cd5a';
    $display->content['new-ca8d0cda-8c56-4d8c-a00f-579070d4cd5a'] = $pane;
    $display->panels['right'][2] = 'new-ca8d0cda-8c56-4d8c-a00f-579070d4cd5a';
    $pane = new stdClass();
    $pane->pid = 'new-c45d4b5a-33fa-4f5a-9759-b17183eb9d1e';
    $pane->panel = 'right';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_file';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'file_all_group_mimetype',
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
    $pane->uuid = 'c45d4b5a-33fa-4f5a-9759-b17183eb9d1e';
    $display->content['new-c45d4b5a-33fa-4f5a-9759-b17183eb9d1e'] = $pane;
    $display->panels['right'][3] = 'new-c45d4b5a-33fa-4f5a-9759-b17183eb9d1e';
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
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = '282b4a45-002d-45fb-924b-2e48fdf50bd1';
    $display->content['new-282b4a45-002d-45fb-924b-2e48fdf50bd1'] = $pane;
    $display->panels['right'][4] = 'new-282b4a45-002d-45fb-924b-2e48fdf50bd1';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-591e90db-25af-449e-a621-b9b57508ccaa';
  $handler->conf['display'] = $display;
  $export['node_view__publication_detail'] = $handler;

  return $export;
}

/**
 * Implements hook_default_page_manager_pages().
 */
function osha_publication_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'case_studies';
  $page->task = 'page';
  $page->admin_title = 'Case studies';
  $page->admin_description = '';
  $page->path = 'case-studies';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_case_studies__panel_context_68462a27-ad1d-4253-b1a2-93f849f2c5a3';
  $handler->task = 'page';
  $handler->subtask = 'case_studies';
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
  $display->title = '';
  $display->uuid = '11a635b4-1f19-4fe1-930e-1a26cb5c344a';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-f9e6150c-417b-46b1-ad86-5cbe6cbbf358';
    $pane->panel = 'center';
    $pane->type = 'node';
    $pane->subtype = 'node';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'nid' => '140',
      'links' => 1,
      'leave_node_title' => 0,
      'identifier' => '',
      'build_mode' => 'body',
      'link_node_title' => 0,
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
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
    $pane->uuid = 'f9e6150c-417b-46b1-ad86-5cbe6cbbf358';
    $display->content['new-f9e6150c-417b-46b1-ad86-5cbe6cbbf358'] = $pane;
    $display->panels['center'][0] = 'new-f9e6150c-417b-46b1-ad86-5cbe6cbbf358';
    $pane = new stdClass();
    $pane->pid = 'new-4989b0bb-baba-4d1a-9ca8-a3b068672c20';
    $pane->panel = 'center';
    $pane->type = 'block';
    $pane->subtype = 'osha_publication-osha_case_studies_listing';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
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
      'css_class' => 'container',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '4989b0bb-baba-4d1a-9ca8-a3b068672c20';
    $display->content['new-4989b0bb-baba-4d1a-9ca8-a3b068672c20'] = $pane;
    $display->panels['center'][1] = 'new-4989b0bb-baba-4d1a-9ca8-a3b068672c20';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = 'new-f9e6150c-417b-46b1-ad86-5cbe6cbbf358';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['case_studies'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'publications_listing';
  $page->task = 'page';
  $page->admin_title = 'Publications listing';
  $page->admin_description = '';
  $page->path = 'publications';
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
  $handler->name = 'page_publications_listing__panel_context_03338832-cd5a-4fcc-9e3c-e69cbf5fb5e1';
  $handler->task = 'page';
  $handler->subtask = 'publications_listing';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Publications listing',
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
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'Publications';
  $display->uuid = '928827f4-5866-4902-8a91-a325c693a5ce';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-e7a9ab38-c830-4b2e-9e23-f49f161509c1';
    $pane->panel = 'middle';
    $pane->type = 'node';
    $pane->subtype = 'node';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'nid' => '105',
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
    $pane->uuid = 'e7a9ab38-c830-4b2e-9e23-f49f161509c1';
    $display->content['new-e7a9ab38-c830-4b2e-9e23-f49f161509c1'] = $pane;
    $display->panels['middle'][0] = 'new-e7a9ab38-c830-4b2e-9e23-f49f161509c1';
    $pane = new stdClass();
    $pane->pid = 'new-f5de493b-9610-4004-94cd-4bdb77aebd96';
    $pane->panel = 'middle';
    $pane->type = 'block';
    $pane->subtype = 'osha_publication-osha_publication_listing';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
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
    $pane->uuid = 'f5de493b-9610-4004-94cd-4bdb77aebd96';
    $display->content['new-f5de493b-9610-4004-94cd-4bdb77aebd96'] = $pane;
    $display->panels['middle'][1] = 'new-f5de493b-9610-4004-94cd-4bdb77aebd96';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = 'new-e7a9ab38-c830-4b2e-9e23-f49f161509c1';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['publications_listing'] = $page;

  return $pages;

}
