<?php

/**
 * Class MigrateOshaNews migrates news.txt contents. The data
 * is stored inside the <em>News</em> content type.
 */
class MigrateOshaFOPPages extends OSHADynamicMigration {

  /**
   * {@inheritdoc}
   */
  public function __construct($arguments) {
    parent::__construct(MigrateGroup::getInstance('OSHA Content types'));
    $this->description = 'Import "FOP Pages" contents from CSV file';

    /* Remove limits on time/memory, slower machines will fail */
    $this->timeLimit = 0;
    $this->memoryLimit = PHP_INT_MAX;

    $source_file = MigrationUtil::getSourceFile($arguments);
    $source_file_links = MigrationUtil::getSourceFileByKey($arguments, 'file_name_links');
    $this->source = new MigrateSourceList(
      new FOPPagesContentListCSV($source_file, $source_file_links),
      new FOPPagesContentItemCSV(),
      $this->fields()
    );

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'varchar',
          'length' => 200,
          'not null' => TRUE,
          'description' => 'Item code',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );

    $node_options = MigrateDestinationNode::options('en', 'full_html');
    $this->destination = new MigrateDestinationNode('fop_page', $node_options);

    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('field_archived', 'archived');
    $this->addFieldMapping('field_main_fop_url', 'main_fop_url');
    $this->addFieldMapping('created', 'creation_date');
    $this->addFieldMapping('changed', 'modification_date');
    $this->addFieldMapping('uid')->defaultValue(1);

    $this->addUnmigratedSources(array(
      'path',
      'language',
      'workflow_state',
      'creator',
      'country',
      'nace',
    ));

