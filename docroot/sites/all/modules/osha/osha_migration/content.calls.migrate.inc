<?php

/**
 * Class MigrateOshaCalls migrates calls.txt contents. The data
 * is stored inside the <em>Calls</em> content type.
 */
class MigrateOshaCalls extends OSHADynamicMigration {

  /**
   * {@inheritdoc}
   */
  public function __construct($arguments) {
    parent::__construct(MigrateGroup::getInstance('OSHA Content types'));
    $this->description = 'Import "Calls" contents from CSV file';

    /* Remove limits on time/memory, slower machines will fail */
    $this->timeLimit = 0;
    $this->memoryLimit = PHP_INT_MAX;

    $source_file = MigrationUtil::getSourceFile($arguments);
    $this->source = new MigrateSourceList(
      new CallsMigrateList($source_file),
      new CallsMigrateItem(),
      $this->fields()
    );

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'Item code',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );

    $node_options = MigrateDestinationNode::options('en', 'full_html');
    $this->destination = new MigrateDestinationNode(OSHA_CALLS_CONTENT_TYPE_CALLS, $node_options);

    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('field_calls_deadline', 'deadline');
    $this->addFieldMapping('field_publication_date', 'publication_date');
    $this->addFieldMapping('field_archived', 'archived');
    $this->addFieldMapping('field_expiration_date', 'expiration_date');

    $this->addFieldMapping('field_related_resources', 'files');
    $this->addFieldMapping('field_related_resources:file_class')->defaultValue('OSHAMigrateFileUri');
    $this->addFieldmapping('field_related_resources:preserve_files')->defaultValue(TRUE);
    $this->addFieldMapping('field_related_resources:file_replace')->defaultValue(FILE_EXISTS_REPLACE);
    $this->addFieldMapping('field_related_resources:source_dir')->defaultValue(osha_migration_get_data_dir() . '/export/');
    $this->addFieldMapping('field_related_resources:destination_file', OSHA_MIGRATION_REPLACED_PATH_PREFIX . 'files');
    $this->addFieldMapping('field_related_resources:multilingual')->defaultValue(TRUE);

    $this->addFieldMapping('created', 'creation_date');
    $this->addFieldMapping('changed', 'modification_date');
    $this->addFieldMapping('uid')->defaultValue(1);

    $this->addUnmigratedSources(array(
      'path',
      'language',
      'workflow_state',
      'field_title',
      'info',
      'description',
      'text',
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
      'body',
      'body:format',
      'body:language',
      'field_author',
      'field_author:language',
      'comment',
      'field_related_resources:language',
      'field_related_resources:destination_dir',
      'field_related_resources:description',
      'title_field',
      'title_field:language',
      'path',
    ));
  }

  /**
   * Migration machine name.
   *
   * {@inheritdoc}
   */
  protected function generateMachineName() {
    return OSHA_MIGRATION_CONTENT_TYPE_CALLS;
  }

  /**
   * Prepare raw data pulled from source.
   *
   * {@inheritdoc}
   */
  public function prepareRow($row) {
    $row->language = "en";
    if (MigrationUtil::entityRowValidator($row, $this) === FALSE) {
      return FALSE;
    }

    //format publication date according to UTC timezone
    $row->publication_date = MigrationUtil::getUTCTimestamp($row->publication_date);

    MigrationUtil::cleanMigratedFileField($row, 'files', 'public://calls/documents');
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
      if (!empty($entity->field_related_resources[$language])) {
        // Attach field_description to the file.
        foreach ($entity->field_related_resources[$language] as $idx => &$file) {
          $file['description'] = $row->file_description[$language][$idx];
        }
        $has_translation = TRUE;
      }
      if (!empty($row->author[$language])) {
        $entity->field_author[$language][0]['value'] = MigrationUtil::decodeHTMLText($row->author[$language]);
        $has_translation = TRUE;
      }
      if (!empty($row->text[$language])) {
        $entity->body[$language][0]['value'] = MigrationUtil::decodeHTMLText($row->text[$language]);
        $entity->body[$language][0]['format'] = 'full_html';
        $has_translation = TRUE;
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
      'title' => '',
      'files' => 'Attached files',
      'file_description' => 'File description (category)',
      'field_title' => '',
      'info' => '',
      'deadline' => '',
      'creator' => 'Author user id from the old website',
      'description' => '',
      'text' => 'Body of the case study',
      'archived' => '',
      'expiration_date' => '',
    );
  }
}

