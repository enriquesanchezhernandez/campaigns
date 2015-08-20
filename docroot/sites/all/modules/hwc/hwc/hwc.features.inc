<?php
/**
 * @file
 * hwc.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function hwc_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "linkit" && $api == "linkit_profiles") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function hwc_image_default_styles() {
  $styles = array();

  // Exported image style: medium_large.
  $styles['medium_large'] = array(
    'label' => 'Medium large (330x330)',
    'effects' => array(
      2 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 330,
          'height' => 330,
          'upscale' => 0,
        ),
        'weight' => 2,
      ),
    ),
  );

  return $styles;
}
