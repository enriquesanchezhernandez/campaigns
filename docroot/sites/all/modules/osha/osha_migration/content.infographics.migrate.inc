<?php

/**
 * Class MigrateOshaInfographics migrates infographics.txt contents. The data
 * is stored inside the <em>Infographics</em> content type.
 */
class MigrateOshaInfographics extends OSHADynamicMigration {

  /**
   * {@inheritdoc}
   */
  public function __construct($arguments) {
    parent::__construct(MigrateGroup::getInstance('OSHA Content types'));
    $this->description = 'Import "Infographics" contents from CSV file';

    /* Remove limits on time/memory, slower machines will fail */
    $this->timeLimit = 0;
    $this->memoryLimit = PHP_INT_MAX;

    $data_path = osha_migration_get_data_dir();
    $source_file = MigrationUtil::getSourceFile($arguments);
    $this->source = new MigrateSourceList(
      new InfographicsContentListCSV($source_file),
      new InfographicsContentItemCSV(),
      $this->fields()
    );

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'int',
          'not null' => TRUE,
          'description' => 'Id',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );

    $node_options = MigrateDestinationNode::options('en', 'full_html');
    $this->destination = new MigrateDestinationNode(OSHA_INFOGRAPHIC_CONTENT_TYPE_INFOGRAPHIC, $node_options);

    $this->addFieldMapping('title', 'title');

    $this->addFieldMapping('field_image', 'image');
    $this->addFieldMapping('field_image:file_replace')->defaultValue(FILE_EXISTS_REPLACE);
    $this->addFieldMapping('field_image:file_class')->defaultValue('OSHAMigrateFileUri');
    $this->addFieldmapping('field_image:preserve_files')->defaultValue(TRUE);
    $this->addFieldMapping('field_image:source_dir')->defaultValue($data_path . '/export-local/infographics');
    $this->addFieldMapping('field_image:destination_file', 'image');
    $this->addFieldMapping('field_image:multilingual')->defaultValue(TRUE);

    $this->addFieldMapping('field_file', 'file');
    $this->addFieldMapping('field_file:file_replace')->defaultValue(FILE_EXISTS_REPLACE);
    $this->addFieldMapping('field_file:file_class')->defaultValue('OSHAMigrateFileUri');
    $this->addFieldmapping('field_file:preserve_files')->defaultValue(TRUE);
    $this->addFieldMapping('field_file:source_dir')->defaultValue($data_path . '/export-local/infographics');
    $this->addFieldMapping('field_file:destination_file', 'file');
    $this->addFieldMapping('field_file:multilingual')->defaultValue(TRUE);

    $this->addFieldMapping('uid')->defaultValue(1);
    $this->addFieldMapping('field_publication_date')->defaultValue(time());
    $this->addFieldMapping('status')->defaultValue(1);

    $this->addUnmigratedSources(array(
      //'path',
      //'language',
      'workflow_state',
    ));

    $this->addUnmigratedDestinations(array(
      'promote',
      'sticky',
      'revision',
      'log',
      'language',
      'tnid',
      'translate',
      'revision_uid',
      'is_new',
      'body:summary',
      'field_image:language',
      'field_image:destination_dir',
      'field_file:language',
      'field_file:destination_dir',
      'field_image:alt',
      'field_publication_date:timezone',
      'field_publication_date:rrule',
      'field_publication_date:to',
      'comment',
    ));
  }

  /**
   * Migration machine name.
   *
   * {@inheritdoc}
   */
  protected function generateMachineName() {
    return OSHA_MIGRATION_CONTENT_TYPE_INFOGRAPHICS;
  }

  /**
   * Prepare raw data pulled from source.
   *
   * {@inheritdoc}
   */
  public function prepareRow($row) {
    if(MigrationUtil::entityRowValidator($row, $this) === FALSE) {
      return FALSE;
    }

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
      'id' => 'Primary Key',
      'path' => 'URL pattern without language',
      'language' => 'Row language',
      'title' => 'Title',
      'image' => 'Path to image file',
      'file' => '',
      'workflow_state' => ''
    );
  }
}

class InfographicsContentListCSV extends MigrateList {
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
    if (!is_readable($this->file)) {
      return array();
    }
    $handle = fopen($this->file, 'r');
    $fields = $raw_data = fgetcsv($handle, 1000, ';');
    self::$data = array();
    $work_flow_key = array_search('workflow_state', $fields);
    while (($raw_data = fgetcsv($handle, 100000, ';')) !== FALSE) {
      $language = !empty($raw_data[1]) ? $raw_data[1] : 'en';
      $path = $raw_data[0];

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
            self::$data[$path][$field][$language] = strtoupper($raw_data[1]).'/png/infographic_'.$raw_data[0].'_'.strtoupper($raw_data[1]).'_v1.0.png';
            break;
          case 'file':
            self::$data[$path][$field][$language] = strtoupper($raw_data[1]).'/pdf/infographic_'.$raw_data[0].'_'.strtoupper($raw_data[1]).'_v1.0.pdf';
            break;

          case 'path':
            if ($language == 'en') {
              $url = $raw_data[2];
            }
            self::$data[$path][$field][$language] = urlencode($url);
            break;

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

class InfographicsContentItemCSV extends MigrateItem {

  /**
   * {@inheritdoc}
   */
  public function getItem($item_id) {
    if (array_key_exists($item_id, InfographicsContentListCSV::$data)) {
      return (object) InfographicsContentListCSV::$data[$item_id];
    }
    return NULL;
  }
}