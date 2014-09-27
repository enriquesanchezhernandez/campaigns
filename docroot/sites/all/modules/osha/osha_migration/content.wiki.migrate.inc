<?php

class OshaMigrateWiki extends DynamicMigration {

  /**
   * {@inheritdoc}
   */
  public function __construct($arguments) {
    parent::__construct(MigrateGroup::getInstance('OSHA Wiki'));
    $this->arguments = $arguments;
    $this->description = 'Import wiki articles from oshawiki.eu';

    $url = variable_get('wiki_query_url', FALSE);
    if (!$url) {
      drupal_set_message('Wiki migration: Query URL variable set to default. Use drush vset to override the value');
      $url = 'http://oshwiki.eu/index.php?title=Special%3AAsk&q=%5B%5B%3A%2B%5D%5D&po=%3FModification+date%0D%0A%3FCategory%0D%0A%3FMaster+page%0D%0A%3FModification+date%0D%0A%3FLanguage+code%0D%0A%3FNP%0D%0A%3FOP%0D%0A&eq=yes&p%5Bformat%5D=json&sort_num=&order_num=ASC&p%5Blink%5D=subject&p%5Bsort%5D=Modification+date&p%5Border%5D%5Bdesc%5D=1&p%5Bheaders%5D=show&p%5Bmainlabel%5D=&p%5Bintro%5D=&p%5Boutro%5D=&p%5Bsearchlabel%5D=&p%5Bdefault%5D=&p%5Bsyntax%5D=standard&eq=yes';
    }
    $this->source = new OshaMigrateSourceWiki($url, array(
        'skip_count' => TRUE,
      )
    );
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'title' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'Wiki page title',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );

    $this->destination = new MigrateDestinationNode(OSHA_WIKI_CONTENT_TYPE);

    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('title_field', 'title');
    $this->addFieldMapping('language', 'language');
    $this->addFieldMapping('field_summary', 'summary');
    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping('field_wiki_page_url', 'url');
    $this->addFieldMapping('field_wiki_categories', 'categories');
    $this->addFieldMapping('field_wiki_categories:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_updated', 'updated');
  }

  /**
   * {@inheritdoc}
   */
  protected function generateMachineName() {
    return OSHA_MIGRATION_CONTENT_TYPE_WIKI;
  }

  /**
   * {@inheritdoc}
   */
  public function prepareRow($row) {
    $row->categories = MigrationUtil::findTidByTaxonomyField($row->categories, 'name_field', OSHA_TAXONOMIES_WIKI_CATEGORIES, 'en');
    return TRUE;
  }

  /**
   * Called by destination right before saving.
   *
   * @param object $entity
   *   Entity to save
   * @param object $row
   *   Source row
   */
  public function prepare($entity, $row) {
    $migration = Migration::currentMigration();
    $languages = array_keys(language_list());
    $entity_type = $migration->getDestination()->getEntityType();

    $translation_handler = entity_translation_get_handler($entity_type, $entity);
    $entity->translations = $translation_handler->getTranslations();

    foreach ($languages as $language) {
      $has_translation = FALSE;
      if (!empty($row->ml_title_field[$language])) {
        $entity->title_field[$language][0]['value'] = MigrationUtil::decodeHTMLText($row->ml_title_field[$language]);
        $has_translation = TRUE;
      }
      if (!empty($row->ml_body[$language])) {
        $entity->body[$language][0]['value'] = MigrationUtil::decodeHTMLText($row->ml_body[$language]);
        $entity->body[$language][0]['format'] = 'full_html';
        $has_translation = TRUE;
      }
      if (!empty($row->ml_summary[$language])) {
        $entity->field_summary[$language][0]['value'] = MigrationUtil::decodeHTMLText($row->ml_summary[$language]);
        $entity->field_summary[$language][0]['format'] = 'full_html';
        $has_translation = TRUE;
      }
      if (!empty($row->ml_url[$language])) {
        $entity->field_wiki_page_url[$language][0]['url'] = $row->ml_url[$language];
        $has_translation = TRUE;
      }
      if ($has_translation) {
        MigrationUtil::setTranslation($translation_handler, $entity, $row, $language);
      }
    }
  }
}


class OshaMigrateSourceWiki extends MigrateSource {

