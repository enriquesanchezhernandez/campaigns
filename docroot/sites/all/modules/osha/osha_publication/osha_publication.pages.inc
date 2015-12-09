<?php

function osha_publication_menu_publications_form($form, $form_state) {
  drupal_set_title(t('Publications'));
  global $language;
  $text = hwc_req_param($form_state, 'text');
  $languages = hwc_req_param($form_state, 'languages', array($language->language));
  $form = array(
    '#action' => 'publications',
    '#method' => 'post',
    'left-column' => array(
      '#type' => 'container',
      '#attributes' => array('class' => array('col col-md-3'))
    ),
    'content' => array(
      '#type' => 'container',
      '#attributes' => array('class' => array('col col-md-9')),
    )
  );
  $form['content']['slideshow'] = array(
    '#type' => 'markup',
    '#markup' => views_embed_view('publications_slideshow', 'slidehow'),
  );
  $form['content']['text'] = array(
    '#type' => 'textfield',
    '#size' => 30,
    '#title' => t('Search'),
    '#maxlength' => 200,
    '#default_value' => $text,
    '#title_display' => 'invisible',
    '#attributes' => array('placeholder' => t('Search Publications')),
    '#prefix' => '<div id="search">',
  );
  $form['content']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
    '#suffix' => '</div>',
  );
  $form['left-column']['relevant_for'] = array(
    '#type' => 'checkboxes',
    '#options' => _hwc_segment_options_list(),
    '#default_value' => array('0'),
    '#title' => t('Relevant for:'),
  );
  $form['left-column']['publication_type'] = array(
    '#type' => 'checkboxes',
    '#options' => _publication_type_options_list(),
    '#default_value' => array('0'),
    '#title' => t('Publications type:'),
  );
  $form['left-column']['languages'] = array(
    '#type' => 'checkboxes',
    '#options' => osha_language_list_options(),
    '#default_value' => $languages,
    '#title' => t('This tool is available in various languages'),
  );
  if (empty($form_state['input'])) {
    $form['content']['results-native'] = osha_publication_menu_publications_search_native($form_state);
    $native_nids = $form['content']['results-native']['#nids'];
    $form['content']['results-related'] = osha_publication_menu_publications_search_related($form_state, $native_nids);
  }
  if (!empty($form_state['#results-native'])) {
    $form['content']['results-native'] = $form_state['#results-native'];
    $form['content']['results-related'] = $form_state['#results-related'];
  }
  return $form;
}


function osha_publication_menu_publications_form_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
  $form_state['redirect'] = FALSE;
  $form_state['#results-native'] = osha_publication_menu_publications_search_native($form_state);
  $native_nids = array();
  if (!empty($form_state['#results-native']['#nids'])) {
    $native_nids = $form_state['#results-native']['#nids'];
  }
  $form_state['#results-related'] = osha_publication_menu_publications_search_related($form_state, $native_nids);
}

