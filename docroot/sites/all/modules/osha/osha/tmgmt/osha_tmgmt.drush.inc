<?php

/**
 * Implements COMMANDFILE_drush_command().
 */
function osha_tmgmt_drush_command()
{
  $items = array();
  $items['osha-tmgmt-statistics'] = array(
    'description' => 'Generate character/page count statistics for nodes',
    'aliases' => array('oshstats'),
    'examples' => array(),
    'arguments' => array(),
    'options' => array(),
    'sections' => array(),
  );
  $items['osha-tmgmt-retranslate-validate'] = array(
    'description' => 'Check if all translations of node have the same structure',
    'aliases' => array('oshrtv'),
    'examples' => array(),
    'arguments' => array('bundle' => 'The node bundle'),
    'options' => array('nids' => 'List of nids separated by comma'),
    'sections' => array(),
  );
  $items['osha-tmgmt-refresh-literals'] = array(
    'description' => 'Feed the list of string literals into the locale system to make it available for translation',
    'aliases' => array('oshrl'),
  );
  $items['test-osha-tmgmt-literals'] = array(
    'description' => 'Add translation X23456789X to all OSHA translatable strings in romanian language',
  );
  return $items;
}

/**
 * Implements COMMANDFILE_drush_help().
 */
function osha_tmgmt_drush_help($section)
{
  switch ($section) {
    case 'osha-tmgmt-statistics':
      return 'This command will create a group of test users assigned to the workflow roles';
    case 'osha-tmgmt-retranslate-validate':
      return 'This command will check if all translations of a node have a the same HTML structure of the body field';
  }
  return NULL;
}

function drush_osha_tmgmt_statistics()
{
  $rows = db_select('node', 'n')
    ->fields('n', array('nid'))
    ->condition('type', array(
        'article', 'banner', 'page', 'blog', 'calls', 'highlight',
        'job_vacancies', 'news', 'press_release', 'publication', 'seminar',
      )
    )
    ->execute()
    ->fetchAllAssoc('nid');
  drush_log(
    sprintf(
      'Computing character/page count for %s nodes, this might take a while ...',
      count($rows)
    ), 'warning'
  );
  foreach ($rows as $row) {
    $node = node_load($row->nid);
    $node = workbench_moderation_node_current_load($node);
    OshaTMGMTStatistics::computeEntityStatistics($node, 'node');
    $fake = new stdClass();
    $fake->id = $node->nid;
    $fake->nid = $node->nid;
    $fake->vid = $node->vid;
    $fake->field_character_count[LANGUAGE_NONE][0]['value'] = $node->character_count;
    $fake->field_page_count[LANGUAGE_NONE][0]['value'] = $node->page_count;
    $fake->bundle = $node->type;
    $fake->type = $node->type;
    field_attach_update('node', $fake);
  }
}

function drush_osha_tmgmt_retranslate_validate($bundle)
{
  $nids = drush_get_option('nids');
  if (!$nids) {
    // Load all
    $query = new EntityFieldQuery();
    $result = $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', $bundle)
      ->propertyOrderBy('nid')
      ->execute();
    $nids = array_keys($result['node']);
  } else {
    $nids = explode(',', $nids);
  }
  if (empty($nids)) {
    drush_log('No node found', 'warning');
    return;
  }
  print("Checking " . count($nids) . " nodes\n");
  foreach ($nids as $nid) {
    $messages = array();
    $valid_languages = array();
    $invalid_languages = array();
    $node = new stdClass();
    $node->nid = $nid;
    OshaTMGMTRetranslate::validate_can_retranslate($node, $messages, $valid_languages, $invalid_languages);
    drush_log(sprintf("Checking node %s (%s)", $node->nid, $node->path['alias']), 'success');
    foreach ($messages as $severity => $message_list) {
      foreach ($message_list as $message) {
        drush_log("  " . $message, $severity);
      }
    }
    foreach ($invalid_languages as $lang => $data) {
      $info = sprintf("Different HTML starting at id = '%s', <%s> in %s, <%s> in %s",
        $data['id'],
        $data[$data['source']], strtoupper($data['source']),
        $data[$lang], strtoupper($lang), TRUE);
      drush_log($info, 'warning');
    }
  }
}

function drush_osha_tmgmt_refresh_literals() {
  osha_tmgmt_refresh_string_list();
}

function drush_osha_tmgmt_test_osha_tmgmt_literals() {
  module_load_include('inc', 'i18n_string', 'i18n_string.pages');
  $strings = osha_tmgmt_get_osha_tmgmt_i18n_string_list();

  $lids = db_query("SELECT lid, source FROM {locales_source} WHERE textgroup NOT IN ('default', 'menu')")->fetchAllKeyed();
  foreach($lids as $lid => $source) {
    $form_state = array(
      'values' => array(
        'lid' => $lid,
        'textgroup' => 'default',
        'location' => '/index.php',
        'translations' => array(
          'ro' => '#ro#' . $source . '#/ro#',
        )
      )
    );
    i18n_string_locale_translate_edit_form_submit(array(), $form_state);
  }
  drush_log('Found ' . count($lids) . ' non built-in interace translated', 'success');

  $i = 0;
  drush_log('Found ' . count($strings) . ' OSHA strings registereed in hook_osha_tmgmt_i18n_string_list', 'success');
  foreach ($strings as $string) {
    if ($lid = db_query("SELECT lid FROM {locales_source} WHERE source = :source AND textgroup = 'default' AND context=''", array(':source' => $string))->fetchCol()) {
      $lid = $lid[0];
      $form_state = array(
        'values' => array(
          'lid' => $lid,
          'textgroup' => 'default',
          'location' => '/index.php',
          'translations' => array(
            'ro' => '#ro#' . $string . '#/ro#',
          )
        )
      );
      i18n_string_locale_translate_edit_form_submit(array(), $form_state);
      $i++;
    }
  }
  drush_log("Translated $i strings", 'success');
  if($i != count($strings)) {
    drush_log('String count not matched - some strings remain untranslated!', 'warning');
  }
}
