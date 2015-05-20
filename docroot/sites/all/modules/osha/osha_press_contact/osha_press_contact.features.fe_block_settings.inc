<?php
/**
 * @file
 * osha_press_contact.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function osha_press_contact_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['views-bureau_members-block'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'bureau_members-block',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'views',
    'node_types' => array(),
    'pages' => 'node/1503',
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
        'weight' => 15,
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

  $export['views-fop_contacts-block'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'fop_contacts-block',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'views',
    'node_types' => array(
      0 => 'fop_page',
    ),
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
        'weight' => 17,
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

  $export['views-press_contacts-block'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'press_contacts-block',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'views',
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
        'weight' => 21,
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