function osha_publication_menu_publications_search_native($form_state) {
  global $language;
  $languages = hwc_req_param($form_state, 'languages', array($language->language));
  if(!$languages)
    $languages = array($language->language);
  $text = hwc_req_param($form_state, 'text');
  $is_search = !empty($text);
  $restrict = array();
  if ($is_search) {
    /** @var SearchApiQuery $query */
    /** @var SearchApiSolrService $server */
    list($server, $query) = osha_publication_menu_publications_get_query();
    $query->condition('status', 1);
    $query->condition('type', 'publication');
    $query->condition('field_file:file', 0, '>');
    $query->keys($text);
    $query->fields(array('title_field', 'body:value'));
    $results = $server->search($query);
    if (!empty($results['results'])) {
      foreach ($results['results'] as $result) {
        $restrict[] = $result['fields']['nid'];
      }
    }
    if (empty($restrict)) {
      return array(
        '#nids' => '',
      );
    }
  }
  $relevant_for_ids = array();
  $relevant_for = array();
  if (!empty($form_state['values']['relevant_for'])) {
    $relevant_for = $form_state['values']['relevant_for'];
  }
  foreach ($relevant_for as $relf) {
    if ($relf) {
      $relevant_for_ids[] = $relf;
    }
  }

  $publication_type_ids = array();
  $publication_type = array();
  if (!empty($form_state['values']['publication_type'])) {
    $publication_type = $form_state['values']['publication_type'];
  }
  foreach ($publication_type as $pubt) {
    if ($pubt) {
      $publication_type_ids[] = $pubt;
    }
  }

  // Select all publications having field_file available in filtered languages.
  $q = db_select('node', 'a');
  $q->innerJoin('field_data_field_publication_type', 'b', 'a.nid = b.entity_id');
  $q->fields('a', array('nid', 'vid'));
  $q->condition('a.type', 'publication');
  $q->condition('a.status', 1);
  $q->orderBy('a.changed', 'DESC');
  if (!empty($restrict)) {
    $q->condition('a.nid', $restrict, 'IN');
  }
  if (!empty($publication_type_ids)) {
    $q->condition('b.field_publication_type_tid', $publication_type_ids, 'IN');
  }
  $pnids = $q->execute()->fetchCol();
  $nids = array();
  foreach($pnids as $pnid) {
    $q = db_select('field_data_field_file', 'b');
    $q->fields('b', array('entity_id'));
    $q->innerJoin('node', 'a', 'a.nid = b.entity_id AND a.vid = b.revision_id');
    $q->condition('b.bundle', 'publication');
    $q->condition('b.entity_id', $pnid);
    $q->condition('b.language', $languages, 'IN');
    $c = $q->countQuery()->execute()->fetchField();

    if (!empty($relevant_for_ids)) {
      // Check if the node is relevant for all selected 'relevant for' checkboxes.
      $q2 = db_select('field_data_field_segment', 'b');
      $q2->fields('b', array('entity_id'));
      $q2->innerJoin('node', 'a', 'a.nid = b.entity_id');
      $q2->condition('b.entity_id', $pnid);
      $q2->condition('b.entity_type', 'node');
      $q2->condition('b.field_segment_tid', $relevant_for_ids, 'IN');
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
    return array();
  }

  //Order publications by publication_date
  $q = db_select('field_data_field_publication_date', 'a');
  $q->fields('a', array('entity_id'));
  $q->condition('entity_id', $nids, 'IN');
  $q->orderBy('field_publication_date_value', 'DESC');
  $nids = $q->execute()->fetchCol();

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
    '#prefix' => '<h4>' . t('Tools and Publications available') . '</h4>',
    'results-native' => node_view_multiple($nodes, 'pub_teaser', 0, $language->language),
    '#suffix' => theme('pager', array(
      'tags' => array('<', '<', '', '>', '>'),
      'quantity' => count($nodes),
      'parameters' => $pager_params,
    ))
  );
  return $ret;
}

function osha_publication_menu_publications_search_related($form_state, $native_nids) {
  global $language;
  $ret = array();
  $languages = hwc_req_param($form_state, 'languages', array($language->language));
  if(!empty($languages)) {
    if (in_array('en', $languages)) {
      return $ret;
    }
  }
  else {
    if($language->language == 'en') {
      return $ret;
    }
  }
  $text = hwc_req_param($form_state, 'text');
  $is_search = !empty($text);
  $sort = $is_search ? 'search_api_relevance' : 'changed';
  $direction = 'desc';
  /** @var SearchApiQuery $query */
  /** @var SearchApiSolrService $server */
  list($server, $query) = osha_publication_menu_publications_get_query();
  $query->condition('status', 1);
  $query->condition('type', 'publication');
  $query->condition('language', 'en');
  $query->condition('field_file:file', 0, '>');
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
      $nids[] = $result['fields']['nid'];
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
  foreach($nodes as $node) {
    $node->filter_languages = $languages;
  }
  $languages = hwc_req_param($form_state, 'languages', array($language->language));
  $pager_params = array('languages' => $languages);
  if ($is_search) {
    $pager_params['text'] = $text;
  }
  $ret = array(
    '#prefix' => '<h4>' . t('Other relevant publications in English') . '</h4>',
    'results-related' => node_view_multiple($nodes, 'pub_teaser', 0, $language->language),
    '#suffix' => theme('pager', array(
      'tags' => array('<', '<', '', '>', '>'),
      'quantity' => count($nodes),
      'parameters' => $pager_params,
      'element' => 1,
    ))
  );
  return $ret;
}

