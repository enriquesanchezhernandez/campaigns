<?php

/**
 * @file
 * Functions for administration/settings interface.
 *
 */


/**
 * Configuration form for corporate_captcha.
 */
function eu_captcha_settings_form() {

  $captcha_languages = array(
    'bg',
    'cs',
    'da',
    'de',
    'el',
    'en',
    'es',
    'et',
    'fr',
    'ga',
    'hr',
    'it',
    'lt',
    'lv',
    'hu',
    'mt',
    'nl',
    'pl',
    'pt',
    'ro',
    'sk',
    'sl',
    'fi',
    'sv',
  );

  $form = array();
//  Disabled for us because we take the language from global $language
//  $form['language'] = array(
//    '#type' => 'select',
//    '#title' => t('Language'),
//    '#options' => $captcha_languages,
//    '#default_value' => variable_get('eu_captcha_language', 'en'),
//    '#description' => t('Language used for labels and ALT on captcha elements'),
//  );
  $form['type'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#options' => array('string' => 'string', 'math' => 'math'),
    '#default_value' => variable_get('eu_captcha_type', 'string'),
    '#description' => t('Type of the captcha, either a list of characters to copy OR a simple math problem to solve'),
  );
  $form['length'] = array(
    '#type' => 'textfield',
    '#title' => t('Length'),
    '#default_value' => variable_get('eu_captcha_length', 6),
    '#description' => t('Number of characters for the captcha'),
  );
  $form['case_sensitive'] = array(
    '#type' => 'checkbox',
    '#title' => t('Case sensitive'),
    '#default_value' => variable_get('eu_captcha_case_sensitive', '0'),
    '#description' => t('Indicates if captcha is case sensitive'),
  );
  $form['autodetect_protocol'] = array(
    '#type' => 'checkbox',
    '#title' => t('Autodetect protocol'),
    '#default_value' => variable_get('eu_captcha_autodetect_protocol', '1'),
    '#description' => t('Use the same protocol for captcha elements as the hosting page'),
  );
  $form['id_confirmation_field'] = array(
    '#type' => 'textfield',
    '#title' => t('ID confirmation field'),
    '#default_value' => variable_get('eu_captcha_id_confirmation_field', ''),
    '#description' => t('Unique ID of the field to type the captcha value'),
  );
  $form['label_confirmation_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Label confirmation field'),
    '#default_value' => variable_get('eu_captcha_label_confirmation_field', ''),
    '#description' => t('Label to display in front of the confirmation field'),
  );
  $form['perturbation'] = array(
    '#type' => 'textfield',
    '#title' => t('Perturbation'),
    '#default_value' => variable_get('eu_captcha_perturbation', 0.6),
    '#description' => t('Perturbation to apply on characters. Float between 0 (no perturbation) and 1 (maximal perturbation)'),
  );
  $form['num_lines'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of lines'),
    '#default_value' => variable_get('eu_captcha_num_lines', 8),
    '#description' => t('Number of lines to display in the background'),
  );
  $form['noise_level'] = array(
    '#type' => 'textfield',
    '#title' => t('Noise level'),
    '#default_value' => variable_get('eu_captcha_noise_level', 0),
    '#description' => t('Quantity of noise to display in the background'),
  );
  $form['image_bg_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Image background color'),
    '#default_value' => variable_get('eu_captcha_image_bg_color', ''),
    '#description' => t('Colour of background'),
  );
  $form['text_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Text color'),
    '#default_value' => variable_get('eu_captcha_text_color', ''),
    '#description' => t('Colour of characters'),
  );
  $form['line_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Line color'),
    '#default_value' => variable_get('eu_captcha_line_color', ''),
    '#description' => t('Colour of lines in the background'),
  );
  $form['noise_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Noise color'),
    '#default_value' => variable_get('eu_captcha_noise_color', ''),
    '#description' => t('Colour of noise in the background'),
  );
  $form['use_transparent_text'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use transparent text'),
    '#default_value' => variable_get('eu_captcha_use_transparent_text', '0'),
    '#description' => t('Transparency of the captcha'),
  );
  $form['text_transparency_percentage'] = array(
    '#type' => 'textfield',
    '#title' => t('Text transparency percentage'),
    '#default_value' => variable_get('eu_captcha_text_transparency_percentage', 0),
    '#description' => t('Transparency level of the captcha. Integer between 0 (no transparency) and 100 (maximum transparency)'),
  );
  $form['#submit'][] = 'eu_captcha_settings_form_submit';
  return system_settings_form($form);
}

/**
 * Validation function for eu_captcha configuration form.
 */
function eu_captcha_settings_form_validate($form, &$form_state) {
  if (!is_numeric($form_state['values']['length'])) {
    form_set_error('eu_captcha_invalid_length', 'The length needs to be integer.');
  }
  if (!is_numeric($form_state['values']['perturbation']) || $form_state['values']['perturbation'] < 0 || $form_state['values']['perturbation'] > 1) {
    form_set_error('eu_captcha_invalid_perturbation', 'The perturbation needs to be a float between 0 and 1.');
  }
  if (!is_numeric($form_state['values']['num_lines'])) {
    form_set_error('eu_captcha_invalid_num_lines', 'The number of lines needs to be integer.');
  }
  if (!is_numeric($form_state['values']['noise_level'])) {
    form_set_error('eu_captcha_invalid_noise_level', 'The noise level needs to be integer.');
  }
}

/**
 * Submit the form.
 */
function eu_captcha_settings_form_submit($form, &$form_state) {
  variable_set('eu_captcha_type', $form_state['values']['type']);
  variable_set('eu_captcha_length', $form_state['values']['length']);
  variable_set('eu_captcha_case_sensitive', $form_state['values']['case_sensitive']);
  variable_set('eu_captcha_autodetect_protocol', $form_state['values']['autodetect_protocol']);
  variable_set('eu_captcha_id_confirmation_field', $form_state['values']['id_confirmation_field']);
  variable_set('eu_captcha_label_confirmation_field', $form_state['values']['label_confirmation_field']);
  variable_set('eu_captcha_perturbation', $form_state['values']['perturbation']);
  variable_set('eu_captcha_num_lines', $form_state['values']['num_lines']);
  variable_set('eu_captcha_noise_level', $form_state['values']['noise_level']);
  variable_set('eu_captcha_image_bg_color', $form_state['values']['image_bg_color']);
  variable_set('eu_captcha_text_color', $form_state['values']['text_color']);
  variable_set('eu_captcha_line_color', $form_state['values']['line_color']);
  variable_set('eu_captcha_noise_color', $form_state['values']['noise_color']);
  variable_set('eu_captcha_use_transparent_text', $form_state['values']['use_transparent_text']);
  variable_set('eu_captcha_text_transparency_percentage', $form_state['values']['text_transparency_percentage']);
}
