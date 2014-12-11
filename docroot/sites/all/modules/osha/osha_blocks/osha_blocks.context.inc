<?php
/**
 * @file
 * osha_blocks.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function osha_blocks_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_latest_oshnews';
  $context->description = 'Where portlet Latest news is shown';
  $context->tag = '';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'blog' => 'blog',
        'seminar' => 'seminar',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
        'articles/blog' => 'articles/blog',
      ),
    ),
    'views' => array(
      'values' => array(
        'blog' => 'blog',
        'seminars' => 'seminars',
      ),
    ),
  );
  $context->reactions = array();
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Where portlet Latest news is shown');
  $export['context_latest_oshnews'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_newsletter';
  $context->description = 'Where to show newsletter and alerts portlets';
  $context->tag = '';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'blog' => 'blog',
        'calls' => 'calls',
        'events' => 'events',
        'highlight' => 'highlight',
        'news' => 'news',
        'seminar' => 'seminar',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
        'articles/careers' => 'articles/careers',
        'articles/procurement' => 'articles/procurement',
        'articles/blog' => 'articles/blog',
      ),
    ),
    'views' => array(
      'values' => array(
        'blog' => 'blog',
        'calls' => 'calls',
        'calls:page_1' => 'calls:page_1',
        'events' => 'events',
        'events:page' => 'events:page',
        'events_index' => 'events_index',
        'highlight' => 'highlight',
        'highlight:page' => 'highlight:page',
        'news' => 'news',
        'news:oshnews_list' => 'news:oshnews_list',
        'vacancies' => 'vacancies',
        'vacancies:page_1' => 'vacancies:page_1',
        'vacancies:page_2' => 'vacancies:page_2',
        'vacancies:page_3' => 'vacancies:page_3',
        'vacancies:page_4' => 'vacancies:page_4',
      ),
    ),
  );
  $context->reactions = array();
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Where to show newsletter and alerts portlets');
  $export['context_newsletter'] = $context;

  return $export;
}