function osha_publication_menu_case_studies_form($form, $form_state) {
  drupal_set_title(t('Publications'));
  $text = hwc_req_param($form_state, 'text');
  $form = array(
    '#action' => 'case-studies',
    '#method' => 'post',
    'left-column' => array(
      '#type' => 'container',
      '#attributes' => array('class' => array('col col-md-3'))
    ),
    'content' => array(
      '#type' => 'container',
      '#attributes' => array('class' => array('col col-md-9')),
    )
  );
  $form['content']['text'] = array(
    '#type' => 'textfield',
    '#size' => 30,
    '#title' => t('Search'),
    '#maxlength' => 200,
    '#default_value' => $text,
    '#title_display' => 'invisible',
    '#attributes' => array('placeholder' => t('Search Case studies')),
    '#prefix' => '<div id="search">',
  );
  $form['content']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
    '#suffix' => '</div>',
  );
  $form['left-column']['relevant_for'] = array(
    '#type' => 'checkboxes',
    '#options' => _hwc_segment_options_list(),
    '#default_value' => array('0'),
    '#title' => t('Relevant for:'),
  );
  if (empty($form_state['input'])) {
    $form['content']['results-native'] = osha_publication_menu_case_studies_search_native($form_state);
  }
  if (!empty($form_state['#results-native'])) {
    $form['content']['results-native'] = $form_state['#results-native'];
  }
  return $form;
}


function osha_publication_menu_case_studies_form_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
  $form_state['redirect'] = FALSE;
  $form_state['#results-native'] = osha_publication_menu_case_studies_search_native($form_state);
}

function osha_publication_menu_case_studies_search_native($form_state) {
  global $language;
  $languages = hwc_req_param($form_state, 'languages', array($language->language));
  $text = hwc_req_param($form_state, 'text');
  $is_search = !empty($text);
  $restrict = array();
  list($server, $query) = osha_publication_menu_publications_get_query();
  $query->condition('status', 1);
  $query->condition('type', 'publication');
  $query->condition('field_file:file', 0, '>');
  $query->condition('field_publication_type', 92);
  $query->keys($text);
  $query->fields(array('title_field', 'body:value'));
  $query->sort('field_publication_date', 'DESC');
  $results = $server->search($query);
  if (!empty($results['results'])) {
    foreach ($results['results'] as $result) {
      if (isset($result['fields']['nid'])) {
        $restrict[] = $result['fields']['nid'];
      }
    }
  }
  if (empty($restrict)) {
    return array(
      '#nids' => '',
    );
  }
  $nids = array_unique($restrict);
  $relevant_for = $form_state['submitted'] === TRUE ? $form_state['values']['relevant_for'] : array();
  foreach ($relevant_for as $relf) {
    if ($relf) {
      $relevant_for_ids[] = $relf;
    }
  }
  if (!empty($relevant_for_ids)) {
    // Check if the node is relevant for all selected 'relevant for' checkboxes.
    $q2 = db_select('field_data_field_segment', 'b');
    $q2->fields('b', array('entity_id'));
    $q2->innerJoin('node', 'a', 'a.nid = b.entity_id');
    $q2->condition('b.entity_id', $restrict, 'IN');
    $q2->condition('b.entity_type', 'node');
    $q2->condition('b.field_segment_tid', $relevant_for_ids, 'IN');
    $nids = $q2->execute()->fetchCol();
  }
  $nids = array_unique($nids);
  if (empty($nids)) {
    return array();
  }
  $per_page = 5;
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
    'results-native' => node_view_multiple($nodes, 'pub_teaser', 0, $language->language),
    '#suffix' => theme('pager', array(
      'tags' => array('<', '<', '', '>', '>'),
      'quantity' => count($nodes),
      'parameters' => $pager_params,
    ))
  );
  return $ret;
}

function osha_publication_menu_publications_get_query() {
  $server = search_api_server_load('solr_server');
  $index = search_api_index_load(SOLR_SEARCH_INDEX);
  $query = new SearchApiQuery($index);
  $query->fields(array()); // Avoid PHP notice
  $solr = new SearchApiSolrService($server);
  return array($solr, $query);
}

/**
 * Get options for publication type filter.
 */
function _publication_type_options_list() {
  $return = array('0' => t('All types'));
  $vocabulary = taxonomy_vocabulary_machine_name_load('publication_types');
  if (!empty($vocabulary)) {
    $terms = taxonomy_get_tree($vocabulary->vid);
    foreach ($terms as $key => $term) {
      $return[$term->tid] = $term->name;
    }
  }
  return $return;
}