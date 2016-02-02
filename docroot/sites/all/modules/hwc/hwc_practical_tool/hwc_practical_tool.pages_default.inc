<?php
/**
 * @file
 * hwc_practical_tool.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function hwc_practical_tool_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__practical_tool_details';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 2;
  $handler->conf = array(
    'title' => 'Practical tool details',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => 'practical_tool_details',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'practical_tool' => 'practical_tool',
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
  $display->layout = 'practical_tool_details';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '545f69dd-e116-42e2-84f3-054360f7be44';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-17e4ba2d-cfaa-4abd-86fc-95793b7a896a';
    $pane->panel = 'middle';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:title_field';
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
      'override_title_heading' => 'h1',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '17e4ba2d-cfaa-4abd-86fc-95793b7a896a';
    $display->content['new-17e4ba2d-cfaa-4abd-86fc-95793b7a896a'] = $pane;
    $display->panels['middle'][0] = 'new-17e4ba2d-cfaa-4abd-86fc-95793b7a896a';
    $pane = new stdClass();
    $pane->pid = 'new-dbe6a5c3-c9c2-4e06-9375-c621746fa6d5';
    $pane->panel = 'middle';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_access_tool_link';
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
    $pane->uuid = 'dbe6a5c3-c9c2-4e06-9375-c621746fa6d5';
    $display->content['new-dbe6a5c3-c9c2-4e06-9375-c621746fa6d5'] = $pane;
    $display->panels['middle'][1] = 'new-dbe6a5c3-c9c2-4e06-9375-c621746fa6d5';
    $pane = new stdClass();
    $pane->pid = 'new-2bb1117c-639c-4418-bd68-2caa41b5e0b8';
    $pane->panel = 'middle';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_country';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'shs_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'linked' => 0,
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
    $pane->uuid = '2bb1117c-639c-4418-bd68-2caa41b5e0b8';
    $display->content['new-2bb1117c-639c-4418-bd68-2caa41b5e0b8'] = $pane;
    $display->panels['middle'][2] = 'new-2bb1117c-639c-4418-bd68-2caa41b5e0b8';
    $pane = new stdClass();
    $pane->pid = 'new-9f3c2633-133a-4798-8bf4-3121b92383a5';
    $pane->panel = 'middle';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_tool_type';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'shs_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'linked' => 0,
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
    $pane->uuid = '9f3c2633-133a-4798-8bf4-3121b92383a5';
    $display->content['new-9f3c2633-133a-4798-8bf4-3121b92383a5'] = $pane;
    $display->panels['middle'][3] = 'new-9f3c2633-133a-4798-8bf4-3121b92383a5';
    $pane = new stdClass();
    $pane->pid = 'new-5ba23bf6-8452-4173-ba14-920c18ac8087';
    $pane->panel = 'middle';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_provider';
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
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = '5ba23bf6-8452-4173-ba14-920c18ac8087';
    $display->content['new-5ba23bf6-8452-4173-ba14-920c18ac8087'] = $pane;
    $display->panels['middle'][4] = 'new-5ba23bf6-8452-4173-ba14-920c18ac8087';
    $pane = new stdClass();
    $pane->pid = 'new-3de5993f-8af1-4d01-be26-9c78f9f586c1';
    $pane->panel = 'middle';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:body';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'inline',
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
    $pane->position = 5;
    $pane->locks = array();
    $pane->uuid = '3de5993f-8af1-4d01-be26-9c78f9f586c1';
    $display->content['new-3de5993f-8af1-4d01-be26-9c78f9f586c1'] = $pane;
    $display->panels['middle'][5] = 'new-3de5993f-8af1-4d01-be26-9c78f9f586c1';
    $pane = new stdClass();
    $pane->pid = 'new-d56ffd82-10b5-4386-958c-2777853bbf08';
    $pane->panel = 'middle';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_additional_information';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'inline',
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
    $pane->uuid = 'd56ffd82-10b5-4386-958c-2777853bbf08';
    $display->content['new-d56ffd82-10b5-4386-958c-2777853bbf08'] = $pane;
    $display->panels['middle'][6] = 'new-d56ffd82-10b5-4386-958c-2777853bbf08';
    $pane = new stdClass();
    $pane->pid = 'new-02d7c136-f951-4699-87eb-d28672a3fd65';
    $pane->panel = 'middle';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_access_tool_link';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'inline',
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
    $pane->position = 7;
    $pane->locks = array();
    $pane->uuid = '02d7c136-f951-4699-87eb-d28672a3fd65';
    $display->content['new-02d7c136-f951-4699-87eb-d28672a3fd65'] = $pane;
    $display->panels['middle'][7] = 'new-02d7c136-f951-4699-87eb-d28672a3fd65';
    $pane = new stdClass();
    $pane->pid = 'new-5191f675-de94-4325-99c9-a1eb9598fe75';
    $pane->panel = 'middle';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_available_languages';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'language_list_formatter',
      'delta_limit' => '0',
      'delta_offset' => '0',
      'delta_reversed' => 0,
      'formatter_settings' => array(
        'format' => array(
          'name' => 'name',
          'iso' => 0,
          'name_native' => 0,
        ),
        'separator' => ',',
        'label' => 'Languages:',
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
    $pane->uuid = '5191f675-de94-4325-99c9-a1eb9598fe75';
    $display->content['new-5191f675-de94-4325-99c9-a1eb9598fe75'] = $pane;
    $display->panels['middle'][8] = 'new-5191f675-de94-4325-99c9-a1eb9598fe75';
    $pane = new stdClass();
    $pane->pid = 'new-ae6519dd-fdf0-4243-85d0-31800a0b5d40';
    $pane->panel = 'middle';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_access_tool_link_fc';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'inline',
      'formatter' => 'access_tool_link_details',
      'delta_limit' => '0',
      'delta_offset' => '0',
      'delta_reversed' => 0,
      'formatter_settings' => array(
        'edit' => '',
        'delete' => '',
        'add' => '',
        'description' => 1,
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
    $pane->position = 9;
    $pane->locks = array();
    $pane->uuid = 'ae6519dd-fdf0-4243-85d0-31800a0b5d40';
    $display->content['new-ae6519dd-fdf0-4243-85d0-31800a0b5d40'] = $pane;
    $display->panels['middle'][9] = 'new-ae6519dd-fdf0-4243-85d0-31800a0b5d40';
    $pane = new stdClass();
    $pane->pid = 'new-4ea61eda-ab16-477e-849f-d1b59140cfa6';
    $pane->panel = 'middle';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_external_urls';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'inline',
      'formatter' => 'entityreference_entity_view',
      'delta_limit' => '0',
      'delta_offset' => '0',
      'delta_reversed' => 0,
      'formatter_settings' => array(
        'link' => 1,
        'field_formatter_class' => '',
        'view_mode' => 'osha_resources',
        'links' => 0,
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
    $pane->uuid = '4ea61eda-ab16-477e-849f-d1b59140cfa6';
    $display->content['new-4ea61eda-ab16-477e-849f-d1b59140cfa6'] = $pane;
    $display->panels['middle'][10] = 'new-4ea61eda-ab16-477e-849f-d1b59140cfa6';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['node_view__practical_tool_details'] = $handler;

  return $export;
}

/**
 * Implements hook_default_page_manager_pages().
 */
