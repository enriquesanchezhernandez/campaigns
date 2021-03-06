<?php

function hwc_practical_tool_menu_tools_form($form, $form_state) {
  drupal_set_title(t('Practical tools'));
  global $language;
  $text = hwc_req_param($form_state, 'text');
  $languages = hwc_req_param($form_state, 'languages', array($language->language));
  $sort = hwc_req_param($form_state, 'sort', 'date');
  $form = array(
    '#action' => 'practical-tools',
    '#method' => 'post',
    'top' => array(
      '#type' => 'container',
      '#attributes' => array('class' => array('col col-md-12')),
    ),
    'left-column' => array(
      '#type' => 'container',
      '#attributes' => array('class' => array('col col-md-3')),
    ),
    'content' => array(
      '#type' => 'container',
      '#attributes' => array('class' => array('col col-md-9')),
    ),
  );
  $form['content']['text'] = array(
    '#type' => 'textfield',
    '#size' => 30,
    '#title' => t('Search'),
    '#maxlength' => 200,
    '#default_value' => $text,
    '#title_display' => 'invisible',
    '#attributes' => array('placeholder' => t('Search Practical tools')),
    '#prefix' => '<div id="search">',
  );
  $form['content']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
    '#suffix' => '</div>',
  );
  $form['content']['sort_fieldset'] = array(
    /* Needed so that the page passes Web Accessibility test */
    '#type' => 'fieldset',
  );
  $form['content']['sort_fieldset']['sort'] = array(
    '#type' => 'radios',
    '#title' => t('Sort by'),
    '#default_value' => $sort,
    '#options' => array('date' => t('Date'), 'alphabetically' => t('Alphabetically')),
  );
  $form['left-column']['relevant_for'] = array(
    '#type' => 'checkboxes',
    '#options' => _hwc_segment_options_list(),
    '#default_value' => array('0'),
    '#title' => t('Relevant for'),
  );
  $form['left-column']['languages'] = array(
    '#type' => 'checkboxes',
    '#options' => osha_language_list_options(),
    '#default_value' => $languages ,
    '#title' => t('Tools are available in several languages'),
  );
  $form['#attached']['js'] = array(
    drupal_get_path('module', 'hwc_practical_tool') . '/js/checkbox-submit.js',
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

function _hwc_practical_tool_sort_nodes(&$nids) {
  global $language;

  $q = db_select('node', 'a');
  $q->innerJoin('field_data_title_field', 'b', 'a.nid = b.entity_id');
  $q->fields('a', array('nid'))
    ->fields('b', array('title_field_value', 'language'))
    ->condition('a.nid', $nids, 'IN')
    ->condition('b.language', array('en', $language->language), 'IN')
    ->orderBy('b.title_field_value');
  $res = $q->execute()->fetchAll();
  $added = array();
  $nids = array();
  foreach ($res as $item) {
    $nid = $item->nid;
    if (!isset($added[$nid])) {
      $nids[] = $nid;
      $added[$nid] = count($nids) - 1;
      continue;
    }
    if ($item->language == 'en') {
      // Node is already added in current language.
      continue;
    }
    unset($nids[$added[$nid]]);
    $nids[] = $nid;
  }
}
function hwc_practical_tool_menu_tools_search_native($form_state) {
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
    list($server, $query) = hwc_practical_tool_menu_tools_get_query();
    $query->condition('status', 1);
    $query->condition('type', 'practical_tool');
    $query->keys($text);
    $query->fields(array('title_field', 'body:value'));
    $results = $server->search($query);
    if (!empty($results['results'])) {
      foreach ($results['results'] as $result) {
        list($lng, $nid) = explode('_', $result['id'], 2);
        $restrict[] = $nid;
      }
      $restrict = array_unique($restrict);
    }
    else {
      return array(
        '#nids' => '',
      );
    }
  }
  $relevant_for_ids = array();
  if ($form_state['submitted'] === TRUE) {
    $relevant_for = $form_state['values']['relevant_for'];
    foreach ($relevant_for as $relf) {
      if ($relf) {
        $relevant_for_ids[] = $relf;
      }
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
  if (!empty($languages)) {
    $q->innerJoin('field_data_field_access_tool_link_fc', 'fc', 'a.nid = fc.entity_id AND a.vid = fc.revision_id');
    $q->innerJoin('field_data_field_available_languages', 'al', 'fc.field_access_tool_link_fc_value = al.entity_id AND fc.field_access_tool_link_fc_revision_id = al.revision_id');
    $q->condition('al.field_available_languages_value', $languages, 'IN');
  }
  if (!empty($relevant_for_ids)) {
    $q->innerJoin('field_data_field_segment', 'fs', 'fs.entity_id = a.nid AND fs.revision_id = a.vid');
    $q->condition('fs.field_segment_tid', $relevant_for_ids, 'IN');
  }
  $nids = $q->execute()->fetchCol();
  $nids = array_unique($nids);
  if (empty($nids)) {
    return array(
      '#nids' => '',
    );
  }

  $sort = hwc_req_param($form_state, 'sort');
  if ($sort == 'alphabetically') {
    _hwc_practical_tool_sort_nodes($nids);
  }

  $per_page = 4;
  $current_page = pager_default_initialize(count($nids), $per_page);
  $page = array_chunk($nids, $per_page, TRUE);
  $nodes = node_load_multiple($page[$current_page]);
  foreach ($nodes as $node) {
    $node->filter_languages = $languages;
  }
  $pager_params = array('languages' => $languages, 'sort' => $sort);
  if ($is_search) {
    $pager_params['text'] = $text;
  }
  $language_names = array();
  $languages_objects = language_list();
  foreach($languages as $code) {
//    $l = i18n_language_load($code);
//    $language_names[] = $l->native;
    $language_names[] = $languages_objects[$code]->name;
  }
  $ret = array(
    '#nids' => $nids,
    '#prefix' => '<h2 class="h4-title">' . t('Tools and guidance in ') . implode(', ', $language_names) . '</h2>',
    'results-native' => node_view_multiple($nodes, 'pub_teaser', 0, $language->language),
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
  $languages = hwc_req_param($form_state, 'languages', array($language->language));
  $ret = array();
  if($form_state['input']) {
    if (($form_state['input']['languages']['en'] !== NULL)) {
      return $ret;
    }
  }
  else {
    if (in_array('en', $languages)) {
      return $ret;
    }
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
      list($lng, $nid) = explode('_', $result['id'], 2);
      $nids[] = $nid;
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

  $q = db_select('node', 'a')
    ->fields('a', array('nid', 'vid'))
    ->condition('type', 'practical_tool')
    ->condition('status', 1)
    ->orderBy('changed', 'DESC');
  $q->innerJoin('field_data_field_access_tool_link_fc', 'fc', 'a.nid = fc.entity_id AND a.vid = fc.revision_id');
  $q->innerJoin('field_data_field_available_languages', 'al', 'fc.field_access_tool_link_fc_value = al.entity_id AND fc.field_access_tool_link_fc_revision_id = al.revision_id');
  $q->condition('al.field_available_languages_value', 'en');
  if (!empty($relevant_for_ids)) {
    $q->innerJoin('field_data_field_segment', 'fs', 'fs.entity_id = a.nid AND fs.revision_id = a.vid');
    $q->condition('fs.field_segment_tid', $relevant_for_ids, 'IN');
  }
  $pnids = $q->execute()->fetchCol();
  $pnids = array_unique($pnids);

  $nids = array_intersect($nids, $pnids);

  $sort = hwc_req_param($form_state, 'sort');
  if ($sort == 'alphabetically') {
    _hwc_practical_tool_sort_nodes($nids);
  }
  
  $per_page = 2;
  $current_page = pager_default_initialize(count($nids), $per_page, 1);
  $page = array_chunk($nids, $per_page, TRUE);
  $nodes = node_load_multiple($page[$current_page]);
  if (empty($nodes)) {
    return array();
  }
  $languages = hwc_req_param($form_state, 'languages', array($language->language));
  foreach ($nodes as $node) {
    $node->filter_languages = $languages;
  }
  $languages = hwc_req_param($form_state, 'languages', array($language->language));
  $pager_params = array('languages' => $languages);
  if ($is_search) {
    $pager_params['text'] = $text;
  }
  $ret = array(
    '#prefix' => '<h2 class="h4-title">' . t('Other relevant tools in English') . '</h2>',
    'results-related' => node_view_multiple($nodes, 'pub_teaser', 0, $language->language),
    '#suffix' => theme('pager', array(
      'tags' => array('<', '<', '', '>', '>'),
      'quantity' => count($nodes),
      'parameters' => $pager_params,
      'element' => 1,
    )),
  );
  return $ret;
}

function hwc_practical_tool_menu_tools_get_query() {
  $server = search_api_server_load('solr_server');
  $index = search_api_index_load(SOLR_SEARCH_INDEX);
  $query = new SearchApiQuery($index);
  $query->fields(array()); // Avoid PHP notice
  $solr = new SearchApiSolrService($server);
  return array($solr, $query);
}