    $this->addUnmigratedDestinations(array(
      'promote',
      'status',
      'sticky',
      'revision',
      'log',
      'language',
      'tnid',
      'translate',
      'revision_uid',
      'is_new',
      'body:summary',
      'field_country',
      'field_image:language',
      'field_image:destination_dir',
      'field_image:alt',
      'field_publication_date:timezone',
      'field_publication_date:rrule',
      'field_publication_date:to',
      'field_summary',
      'field_summary:format',
      'field_tags:create_term',
      'field_tags:ignore_case',
      'field_thesaurus:create_term',
      'field_thesaurus:ignore_case',
      'field_link:title',
      'field_link:attributes',
      'field_fop_link_section',
      'comment',
    ));
  }

  /**
   * Migration machine name.
   *
   * {@inheritdoc}
   */
  protected function generateMachineName() {
    return OSHA_MIGRATION_CONTENT_TYPE_FOP_PAGES;
  }

  /**
   * Prepare raw data pulled from source.
   *
   * {@inheritdoc}
   */
  public function prepareRow($row) {
    if (MigrationUtil::entityRowValidator($row, $this) === FALSE) {
      return FALSE;
    }

    //format date according to UTC timezone
    $row->publication_date = MigrationUtil::getUTCTimestamp($row->publication_date);
    $row->expiration_date = MigrationUtil::getUTCTimestamp($row->expiration_date);
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
    parent::prepare($entity, $row);
    $migration = Migration::currentMigration();
    $languages = array_keys(language_list());
    $entity_type = $migration->getDestination()->getEntityType();
    $translation_handler = entity_translation_get_handler($entity_type, $entity);

    $entity->translations = $translation_handler->getTranslations();

    foreach ($languages as $language) {
      $has_translation = FALSE;
      if (!empty($row->title_field[$language])) {
        $entity->title_field[$language][0]['value'] = MigrationUtil::decodeHTMLText($row->title_field[$language]);
        $has_translation = TRUE;
      }
      if (!empty($row->description[$language])) {
        $entity->field_summary[$language][0]['value'] = MigrationUtil::decodeHTMLText($row->description[$language]);
        $entity->field_summary[$language][0]['format'] = 'full_html';
        $has_translation = TRUE;
      }
      if (!empty($row->text[$language])) {
        $entity->body[$language][0]['value'] = MigrationUtil::decodeHTMLText($row->text[$language]);
        $entity->body[$language][0]['format'] = 'full_html';
        $has_translation = TRUE;
      }

      if (!empty($row->country)) {
        $country = "";
        $iso2 = NULL;
        $countries = country_get_list();
        if (strlen($row->country) == 2) {
          // ISO2
          $iso2 = $row->country;
          if (!in_array($iso2, array_keys($countries))) {
            $iso2 = NULL;
          }
        }
        else {
          // Country name.
          if (!in_array($row->country, $countries)) {
            $iso2 = MigrationUtil::getNonStandardCountry($row->country);
            if ($iso2 != NULL) {
              // It's a non standard name.
              $country = $row->country;
            }
          }
        }

        if ($iso2 == NULL) {
          $this->displayMessage('Focal Points Pages - Country '
            . $row->country . ' not found', 'warning');
        }
        else {
          // Get the term or create it.
          $tid = MigrationUtil::getCountryTermByISO2($iso2);
          if (empty($tid)) {
            $voc = taxonomy_vocabulary_machine_name_load('country');
            $term = new stdClass();
            $term->vid = $voc->vid;
            if (empty($country)) {
              $country = $countries[$iso2];
            }
            $term->name = ucwords(strtolower($country));
            $term->field_iso2[LANGUAGE_NONE][0]['value'] = $iso2;
            taxonomy_term_save($term);
            $tid = $term->tid;
          }
          $entity->field_country[LANGUAGE_NONE][0] = array('tid' => $tid);
        }
      }

      $voc = taxonomy_vocabulary_machine_name_load('fop_link_sections');
      $entity->field_fop_link;
      $field_fop_link = array();
      // Attach field collection field_fop_link.
      if (is_array($row->field_fop_link)) {
        foreach($row->field_fop_link as $lang => $links) {
          foreach ($links as $link) {
            $field_collection_item = entity_create('field_collection_item', array('field_name' => 'field_fop_link'));
            $field_collection_item->setHostEntity('node', $entity, $lang);
            $field_collection_item->field_link[$lang][] = array(
              'title' => MigrationUtil::decodeHTMLText($link['title']),
              'url' => $link['url'],
            );
            if (!empty($link['section'])) {
              $term = taxonomy_get_term_by_name($link['section'], 'fop_link_sections');
              if (empty($term)) {
                $term = new stdClass();
                $term->vid = $voc->vid;
                $term->name = $link['section'];
                taxonomy_term_save($term);
              }
              else {
                $term = current($term);
              }
              $field_collection_item->field_fop_link_section[$lang][] = array('tid' => $term->tid);
            }
            $field_collection_item->save(TRUE);
            $field_fop_link[$lang][] = array(
              'value' => $field_collection_item->item_id,
              'revision_id' => $field_collection_item->revision_id,
            );
          }
        }
        $entity->field_fop_link = $field_fop_link;
      }
      if ($has_translation) {
        MigrationUtil::setTranslation($translation_handler, $entity, $row, $language);
      }
    }
  }

  /**
   * Return the list of available source fields.
   *
   * @return array
   *   An array o fields with their description
   */
  public function fields() {
    return array(
      'id' => 'Primary Key (URL pattern)',
      'path' => 'URL pattern without language',
      'language' => 'Row language',
      'workflow_state' => '',
      'creation_date' => '',
      'modification_date' => '',
      'publication_date' => '',
      'creator' => 'Author user id from the old website',
      'title' => '',
      'description' => '',
      'text' => 'Body of the news',
      'image' => 'Path to image file',
      'imageCaption' => 'Image tooltip',
      'subject' => 'Categories/Tags',
      'country' => '',
      'subcategory' => 'Merged into categories',
      'multilingual_thesaurus' => '',
      'nace' => 'Nace codes taxonomy',
      'archived' => '',
      'expiration_date' => '',
    );
  }

  public function rollback(array $key) {
    $idlist = $this->getOption('idlist');
    if ($idlist) {
      // Make the IDs keys, to more easily identify them
      $idlist = array_flip(explode(',', $idlist));
    }
    foreach ($this->map as $destination_key) {
      if (($return = $this->checkStatus()) != MigrationBase::RESULT_COMPLETED) {
        break;
      }
      if ($this->itemOptionExceeded()) {
        break;
      }
      $current_source_key = $this->map->getCurrentKey();
      // If there's an idlist, skip anything not in the list
      if ($idlist && !isset($idlist[$current_source_key['sourceid1']])) {
        continue;
      }
      // Delete the field_collections.
      try {
        if ($this->systemOfRecord == Migration::SOURCE) {
          // Skip when the destination key is null
          $skip = FALSE;
          foreach ($destination_key as $key_value) {
            if (is_null($key_value)) {
              $skip = TRUE;
              break;
            }
          }
          if (!$skip) {
            foreach ($this->extractFCIds($destination_key->destid1) as $id) {
              $field_collection_item = field_collection_item_load($id);
              if ($field_collection_item instanceof FieldCollectionItemEntity) {
                $field_collection_item->delete();
              }
            }
          }
        }
      }
      catch (Exception $e) {
        continue;
      }
    }
    parent::rollback();
  }

  public function extractFCIds($nid) {
    $ids = array();
    $node = node_load($nid);
    foreach ($node->field_fop_link as $lang => $links) {
      foreach ($links as $link) {
        if (!empty($link['value'])) {
          $ids[]= $link['value'];
        }
      }
    }
    return $ids;
  }
}

