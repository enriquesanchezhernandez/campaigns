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

  $tags_voc = taxonomy_vocabulary_machine_name_load(OSHA_TAXONOMIES_TAGS);
  $tags = taxonomy_term_load_multiple(array(), array('vid' => $tags_voc->vid));
  $options = array();
  foreach ($tags as $tag) {
    $options[$tag->tid] = $tag->name;
  }
  $form['hwc_current_campaign_tags'] = array(
    '#title' => 'Current campaigns tags',
    '#type' => 'select',
    '#multiple' => TRUE,
    '#options' => $options,
    '#default_value' => variable_get('hwc_current_campaign_tags', array()),
  );

  return system_settings_form($form);
}
