<?php
/**
 * @file
 * osha_blocks.features.inc
 */

/**
 * Implements hook_default_blockgroups().
 */
function osha_blocks_default_blockgroups() {
  return array(
    'related' => 'Related',
  );
}

/**
 * Implements hook_ctools_plugin_api().
 */
function osha_blocks_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