class FOPPagesContentListCSV extends MigrateList {
  protected $file = '';
  public static $data = array();

  /**
   * {@inheritdoc}
   */
  public function __construct($file, $file_links) {
    parent::__construct();
    $this->file = $file;
    $this->file_links = $file_links;
    $this->parseSourceFile();
  }

  /**
   * {@inheritdoc}
   */
  public function __toString() {
    return $this->file;
  }

  /**
   * Parse the CSV file and populate the local cache.
   */
  protected function parseSourceFile() {
    $handle = fopen($this->file, 'r');
    $fields = $raw_data = fgetcsv($handle, 1000, ';');
    self::$data = array();
    $work_flow_key = array_search('workflow_state', $fields);
    while (($raw_data = fgetcsv($handle, 100000, ';')) !== FALSE) {
      $language = !empty($raw_data[1]) ? $raw_data[1] : 'en';
      $path = MigrationUtil::getIDFromSourceRow($raw_data);
      // Ignore this page, it's migrated from pages.
      if ($path == 'oshnetwork/focal-points/index_html') {
        continue;
      }
      self::$data[$path]['id'] = $path;
      // Assign the workflow state of the row from english entry.
      if ($language == 'en') {
        self::$data[$path]['workflow_state'] = $raw_data[$work_flow_key];
      }
      // Skip the private translations.
      if (!in_array($raw_data[$work_flow_key],
        array('published', 'checked', 'to_amend'))) {
        continue;
      }
      foreach ($fields as $key => $field) {
        switch ($field) {
          case 'title':
            if ($language == 'en') {
              self::$data[$path]['title'] = MigrationUtil::decodeHTMLText($raw_data[$key]);
            }
            self::$data[$path]['title_field'][$language] = $raw_data[$key];
            break;

          case 'image':
          case 'aliases':
          case 'description':
          case 'text':
            self::$data[$path][$field][$language] = $raw_data[$key];
            break;

          default:
            if ($language == 'en') {
              self::$data[$path][$field] = $raw_data[$key];
            }
            break;
        }
      }
    }

    // Get links
    $handle_links = fopen($this->file_links, 'r');
    $raw_data_links = fgetcsv($handle_links, 1000, ';');
    while (($raw_data_links = fgetcsv($handle_links, 100000, ';')) !== FALSE) {
      $language = substr($raw_data_links[0], 1, 2);
      $path = substr($raw_data_links[0], 4);
      $link = array(
        'url' => $raw_data_links[3],
        'title' => $raw_data_links[2],
      );
      if ($language == 'en') {
        $link['title'] = $raw_data_links[1];
      }
      $link['section'] = $this->idToWords($raw_data_links[4]);
      if (isset(self::$data[$path])) {
        self::$data[$path]['field_fop_link'][$language][] = $link;
      }
    }
  }

  public function idToWords($string_id) {
    $word = str_replace('_', ' ', $string_id);
    $word = ucwords($word);
    return $word;
  }

  /**
   * {@inheritdoc}
   */
  public function getIdList() {
    if (empty(self::$data)) {
      $this->parseSourceFile();
    }
    return array_keys(self::$data);
  }

  /**
   * {@inheritdoc}
   */
  public function computeCount() {
    return count(self::$data);
  }
}

class FOPPagesContentItemCSV extends MigrateItem {

  /**
   * {@inheritdoc}
   */
  public function getItem($item_id) {
    if (array_key_exists($item_id, FOPPagesContentListCSV::$data)) {
      return (object) FOPPagesContentListCSV::$data[$item_id];
    }
    return NULL;
  }
}