  protected static $templateUrl = 'http://oshwiki.eu/index.php?title=Special%3AAsk&q=%5B%5B%3A%2B%5D%5D&po=%3FModification+date%0D%0A%3FCategory%0D%0A%3FMaster+page%0D%0A%3FModification+date%0D%0A%3FLanguage+code%0D%0A%3FNP%0D%0A%3FOP%0D%0A&eq=yes&p%5Bformat%5D=json&sort_num=&order_num=ASC&p%5Blimit%5D=5&p%5Boffset%5D=2&p%5Blink%5D=subject&p%5Bsort%5D=Modification+date&p%5Border%5D%5Bdesc%5D=1&p%5Bheaders%5D=show&p%5Bmainlabel%5D=&p%5Bintro%5D=&p%5Boutro%5D=&p%5Bsearchlabel%5D=&p%5Bdefault%5D=&p%5Bsyntax%5D=standard&p%5Bprettyprint%5D=1&eq=yes';
  protected $url;
  protected $serviceQueried = FALSE;
  protected $data = array();

  /**
   * {@inheritdoc}
   */
  public function __construct($url, array $options = array()) {
    parent::__construct($options);
    $this->url = $url;
  }

  /**
   * Return a string representing the source, for display in the UI.
   */
  public function __toString() {
    return t(
      "Extract pages from wiki using semantic search and JSON export. Handles pagination. Query example: <a target='_blank' href='!url'>Open</a>",
      array('!url' => self::$templateUrl)
    );
  }

  /**
   * The list of available fields to map from the source, keyed by field name.
   */
  public function fields() {
    return array(
      'title' => t('Wiki english page title'),
      'language' => t('Language code'),
      'summary' => t('Wiki page summary'),
      'body' => t('Wiki page content localized'),
      'url' => t('Page URL'),
      'categories' => t('Wiki categories'),
      'updated' => t('Date when page was last modified'),
      // 'nace' => t('Nace codes'),
      // 'thesaurus' => t('Thesaurus codes'),
    );
  }

  /**
   * Return the number of available source records.
   */
  public function computeCount() {
    // @todo pre-search for all records without fields to compute all nodes for pagination.
    return 0;
  }

  /**
   * Do whatever needs to be done to start a fresh traversal of the source data.
   *
   * This is always called at the start of an import, so tasks such as opening
   * file handles, running queries, and so on should be performed here.
   */
  public function performRewind() {
    reset($this->data);
  }

  /**
   * Fetch the next row of data, returning it as an object.
   *
   * @return object
   *   FALSE data as stdClass, FALSE when there is no more data available.
   */
  public function getNextRow() {
    if (empty($this->data)) {
      $this->pullRemoteData();
    }
    return next($this->data);
  }

  /**
   * Query the remote source and pull the data.
   */
  protected function pullRemoteData() {
    /* @todo Implement remote filtering
     * $last = variable_get('osha_wiki_last_migration', FALSE)
     * Send this filter so only pull the content created/updated after this date
     */
    if (!$this->serviceQueried) {
      $this->data = array();
      $this->serviceQueried = TRUE;
      $local_latest_date = $this->getLatestItemDate();

      $pretty_print = TRUE;
      $base_url = $this->url;
      if ($pretty_print) {
        $base_url .= '&p%5Bprettyprint%5D=1';
      }
      // Result offset and page size.
      $page_size = variable_get('osha_wiki_migration_pagesize', 25);
      $base_url .= '&p%5Blimit%5D=' . $page_size;

      $page = 0;
      while (TRUE) {
        $page++;
        try {
          $this->setMessage("Processing results page $page", MigrationBase::MESSAGE_INFORMATIONAL);
          $url = $base_url . '&p%5Boffset%5D=' . ($page * $page_size);
          $content = file_get_contents($url);
          $content = json_decode($content, TRUE);
          if (!empty($content['results'])) {
            if (!$this->processRemoteResultsPage($content['results'], $local_latest_date)) {
              $this->setMessage("Finished at page #$page because we hit the oldest item", MigrationBase::MESSAGE_WARNING);
              break;
            }
          }
          else {
            $this->setMessage("Finished at page #$page due to empty results", MigrationBase::MESSAGE_WARNING);
            break;
          }
        }
        catch(Exception $e) {
          $msg = sprintf('Exception while retrieving remote wiki data for page %s (%s) ', $page, $e->getMessage());
          $this->setMessage($msg, MigrationBase::MESSAGE_ERROR);
          break;
        }
      }
    }
  }

