<?php

define('OSHA_MIGRATE_FILES_DEST_DIR', 'public://files');
/**
 * Class MigrateOshaPublicationFiles
 */
class OshaMigrateFiles extends DynamicMigration {

  /**
   * {@inheritdoc}
   */
  public function __construct($arguments) {
    parent::__construct();
    $this->description = t('Imports files needed bt publication');
    $this->dependencies = array(
//      OSHA_MIGRATION_TAXONOMY_TAGS,
      OSHA_MIGRATION_TAXONOMY_THESAURUS,
      OSHA_MIGRATION_TAXONOMY_NACE_CODES,
    );

    /* Remove limits on time/memory, slower machines will fail */
    $this->timeLimit = 0;
    $this->memoryLimit = PHP_INT_MAX;

    $file_name = NULL;
    if (isset($arguments['file_name'])) {
      $file_name = $arguments['file_name'];
    }

    // Set bundle document.
    $this->destination = new MigrateDestinationFile('document', 'MigrateFileUri');

    $source_file = MigrationUtil::getSourceFile($arguments);

    $this->source = new MigrateSourceList(new OshaMigrateFilesListCSV($source_file),
      new OshaMigrateFilesItemCSV(osha_migration_get_data_dir(OSHA_MIGRATION_EXPORT_DIRECTORY)), $this->destination->fields());

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'File old path',
        ),
      ),
      MigrateDestinationFile::getKeySchema()
    );

    $this->addFieldMapping('source_dir')->defaultValue(osha_migration_get_data_dir(OSHA_MIGRATION_EXPORT_DIRECTORY));
    $this->addFieldMapping('destination_file', OSHA_MIGRATION_REPLACED_PATH_PREFIX . 'file');
    $this->addFieldMapping('value', 'file_uri');
    $this->addFieldMapping('destination_dir')->defaultValue(OSHA_MIGRATE_FILES_DEST_DIR);
    $this->addFieldMapping('preserve_files')->defaultValue(FALSE);
    $this->addFieldMapping('file_replace')->defaultValue(FILE_EXISTS_REPLACE);
    $this->addFieldMapping('timestamp', 'timestamp');
    $this->addFieldMapping('filename', 'title');

    $this->addFieldMapping('field_file_description', 'description');

    $this->addFieldMapping('field_tags', 'subject');
    $this->addFieldMapping('field_tags:source_type')->defaultValue('tid');

    $this->addFieldMapping('field_thesaurus', 'multilingual_thesaurus');
    $this->addFieldMapping('field_thesaurus:source_type')->defaultValue('tid');

    $this->addFieldMapping('field_nace_codes', 'nace');
    $this->addFieldMapping('field_nace_codes:source_type')->defaultValue('tid');

    $this->addUnmigratedDestinations(
      array(
        'field_nace_codes:create_term',
        'field_nace_codes:ignore_case',
        'field_tags:create_term',
        'field_tags:ignore_case',
        'field_thesaurus:create_term',
        'field_thesaurus:ignore_case',
      )
    );

  }

  /**
   * {@inheritdoc}
   */
  protected function generateMachineName() {
    return OSHA_MIGRATION_FILES;
  }

  /**
   * Prepares the source row before migration.
   *
   * @param object $row
   *   One source $row as returned by getItem
   *
   * @return bool
   *   TRUE if row is valid
   */
  public function prepareRow($row) {
    $row->file_uri = $row->file;
    $row->timestamp = time();

    $tags = $row->subject . ',' . $row->subcategory;
    $row->subject = MigrationUtil::decodeTagsTerms($tags);
    $row->multilingual_thesaurus = MigrationUtil::findTidByTaxonomyField(
      explode(',', $row->multilingual_thesaurus),
      'field_thesaurus_code',
      OSHA_TAXONOMIES_THESAURUS
    );
    if (!empty($row->nace) || $row->nace == '0') {
      $row->nace = explode(',', $row->nace);
      $row->nace = MigrationUtil::findTidByTaxonomyField(
        $row->nace,
        'field_nace_code',
        OSHA_TAXONOMIES_NACE_CODES
      );
    }
    $destination = MigrationUtil::cleanMigratedFile($row, 'file', OSHA_MIGRATE_FILES_DEST_DIR);
    if (empty($destination)) {
      return FALSE;
    }
    if (!is_file(osha_migration_get_data_dir(OSHA_MIGRATION_EXPORT_DIRECTORY) . $row->file)) {
      $this->saveMessage("File could not be found, ignoring {$row->file}", MigrationBase::MESSAGE_WARNING);
      return FALSE;
    }
    return TRUE;
  }

  public function prepare($entity, $row) {
    $entity->path['pathauto'] = 0;
    $file_language = (!empty($row->language)) ? $row->language : 'en';
    $entity->field_language[LANGUAGE_NONE][0]['value'] = $file_language;
    if (!empty($row->title)) {
      $entity->filename = $row->title;
    }
  }

  /**
   * Sets the node aliases after the migration, nid is available.
   *
   * @param object $entity
   *   Entity to be saved
   * @param object $row
   *   Source row
   */
  public function complete($entity, $row) {
    $language = $entity->field_language[LANGUAGE_NONE][0]['value'];
    $path = $row->path;
    if (substr($path, 2, 1) == '/') {
      // Assume path starts with /LL/, so remove language.
      $path = substr($path, 1, 3);
    }
    else {
      // Remove only first /
      $path = substr($path, 1);
    }
    // Existing Path.
    $conditions = array(
      'source' => 'file/' . $entity->fid,
      'language' => $language,
    );
    $existing_path = path_load($conditions);
    // New Path.
    $args = array(
      'source' => 'file/' . $entity->fid,
      'alias' => $path,
      'language' => $language,
    );
    if (empty($existing_path)) {
      // Save the path.
      path_save($args);
    }
    elseif (!empty($existing_path) && $existing_path['alias'] != $path) {
      // If path is changed, move existing to redirect and save the new one.
      path_delete($conditions);
      while (path_load($conditions)) {
        path_delete($conditions);
      }
      $source_redirects = redirect_load_by_source($existing_path['alias'], $language);
      if ($source_redirects == FALSE) {
        $redirect = new stdClass();
        $redirect->source = $existing_path['alias'];
        $redirect->source_options = array();
        $redirect->redirect = 'file/' . $entity->fid;
        $redirect->redirect_options = array();
        $redirect->status_code = 0;
        $redirect->type = 'redirect';
        $redirect->language = $language;
        redirect_save($redirect);
      }
      path_save($args);
    }

    // Add usage to prevent file removal when revert Publication migration.
    file_usage_add($entity, 'osha_migration_file', 'file_entity', $entity->fid);

//    //check if source redirect exists
//    $source = $path . '/view';
//    $source_redirects = redirect_load_by_source($source,$language);
//
//    if ($source_redirects == FALSE) {
//      // create redirect from file's/view path to file's path
//      $redirect = new stdClass();
//      $redirect->source = $source;                                   // From URL
//      $redirect->source_options = array();
//      $redirect->redirect = 'file/'.$entity->fid;                    // To URL
//      $redirect->redirect_options = array();
//      $redirect->status_code = 0;                                    // Redirect Status
//      $redirect->type = 'redirect';
//      $redirect->language = $language;
//
//      // Create the redirect
//      redirect_save($redirect);
//    }
  }
  protected function postRollback() {
    parent::postRollback();
    db_delete('file_usage')->condition('module', 'osha_migration_file');
  }
}

