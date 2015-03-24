<?php

// Localizations settings
osha_update_webform_localization();

/**
 * Set Webform Localization by String Translation
 * for the last inserted webform
 */
function osha_update_webform_localization(){
  // Get the last inserted node of webform content type
  $last_id = db_query("SELECT MAX(nid) FROM node WHERE type = 'webform'")->fetchField();

  // Insert or update options for the last webform inserted
  $query = db_query("SELECT * FROM webform_localization WHERE nid = $last_id")->fetchField();
  $data = array(
    'nid' => $last_id,
    'expose_strings' => 1,
    'single_webform' => $last_id,
    'webform_properties' => '',
  );
  if ($query) {
    drupal_write_record('webform_localization', $data, 'nid');
  }
  else {
    drupal_write_record('webform_localization', $data);
  }

  // Create webform node alias
  osha_update_webform_alias($last_id);
}

/**
 * Create alias for the last inserted webform
 */
function osha_update_webform_alias($last_id){
  $languages = osha_language_list();
  $source = 'node/'.$last_id;

  $query = db_query("SELECT * FROM url_alias WHERE source = '{$source}'")->fetchField();

  if (!$query) {
    foreach ($languages as $key => $language){
      $data = array(
        'source' => $source,
        'alias' => 'inside-eu-osha/governance-eu-osha/internal_documents/document_request_form',
        'language' => $key,
      );
      drupal_write_record('url_alias', $data);
    }
  }
}