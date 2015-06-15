<?php
/**
 * @file
 * osha_publication.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function osha_publication_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['views-publications-slidehow'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'publications-slidehow',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'views',
    'node_types' => array(),
    'pages' => 'tools-and-publications/publications',
    'roles' => array(),
    'themes' => array(
      'hwc_frontend' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'hwc_frontend',
        'weight' => 4,
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

  return $export;
}
