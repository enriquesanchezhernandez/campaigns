<?php
/**
 * @file
 * osha_search.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function osha_search_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "apachesolr_search" && $api == "apachesolr_search_defaults") {
    return array("version" => "3");
  }
  if ($module == "facetapi" && $api == "facetapi_defaults") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function osha_search_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}