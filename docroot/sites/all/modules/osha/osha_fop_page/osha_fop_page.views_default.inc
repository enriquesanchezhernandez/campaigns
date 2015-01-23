<?php
/**
 * @file
 * osha_fop_page.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function osha_fop_page_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'fop_links';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'field_collection_item';
  $view->human_name = 'FOP Links';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'FOP Links';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_fop_link_section',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Field collection item: Entity with the Link (field_fop_link) */
  $handler->display->display_options['relationships']['field_fop_link_node']['id'] = 'field_fop_link_node';
  $handler->display->display_options['relationships']['field_fop_link_node']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_fop_link_node']['field'] = 'field_fop_link_node';
  $handler->display->display_options['relationships']['field_fop_link_node']['required'] = TRUE;
  /* Relationship: Content revision: Content */
  $handler->display->display_options['relationships']['nid']['id'] = 'nid';
  $handler->display->display_options['relationships']['nid']['table'] = 'node_revision';
  $handler->display->display_options['relationships']['nid']['field'] = 'nid';
  $handler->display->display_options['relationships']['nid']['relationship'] = 'field_fop_link_node';
  $handler->display->display_options['relationships']['nid']['required'] = TRUE;
  /* Field: Field collection item: Link */
  $handler->display->display_options['fields']['field_link']['id'] = 'field_link';
  $handler->display->display_options['fields']['field_link']['table'] = 'field_data_field_link';
  $handler->display->display_options['fields']['field_link']['field'] = 'field_link';
  $handler->display->display_options['fields']['field_link']['label'] = '';
  $handler->display->display_options['fields']['field_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_link']['click_sort_column'] = 'url';
  /* Field: Field collection item: Section */
  $handler->display->display_options['fields']['field_fop_link_section']['id'] = 'field_fop_link_section';
  $handler->display->display_options['fields']['field_fop_link_section']['table'] = 'field_data_field_fop_link_section';
  $handler->display->display_options['fields']['field_fop_link_section']['field'] = 'field_fop_link_section';
  $handler->display->display_options['fields']['field_fop_link_section']['label'] = '';
  $handler->display->display_options['fields']['field_fop_link_section']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_fop_link_section']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_fop_link_section']['type'] = 'i18n_taxonomy_term_reference_plain';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'field_fop_link_node';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $translatables['fop_links'] = array(
    t('Master'),
    t('FOP Links'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('field_fop_link'),
    t('Get the actual content from a content revision.'),
    t('All'),
    t('Block'),
  );
  $export['fop_links'] = $view;

  return $export;
}