class OshaMigrateFilesListCSV extends MigrateList {

  protected $fileUrl = '';
  protected $multilingualFields;
  public static $csvData;

  /**
   * Populates csvData with parsed information from $file_url.
   *
   * @param string $file_url
   *   The location of the file with source raw data
   */
  public function __construct($file_url) {
    parent::__construct();
    $this->fileUrl = $file_url;

    self::$csvData = $this->parseMultilingualCSV($this->fileUrl);
  }

  /**
   * Returns the file url.
   *
   * @return string
   *   The file url
   */
  public function __toString() {
    return $this->fileUrl;
  }

  /**
   * Parses the csv $file and molds the data, to best suit our needs.
   *
   * The data is cached
   *
   * @param string $file
   *   The csv file url
   *
   * @return array
   *   Returns assoc array of assoc arrays which represents one source row
   *   array[id][field] -- row
   */
  protected function parseMultilingualCSV($file) {
    $handle = fopen($file, 'r');
    $fields = $data = fgetcsv($handle, 1000, ';');
    $final = array();
    while (($data = fgetcsv($handle, 100000, ';')) !== FALSE) {
      $row_id = $data[0];
      foreach ($fields as $key => $field) {
        $final[$row_id][$field] = $data[$key];
      }
      $final[$row_id]['id'] = $row_id;
    }

    foreach (array_keys($final) as $row_id) {
      if ($final[$row_id]['workflow_state'] !== 'published' ||
        strlen($final[$row_id]['file']) > 224 ||
        empty($final[$row_id]['file'])
      ) {
        unset($final[$row_id]);
      }
    }
    return $final;
  }

  /**
   * {@inheritdoc}
   */
  public function getIdList() {
    if (self::$csvData) {
      return array_keys(self::$csvData);
    }
    Migration::displayMessage(
      t('Loading of !fileUrl failed:',
        array('!listurl' => $this->fileUrl))
    );
    return NULL;
  }

  /**
   * Create a stub object that will be later migrated.
   *
   * @param object $migration
   *   Migration object
   * @param array $source
   *   Source object
   *
   * @return array
   *   Array with new tid
   */
  protected function createStub($migration, array $source) {
    $file = new stdClass();
    $file->uri = OSHA_MIGRATE_FILES_DEST_DIR . $source[0];
    $file->uid = 1;
    file_save($file);
    return array($file->fid);
  }

  /**
   * {@inheritdoc}
   */
  public function computeCount() {
    return count(self::$csvData);
  }
}

class OshaMigrateFilesItemCSV extends MigrateItemFile {

  protected $data;

  /**
   * {@inheritdoc}
   */
  public function getItem($item_id) {
    if (empty($this->data)) {
      $csv_data = OshaMigrateFilesListCSV::$csvData;
      foreach ($csv_data as $csv_id => $item) {
        $this->data[$csv_id] = (object) $item;
      }
    }
    return isset($this->data[$item_id]) ? $this->data[$item_id] : NULL;
  }
}
