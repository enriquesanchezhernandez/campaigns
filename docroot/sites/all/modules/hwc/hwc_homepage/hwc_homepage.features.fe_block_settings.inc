<?php
/**
 * @file
 * hwc_homepage.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function hwc_homepage_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['blockgroup-tools_and_resources_block_g'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'tools_and_resources_block_g',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'blockgroup',
    'node_types' => array(),
    'pages' => '<front>',
    'roles' => array(),
    'themes' => array(
      'hwc_frontend' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'hwc_frontend',
        'weight' => 1,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Tools and resources block group',
    'visibility' => 1,
  );

  $export['menu_block-1'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 1,
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'menu_block',
    'node_types' => array(),
    'pages' => '<front>',
    'roles' => array(),
    'themes' => array(
      'hwc_frontend' => array(
        'region' => 'blockgroup_tools_and_resources_block_g',
        'status' => 1,
        'theme' => 'hwc_frontend',
        'weight' => 1,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '<none>',
    'visibility' => 1,
  );

  $export['nodeblock-54'] = array(
    'cache' => 1,
    'custom' => 0,
    'delta' => 54,
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'nodeblock',
    'node_types' => array(),
    'pages' => '<front>',
    'roles' => array(),
    'themes' => array(
      'hwc_frontend' => array(
        'region' => 'blockgroup_tools_and_resources_block_g',
        'status' => 1,
        'theme' => 'hwc_frontend',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '<none>',
    'visibility' => 1,
  );

  $export['views-frontpage_slider-block'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'frontpage_slider-block',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'hwc_frontend' => array(
        'region' => 'header',
        'status' => 1,
        'theme' => 'hwc_frontend',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  return $export;
}
