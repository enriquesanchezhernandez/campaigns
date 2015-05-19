<?php
/**
 * @file
 * osha.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function hcw_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "linkit" && $api == "linkit_profiles") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function hcw_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
