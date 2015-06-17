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

  return $export;
}