function hwc_practical_tool_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'practical_tools_listing';
  $page->task = 'page';
  $page->admin_title = 'Practical tools listing';
  $page->admin_description = '';
  $page->path = 'practical-tools';
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
  $handler->name = 'page_practical_tools_listing__panel_context_f90c4d3e-683b-4dd2-a516-4b046ab3e75f';
  $handler->task = 'page';
  $handler->subtask = 'practical_tools_listing';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Practical tools listing',
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
    'middle' => array(
      'style' => '-1',
    ),
  );
  $display->cache = array();
  $display->title = 'Practical tools';
  $display->uuid = '286d97ce-6c9e-4437-852b-031f77a40961';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-84992a82-9ee8-44c2-8b19-f23a24a82abe';
    $pane->panel = 'middle';
    $pane->type = 'node';
    $pane->subtype = 'node';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'nid' => '139',
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
      'style' => 'default',
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'section-introduction',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '84992a82-9ee8-44c2-8b19-f23a24a82abe';
    $display->content['new-84992a82-9ee8-44c2-8b19-f23a24a82abe'] = $pane;
    $display->panels['middle'][0] = 'new-84992a82-9ee8-44c2-8b19-f23a24a82abe';
    $pane = new stdClass();
    $pane->pid = 'new-65a196f7-6a56-4168-94c7-f950af997e21';
    $pane->panel = 'middle';
    $pane->type = 'block';
    $pane->subtype = 'hwc_practical_tool-hwc_practical_tool_listing';
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
    $pane->uuid = '65a196f7-6a56-4168-94c7-f950af997e21';
    $display->content['new-65a196f7-6a56-4168-94c7-f950af997e21'] = $pane;
    $display->panels['middle'][1] = 'new-65a196f7-6a56-4168-94c7-f950af997e21';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = 'new-84992a82-9ee8-44c2-8b19-f23a24a82abe';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['practical_tools_listing'] = $page;

  return $pages;

}
