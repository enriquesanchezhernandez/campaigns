<?php

/**
 * Implementation of hook_views_plugins().
 */
function hwc_views_plugins() {
  $path = drupal_get_path('module', 'hwc');

  return array(
    'style' => array(
      'hwc_quicktabs' => array(
        'title' => t('HWC Quicktabs'),
        'help' => t('Display view in Quicktabs.'),
        'handler' => 'hwc_quicktabs_style_plugin',
        'path' => "$path/includes",
        'theme' => 'quicktabs_view',
        'uses row plugin' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
  );
}
