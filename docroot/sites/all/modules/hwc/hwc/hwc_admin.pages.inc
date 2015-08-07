<?php

function hwc_admin_config_form() {
  $form['title'] = array(
    '#markup' => '<h1>HWC website configuration</h1>',
  );
  $form['fb_app_key'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('fb_app_key', ''),
    '#title' => 'Facebook application key',
  );
  // By default, render the form using theme_system_settings_form().
  if (!isset($form ['#theme'])) {
    $form ['#theme'] = 'system_settings_form';
  }
  return system_settings_form($form);
}
