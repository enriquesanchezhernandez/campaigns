<?php

function hwc_practical_tool_relevant_for_list() {
  $vocabulary = taxonomy_vocabulary_machine_name_load('practical_tool_relevant_for');
  $terms = taxonomy_get_tree($vocabulary->vid);
  $return = array('0' => 'All audience');
  foreach($terms as $key => $term) {
    $return[$term->tid] = $term->name;
  }
  return $return;
}

function hwc_practical_tool_menu_tools_form($form, $form_state) {
  drupal_set_title(t('Practical tools'));
  global $language;
  $text = hwc_req_param($form_state, 'text');
  $languages = hwc_req_param($form_state, 'languages', array($language->language));
  $form = array(
    '#action' => 'practical-tools',
    '#method' => 'post',
    'top' => array(
      '#type' => 'container',
      '#attributes' => array('class' => array('col col-md-12')),
    ),
    'left-column' => array(
      '#type' => 'container',
      '#attributes' => array('class' => array('col col-md-4')),
    ),
    'content' => array(
      '#type' => 'container',
      '#attributes' => array('class' => array('col col-md-8')),
    ),
  );
  $form['content']['text'] = array(
    '#type' => 'textfield',
    '#size' => 30,
    '#title' => t('Search'),
    '#maxlength' => 200,
    '#default_value' => $text,
    '#title_display' => 'invisible',
    '#attributes' => array('placeholder' => t('Free text filter')),
  );
  $form['content']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
  );
  $form['left-column']['relevant_for'] = array(
    '#type' => 'checkboxes',
    '#options' => hwc_practical_tool_relevant_for_list(),
    '#default_value' => array('0'),
    '#title' => t('Relevant for:'),
  );
  $form['left-column']['languages'] = array(
    '#type' => 'checkboxes',
    '#options' => osha_language_list_options(),
    '#default_value' => $languages ,
    '#title' => t('This tools are available in various languages:'),
  );
  if (empty($form_state['input'])) {
    $form['content']['results-native'] = hwc_practical_tool_menu_tools_search_native($form_state);
    $native_nids = $form['content']['results-native']['#nids'];
    $form['content']['results-related'] = hwc_practical_tool_menu_tools_search_related($form_state, $native_nids);
  }
  if (!empty($form_state['#results-native'])) {
    $form['content']['results-native'] = $form_state['#results-native'];
    $form['content']['results-related'] = $form_state['#results-related'];
  }
  return $form;
}


function hwc_practical_tool_menu_tools_form_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
  $form_state['redirect'] = FALSE;
  $form_state['#results-native'] = hwc_practical_tool_menu_tools_search_native($form_state);
  $native_nids = $form_state['#results-native']['#nids'];
  $form_state['#results-related'] = hwc_practical_tool_menu_tools_search_related($form_state, $native_nids);
}

function hwc_practical_tool_menu_tools_search_native($form_state) {
  global $language;
  $languages = hwc_req_param($form_state, 'languages', array($language->language));
  if(!$languages)
    $languages = array($language->language);
  $text = hwc_req_param($form_state, 'text');
  $is_search = !empty($text);
  $restrict = array();
  $relevant_for_ids = array();
  if ($is_search) {
    $relevant_for = $form_state['values']['relevant_for'];
    foreach ($relevant_for as $relf) {
      if ($relf) {
        $relevant_for_ids[] = $relf;
      }
    }
    /** @var SearchApiQuery $query */
    /** @var SearchApiSolrService $server */
    list($server, $query) = hwc_practical_tool_menu_tools_get_query();
    $query->condition('status', 1);
    $query->condition('type', 'practical_tool');
    $query->keys($text);
    $query->fields(array('title_field', 'body:value'));
    $results = $server->search($query);
    if (!empty($results['results'])) {
      foreach ($results['results'] as $result) {
        $restrict[] = $result['fields']['nid'];
      }
    }
    else {
      return array(
        '#nids' => '',
      );
    }

  }
  $q = db_select('node', 'a')
    ->fields('a', array('nid', 'vid'))
    ->condition('type', 'practical_tool')
    ->condition('status', 1)
    ->orderBy('changed', 'DESC');
  if (!empty($restrict)) {
    $q->condition('a.nid', $restrict, 'IN');
  }
  $pnids = $q->execute()->fetchCol();
  $nids = array();
  foreach ($pnids as $pnid) {
    // Check if the node is translated in all selected languages.
    $q = db_select('entity_translation', 'b');
    $q->fields('b', array('entity_id'));
    $q->innerJoin('node', 'a', 'a.nid = b.entity_id');
    $q->condition('b.entity_id', $pnid);
    $q->condition('b.entity_type', 'node');
    $q->condition('b.language', $languages, 'IN');
    $c = $q->countQuery()->execute()->fetchField();

    if (!empty($relevant_for_ids)) {
      // Check if the node is relevant for all selected 'relevant for' checkboxes.
      $q2 = db_select('field_data_field_relevant_for', 'b');
      $q2->fields('b', array('entity_id'));
      $q2->innerJoin('node', 'a', 'a.nid = b.entity_id');
      $q2->condition('b.entity_id', $pnid);
      $q2->condition('b.entity_type', 'node');
      $q2->condition('b.field_relevant_for_tid', $relevant_for_ids, 'IN');
      $c2 = $q2->countQuery()->execute()->fetchField();
    }
    else {
      // No 'relevant for' checkbox is selected, so let the node pass this check.
      $c2 = 1;
    }

    if ($c >= count($languages) && $c2 >= count($relevant_for_ids)) {
      $nids[] = $pnid;
    }
  }
  $nids = array_unique($nids);
  if (empty($nids)) {
    return array(
      '#nids' => '',
    );
  }
  $per_page = 4;
  $current_page = pager_default_initialize(count($nids), $per_page);
  $page = array_chunk($nids, $per_page, TRUE);
  $nodes = node_load_multiple($page[$current_page]);
  foreach($nodes as $node) {
    $node->filter_languages = $languages;
  }
  $pager_params = array('languages' => $languages);
  if ($is_search) {
    $pager_params['text'] = $text;
  }
  $ret = array(
    '#nids' => $nids,
    '#prefix' => '<h4>' . t('Practical tools available in national languages') . '</h4>',
    'results-native' => node_view_multiple($nodes, 'teaser', 0, $language->language),
    '#suffix' => theme('pager', array(
      'tags' => array('<', '<', '', '>', '>'),
      'quantity' => count($nodes),
      'parameters' => $pager_params,
    ))
  );
  return $ret;
}

