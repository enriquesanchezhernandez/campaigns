<?php
/**
 * @file
 * hwc_partner.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function hwc_partner_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['hwc_partner-hwc_partner_private_link_0'] = array(
    'cache' => 8,
    'custom' => 0,
    'delta' => 'hwc_partner_private_link_0',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'hwc_partner',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'hwc_frontend' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'hwc_frontend',
        'weight' => -56,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Create an Event',
    'visibility' => 0,
  );

  $export['hwc_partner-hwc_partner_private_link_1'] = array(
    'cache' => 8,
    'custom' => 0,
    'delta' => 'hwc_partner_private_link_1',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'hwc_partner',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'hwc_frontend' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'hwc_frontend',
        'weight' => -55,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Create News',
    'visibility' => 0,
  );

  $export['hwc_partner-hwc_partner_private_link_2'] = array(
    'cache' => 8,
    'custom' => 0,
    'delta' => 'hwc_partner_private_link_2',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'hwc_partner',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'hwc_frontend' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'hwc_frontend',
        'weight' => -54,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Private Area',
    'visibility' => 0,
  );

  return $export;
}
