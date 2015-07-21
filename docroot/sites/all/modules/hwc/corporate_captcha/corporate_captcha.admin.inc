<?php

/**
 * @file
 * Functions for administration/settings interface.
 *
 */


/**
 * Configuration form for corporate_captcha.
 */
function corporate_captcha_settings_form() {

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
//    '#default_value' => variable_get('corporate_captcha_language', 'en'),
//    '#description' => t('Language used for labels and ALT on captcha elements'),
//  );
  $form['type'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#options' => array('string' => 'string', 'math' => 'math'),
    '#default_value' => variable_get('corporate_captcha_type', 'string'),
    '#description' => t('Type of the captcha, either a list of characters to copy OR a simple math problem to solve'),
  );
  $form['length'] = array(
    '#type' => 'textfield',
    '#title' => t('Length'),
    '#default_value' => variable_get('corporate_captcha_length', 6),
    '#description' => t('Number of characters for the captcha'),
  );
  $form['case_sensitive'] = array(
    '#type' => 'select',
    '#title' => t('Case sensitive'),
    '#options' => array('false' => 'false', 'true' => 'true'),
    '#default_value' => variable_get('corporate_captcha_case_sensitive', 'false'),
    '#description' => t('Indicates if captcha is case sensitive'),
  );
  $form['autodetect_protocol'] = array(
    '#type' => 'select',
    '#title' => t('Autodetect protocol'),
    '#options' => array('false' => 'false', 'true' => 'true'),
    '#default_value' => variable_get('corporate_captcha_autodetect_protocol', 'true'),
    '#description' => t('Use the same protocol for captcha elements as the hosting page'),
  );
  $form['perturbation'] = array(
    '#type' => 'textfield',
    '#title' => t('Perturbation'),
    '#default_value' => variable_get('corporate_captcha_perturbation', 0.6),
    '#description' => t('Perturbation to apply on characters. Float between 0 (no perturbation) and 1 (maximal perturbation)'),
  );
  $form['num_lines'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of lines'),
    '#default_value' => variable_get('corporate_captcha_num_lines', 8),
    '#description' => t('Number of lines to display in the background'),
  );
  $form['noise_level'] = array(
    '#type' => 'textfield',
    '#title' => t('Noise level'),
    '#default_value' => variable_get('corporate_captcha_noise_level', 0),
    '#description' => t('Quantity of noise to display in the background'),
  );
  $form['#submit'][] = 'corporate_captcha_settings_form_submit';
  return system_settings_form($form);
}

/**
 * Validation function for corporate_captcha configuration form.
 */
function corporate_captcha_settings_form_validate($form, &$form_state) {
  if (!is_numeric($form_state['values']['length'])) {
    form_set_error('corporate_captcha_invalid_length', 'The length needs to be integer.');
  }
  if (!is_numeric($form_state['values']['perturbation']) || $form_state['values']['perturbation'] < 0 || $form_state['values']['perturbation'] > 1) {
    form_set_error('corporate_captcha_invalid_perturbation', 'The perturbation needs to be a float between 0 and 1.');
  }
  if (!is_numeric($form_state['values']['num_lines'])) {
    form_set_error('corporate_captcha_invalid_num_lines', 'The number of lines needs to be integer.');
  }
  if (!is_numeric($form_state['values']['noise_level'])) {
    form_set_error('corporate_captcha_invalid_noise_level', 'The noise level needs to be integer.');
  }
}

/**
 * Submit the form.
 */
function corporate_captcha_settings_form_submit($form, &$form_state) {
  variable_set('corporate_captcha_type', $form_state['values']['type']);
  variable_set('corporate_captcha_length', $form_state['values']['length']);
  variable_set('corporate_captcha_case_sensitive', $form_state['values']['case_sensitive']);
  variable_set('corporate_captcha_case_autodetect_protocol', $form_state['values']['autodetect_protocol']);
  variable_set('corporate_captcha_perturbation', $form_state['values']['perturbation']);
  variable_set('corporate_captcha_num_lines', $form_state['values']['num_lines']);
  variable_set('corporate_captcha_noise_level', $form_state['values']['noise_level']);
}