function hwc_practical_tool_menu_tools_search_related($form_state, $native_nids) {
  global $language;
  $ret = array();
  if ($language->language == 'en') {
    return $ret;
  }
  $text = hwc_req_param($form_state, 'text');
  $is_search = !empty($text);
  $sort = $is_search ? 'search_api_relevance' : 'changed';
  $direction = 'desc';
  /** @var SearchApiQuery $query */
  /** @var SearchApiSolrService $server */
  list($server, $query) = hwc_practical_tool_menu_tools_get_query();
  $query->condition('status', 1);
  $query->condition('type', 'practical_tool');
  $query->condition('language', 'en');
  if (!empty($sort)) {
    $query->sort($sort, $direction);
  }
  if ($is_search) {
    $query->keys($text);
    $query->fields(array('title_field', 'body:value'));
  }
  $nids = array();
  $results = $server->search($query);
  if (!empty($results['results'])) {
    $nids = array();
    foreach ($results['results'] as $result) {
      $nids[] = $result['fields']['search_api_id'];
    }
  }
  $nids = array_unique($nids);
  if (!empty($native_nids)) { // Remove the nodes displayed above (native)
    $nids = array_filter($nids, function($nid) use ($native_nids) {
      return !in_array($nid, $native_nids);
    });
  }
  if (empty($nids)) {
    return array();
  }

  $per_page = 2;
  $current_page = pager_default_initialize(count($nids), $per_page, 1);

  $page = array_chunk($nids, $per_page, TRUE);
  $nodes = node_load_multiple($page[$current_page]);
  $languages = hwc_req_param($form_state, 'languages', array($language->language));
  foreach($nodes as $node) {
    $node->filter_languages = $languages;
  }
  $languages = hwc_req_param($form_state, 'languages', array($language->language));
  $pager_params = array('languages' => $languages);
  if ($is_search) {
    $pager_params['text'] = $text;
  }
  $ret = array(
    '#prefix' => '<h4>' . t('Other relevant practical tools in English') . '</h4>',
    'results-related' => node_view_multiple($nodes, 'teaser', 0, $language->language),
    '#suffix' => theme('pager', array(
      'tags' => array('<', '<', '', '>', '>'),
      'quantity' => count($nodes),
      'parameters' => $pager_params,
      'element' => 1,
    ))
  );
  return $ret;
}

function hwc_practical_tool_menu_tools_get_query() {
  module_load_include('inc', 'osha_search', 'osha_search.features');
  $servers = osha_search_default_search_api_server();
  reset($servers);
  $server = search_api_server_load(key($servers));
  $indexes = osha_search_default_search_api_index();
  reset($indexes);
  $index = search_api_index_load(key($indexes));
  $query = new SearchApiQuery($index);
  $query->fields(array()); // Avoid PHP notice
  $solr = new SearchApiSolrService($server);
  return array($solr, $query);
}
