<?php
/**
 * @file
 * hwc_homepage.panels_default.inc
 */

/**
 * Implements hook_default_panels_mini().
 */
function hwc_homepage_default_panels_mini() {
  $export = array();

  $mini = new stdClass();
  $mini->disabled = FALSE; /* Edit this to true to make a default mini disabled initially */
  $mini->api_version = 1;
  $mini->name = 'front_page_blocks_set';
  $mini->category = '';
  $mini->admin_title = 'Front page blocks set';
  $mini->admin_description = '';
  $mini->requiredcontexts = array();
  $mini->contexts = array();
  $mini->relationships = array();
  $display = new panels_display();
  $display->layout = 'flexible';
  $display->layout_settings = array(
    'items' => array(
      'canvas' => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 'main',
          1 => 1,
          2 => 2,
        ),
        'parent' => NULL,
      ),
      'main' => array(
        'type' => 'column',
        'width' => 50,
        'width_type' => '%',
        'children' => array(
          0 => 'main-row',
        ),
        'parent' => 'canvas',
        'class' => 'col-sm-4',
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
        'type' => 'column',
        'width' => 25,
        'width_type' => '%',
        'parent' => 'canvas',
        'children' => array(
          0 => 3,
        ),
        'class' => 'col-sm-4',
        'hide_empty' => 0,
      ),
      2 => array(
        'type' => 'column',
        'width' => 25,
        'width_type' => '%',
        'parent' => 'canvas',
        'children' => array(
          0 => 4,
        ),
        'class' => 'col-sm-4',
        'hide_empty' => 0,
      ),
      3 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'content',
        ),
        'parent' => '1',
        'class' => '',
        'hide_empty' => 0,
      ),
      'content' => array(
        'type' => 'region',
        'title' => 'content',
        'width' => 100,
        'width_type' => '%',
        'parent' => '3',
        'class' => '',
        'hide_empty' => 0,
      ),
      4 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'content_',
        ),
        'parent' => '2',
        'class' => '',
        'hide_empty' => 0,
      ),
      'content_' => array(
        'type' => 'region',
        'title' => 'content',
        'width' => 100,
        'width_type' => '%',
        'parent' => '4',
        'class' => '',
        'hide_empty' => 0,
      ),
    ),
  );
  $display->panel_settings = array(
    'style_settings' => array(
      'left' => NULL,
      'default' => NULL,
      'middle' => NULL,
      'right' => NULL,
      'center' => NULL,
      'content' => NULL,
      'content_' => NULL,
    ),
    'left' => array(
      'style' => '-1',
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'a027fda3-4ff0-4ff5-8da8-fad45303fba9';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-fb9dd05c-3e4a-45cf-9a57-a760e61585d0';
    $pane->panel = 'center';
    $pane->type = 'block';
    $pane->subtype = 'hwc_homepage-hwc_homepage_tools_and_resources';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Tools and publications',
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
    $pane->uuid = 'fb9dd05c-3e4a-45cf-9a57-a760e61585d0';
    $display->content['new-fb9dd05c-3e4a-45cf-9a57-a760e61585d0'] = $pane;
    $display->panels['center'][0] = 'new-fb9dd05c-3e4a-45cf-9a57-a760e61585d0';
    $pane = new stdClass();
    $pane->pid = 'new-f75f6127-6130-4530-9ac9-b250d61252e3';
    $pane->panel = 'content';
    $pane->type = 'block';
    $pane->subtype = 'menu-menu-information-tailored';
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
    $pane->uuid = 'f75f6127-6130-4530-9ac9-b250d61252e3';
    $display->content['new-f75f6127-6130-4530-9ac9-b250d61252e3'] = $pane;
    $display->panels['content'][0] = 'new-f75f6127-6130-4530-9ac9-b250d61252e3';
    $pane = new stdClass();
    $pane->pid = 'new-fe8c4144-a902-44fd-b7ca-9cd5a6dcfccc';
    $pane->panel = 'content_';
    $pane->type = 'views';
    $pane->subtype = 'news';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 1,
      'use_pager' => 0,
      'nodes_per_page' => '2',
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
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'fe8c4144-a902-44fd-b7ca-9cd5a6dcfccc';
    $display->content['new-fe8c4144-a902-44fd-b7ca-9cd5a6dcfccc'] = $pane;
    $display->panels['content_'][0] = 'new-fe8c4144-a902-44fd-b7ca-9cd5a6dcfccc';
    $pane = new stdClass();
    $pane->pid = 'new-5af75913-e8bf-4ede-a5c1-c66882f4f0a0';
    $pane->panel = 'content_';
    $pane->type = 'views';
    $pane->subtype = 'frontpage_events';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 1,
      'use_pager' => 0,
      'nodes_per_page' => '2',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'block',
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
    $pane->uuid = '5af75913-e8bf-4ede-a5c1-c66882f4f0a0';
    $display->content['new-5af75913-e8bf-4ede-a5c1-c66882f4f0a0'] = $pane;
    $display->panels['content_'][1] = 'new-5af75913-e8bf-4ede-a5c1-c66882f4f0a0';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $mini->display = $display;
  $export['front_page_blocks_set'] = $mini;

  return $export;
}