class CallsMigrateList extends MigrateList {
  protected $file = '';
  public static $data = array();

  /**
   * {@inheritdoc}
   */
  public function __construct($file) {
    parent::__construct();
    $this->file = $file;
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
    $fields = $raw_data = fgetcsv($handle, NULL, ';');
    $work_flow_key = array_search('workflow_state', $fields);

    self::$data = array();
    while (($raw_data = fgetcsv($handle, NULL, ';')) !== FALSE) {
      $language = !empty($raw_data[1]) ? $raw_data[1] : 'en';
      $path = MigrationUtil::getIDFromSourceRow($raw_data);
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
        if (empty($raw_data[$key])) {
          continue;
        }
        switch ($field) {
          case 'title':
            if ($language == 'en') {
              self::$data[$path]['title'] = MigrationUtil::decodeHTMLText($raw_data[$key]);
            }
            self::$data[$path]['title_field'][$language] = MigrationUtil::decodeHTMLText($raw_data[$key]);
            break;

          case 'contract_notice':
            self::$data[$path]['files'][$language][] = $raw_data[$key];
            $term = taxonomy_get_term_by_name('Contract notice', 'attachment_file_type');
            self::$data[$path]['file_description'][$language][] = empty($term) ? 'Contract notice' : current(array_keys($term));
            break;

          case 'contract_notice_corrigendum':
            self::$data[$path]['files'][$language][] = $raw_data[$key];
            $term = taxonomy_get_term_by_name('Contract Notice Corrigendum', 'attachment_file_type');
            self::$data[$path]['file_description'][$language][] = empty($term) ? 'Contract Notice Corrigendum' : current(array_keys($term));
            break;

          case 'technical_specifications':
            self::$data[$path]['files'][$language][] = $raw_data[$key];
            $term = taxonomy_get_term_by_name('Technical Specs', 'attachment_file_type');
            self::$data[$path]['file_description'][$language][] = empty($term) ? 'Technical Specs' : current(array_keys($term));
            break;

          case 'amendments':
            self::$data[$path]['files'][$language][] = $raw_data[$key];
            $term = taxonomy_get_term_by_name('Amendments', 'attachment_file_type');
            self::$data[$path]['file_description'][$language][] = empty($term) ? 'Amendments' : current(array_keys($term));
            break;

          case 'agency_responses':
            self::$data[$path]['files'][$language][] = $raw_data[$key];
            $term = taxonomy_get_term_by_name('Clarifications to questions', 'attachment_file_type');
            self::$data[$path]['file_description'][$language][] = empty($term) ? 'Clarifications to questions' : current(array_keys($term));
            break;

          case 'award_notice':
            self::$data[$path]['files'][$language][] = $raw_data[$key];
            $term = taxonomy_get_term_by_name('Award Notice', 'attachment_file_type');
            self::$data[$path]['file_description'][$language][] = empty($term) ? 'Award Notice' : current(array_keys($term));
            break;

          case 'award_notice_corrigendum':
            self::$data[$path]['files'][$language][] = $raw_data[$key];
            $term = taxonomy_get_term_by_name('Award Notice Corrigendum', 'attachment_file_type');
            self::$data[$path]['file_description'][$language] = empty($term) ? 'Award Notice Corrigendum' : current(array_keys($term));
            break;

          case 'aliases':
          case 'author':
          case 'text':
            self::$data[$path][$field][$language] = $raw_data[$key];
            break;

          case 'path':
            $path_language = explode('/', $raw_data[$key], 3);
            self::$data[$path][$field][$language] = $path_language[2];
            continue;

          default:
            if ($language == 'en') {
              self::$data[$path][$field] = $raw_data[$key];
            }
            break;
        }
      }
    }
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

class CallsMigrateItem extends MigrateItem {

  /**
   * {@inheritdoc}
   */
  public function getItem($item_id) {
    if (array_key_exists($item_id, CallsMigrateList::$data)) {
      return (object) CallsMigrateList::$data[$item_id];
    }
    return NULL;
  }
}
