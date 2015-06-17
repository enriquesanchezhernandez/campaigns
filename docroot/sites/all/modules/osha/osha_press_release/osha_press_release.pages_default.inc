<?php
/**
 * @file
 * osha_press_release.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function osha_press_release_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'press_room';
  $page->task = 'page';
  $page->admin_title = 'Press room';
  $page->admin_description = '';
  $page->path = 'press-room';
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
  $handler->name = 'page_press_room__panel_context_dc272202-981f-4f4f-a5a9-77d618920cda';
  $handler->task = 'page';
  $handler->subtask = 'press_room';
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
          0 => 'main-row',
          1 => 1,
        ),
        'parent' => 'canvas',
        'class' => 'col-sm-12',
        'hide_empty' => 0,
      ),
      'main-row' => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'center',
        ),
        'parent' => 'main',
      ),
      'center' => array(
        'type' => 'region',
        'title' => 'Center',
        'width' => 100,
        'width_type' => '%',
        'parent' => 'main-row',
      ),
      1 => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 2,
          1 => 3,
        ),
        'parent' => 'main',
        'class' => '',
        'hide_empty' => 0,
      ),
      2 => array(
        'type' => 'column',
        'width' => '71.24786528456254',
        'width_type' => '%',
        'parent' => '1',
        'children' => array(
          0 => 4,
        ),
        'class' => 'col-sm-9',
        'hide_empty' => 0,
      ),
      3 => array(
        'type' => 'column',
        'width' => '28.75213471543747',
        'width_type' => '%',
        'parent' => '1',
        'children' => array(
          0 => 5,
        ),
        'class' => 'col-sm-3',
        'hide_empty' => 0,
      ),
      4 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'content',
        ),
        'parent' => '2',
        'class' => '',
        'hide_empty' => 0,
      ),
      'content' => array(
        'type' => 'region',
        'title' => 'Content',
        'width' => 100,
        'width_type' => '%',
        'parent' => '4',
        'class' => '',
        'hide_empty' => 0,
      ),
      5 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'content_',
        ),
        'parent' => '3',
        'class' => '',
        'hide_empty' => 0,
      ),
      'content_' => array(
        'type' => 'region',
        'title' => 'Content',
        'width' => 100,
        'width_type' => '%',
        'parent' => '5',
        'class' => '',
        'hide_empty' => 0,
      ),
    ),
  );
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
      'content' => NULL,
      'content_' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'Press room';
  $display->uuid = '10d09353-21ff-4a10-998c-3270e13d7521';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-ab2e1394-442b-4579-85f6-07980c76900e';
    $pane->panel = 'center';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => '',
      'title' => '',
      'body' => '<p>Lorem ipsum</p>',
      'format' => 'full_html',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'ab2e1394-442b-4579-85f6-07980c76900e';
    $display->content['new-ab2e1394-442b-4579-85f6-07980c76900e'] = $pane;
    $display->panels['center'][0] = 'new-ab2e1394-442b-4579-85f6-07980c76900e';
    $pane = new stdClass();
    $pane->pid = 'new-c79a41b1-35b5-4f7f-a5f5-c26d6c4892dd';
    $pane->panel = 'content';
    $pane->type = 'views';
    $pane->subtype = 'press_releases';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 1,
      'nodes_per_page' => '10',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'page',
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
    $pane->uuid = 'c79a41b1-35b5-4f7f-a5f5-c26d6c4892dd';
    $display->content['new-c79a41b1-35b5-4f7f-a5f5-c26d6c4892dd'] = $pane;
    $display->panels['content'][0] = 'new-c79a41b1-35b5-4f7f-a5f5-c26d6c4892dd';
    $pane = new stdClass();
    $pane->pid = 'new-e411aa7e-f936-4ea8-813c-6556763895f6';
    $pane->panel = 'content_';
    $pane->type = 'block';
    $pane->subtype = 'osha_press_release-osha_press_rel_become_partner';
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
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'e411aa7e-f936-4ea8-813c-6556763895f6';
    $display->content['new-e411aa7e-f936-4ea8-813c-6556763895f6'] = $pane;
    $display->panels['content_'][0] = 'new-e411aa7e-f936-4ea8-813c-6556763895f6';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['press_room'] = $page;

  return $pages;

}
