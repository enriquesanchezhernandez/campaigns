<?php
/**
 * @file
 * hcw.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function hcw_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['menu-menu-footer-menu'] = array(
    'cache' => -1,
    'delta' => 'menu-footer-menu',
    'i18n_block_language' => array(),
    'module' => 'menu',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'hcw_frontend' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'hcw_frontend',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
  );

  return $export;
}