  /**
   * Process the list of results from the remote service.
   *
   * @param array $results
   *   List of JSON objects.
   *
   * @return bool
   *   Return FALSE if we hit the oldest item
   */
  protected function processRemoteResultsPage($results, $local_latest_date) {
    $ret = TRUE;
    foreach ($results as $key => $data) {
      if ($this->validateDataRow($key, $data)) {
        $page_id = str_replace('//oshwiki.eu/wiki/', '', $data['fullurl']);
        $url = 'http:' . $data['fullurl'];
        $parent = $data['printouts']['Master page'][0]['fulltext'];
        $language = $data['printouts']['Language code'][0];

        // Deal with translations.
        if ($language != 'en') {
          if (array_key_exists($parent, $this->data)) {
            $ob = $this->data[$parent];
          }
          else {
            $ob = new stdClass();
            $ob->title = $key;
            $ob->language = $language;
            $ob->translations[] = $language;
          }
        }
        else {
          $ob = new stdClass();
          $ob->language = 'en';
          $ob->title = $key;
        }
        $body = $this->getWikiPageContent($page_id);
        $ob->ml_body[$language] = $body;
        $ob->ml_summary[$language] = $this->getWikiSummaryFromBody($body);
        $ob->categories = array();
        if ($language == 'en' && !empty($data['printouts']['Category'])) {
          foreach ($data['printouts']['Category'] as $cat_data) {
            $cat_name = str_replace('Category:', '', $cat_data['fulltext']);
            $ob->categories[] = $cat_name;
          }
        }
        $ob->ml_title_field[$language] = $key;

        $ob->updated = '';
        if (!empty($data['printouts']['Modification date'][0])) {
          $updated = $data['printouts']['Modification date'][0];
          $ob->updated = $updated;
          if ($updated < $local_latest_date) {
            $ret = FALSE;
          }
        }
        $ob->ml_url[$language] = $url;
        // @todo Add fields
        // $ob->nace = '';
        // $ob->thesaurus = '';
        if ($language == 'en') {
          if ($ob->updated > $local_latest_date) {
            $this->data[$parent] = $ob;
          }
        }
      }
    }
    return $ret;
  }

  /**
   * Extract the summary text for the wiki page from the body.
   *
   * @param string $body
   *   Text containing the body.
   *
   * @return string
   *   Summary text to add into field_summary
   */
  protected function getWikiSummaryFromBody($body) {
    $summary = '';
    if (strlen($body)) {
      $summary = explode('\n', $body);
      $summary = array_filter($summary);
      $summary = array_slice($summary, 0, 5);
      foreach ($summary as &$line) {
        $line = preg_replace('/==/', '<h2>', $line, 1);
        $line = preg_replace('/==/', '</h2>', $line, 1);
      }
      $summary = implode('\n', $summary);
    }
    return $summary;
  }

  /**
   * Retrieve the latest timestamp for wiki pages from field_updated.
   * @return string
   *   Returns empty or date to filter the content by.
   * @throws EntityFieldQueryException
   */
  public function getLatestItemDate() {
    $ret = NULL;
    $query = new EntityFieldQuery();
    $result = $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'wiki_page')
      ->fieldOrderBy('field_updated', 'value', 'DESC')
      ->execute();
    if (isset($result['node'])) {
      $latest_id = current($result['node']);
      $latest = node_load($latest_id->nid);
      if (!empty($latest->field_updated[LANGUAGE_NONE][0]['value'])) {
        $ret = $latest->field_updated[LANGUAGE_NONE][0]['value'];
        $ret = strtotime($ret);
      }
    }
    return $ret;
  }

  function getWikiPageContent($page_id) {
    $url = sprintf('http://oshwiki.eu/api.php?action=parse&format=json&prop=wikitext&page=%s', $page_id);
    $data = drupal_http_request($url);
    if (isset($data) && $data->code == 200) {
      $content = json_decode($data->data, TRUE);
      if (!empty($content['parse']['wikitext']['*'])) {
        $text = $content['parse']['wikitext']['*'];
        if($pos = strpos($text, "==")) {
          $text = substr($text, $pos);
        }
        return $text;
      }
    }
    return '';
  }

  /**
   * Add messages during data retrieval for debugging.
   *
   * @param string $msg
   *   Message string
   * @param int $severity
   *   Migration message level
   */
  protected function setMessage($msg, $severity = MigrationBase::MESSAGE_WARNING) {
    drupal_set_message($msg);
    $this->activeMigration->queueMessage($msg, $severity);
  }

  /**
   * Check if row is importable.
   *
   * @param string $key
   *   Page title
   * @param array $data
   *   Actual data to validate
   *
   * @return bool
   *   TRUE if data is valid
   */
  protected function validateDataRow($key, $data) {
    if (empty($data['printouts']['Language code'][0])) {
      $this->setMessage('Skipping record without language: ' . $key);
      return FALSE;
    }
    if (empty($data['printouts']['Master page'][0]['fulltext'])) {
      $this->setMessage('Skipping record without title: ' . $key);
      return FALSE;
    }
    if (empty($data['fullurl'])) {
      $this->setMessage('Skipping record URL: ' . $key);
      return FALSE;
    }
    $parent = $data['printouts']['Master page'][0]['fulltext'];
    if ($data['printouts']['Language code'][0] != 'en' && empty($parent)) {
      $this->setMessage('Translation has no parent page: ' . $key);
      return FALSE;
    }
    return TRUE;
  }
}