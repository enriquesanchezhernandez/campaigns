<?php

define('OSHA_MIGRATE_IMAGES_DEST_DIR', 'public://');
/**
 * Class OshaMigrateImages
 */
class OshaMigrateImages extends DynamicMigration {

  /**
   * {@inheritdoc}
   */
  public function __construct($arguments) {
    parent::__construct();
    $this->description = t('Imports images');

    /* Remove limits on time/memory, slower machines will fail */
    $this->timeLimit = 0;
    $this->memoryLimit = PHP_INT_MAX;

    // Set bundle document.
    $this->destination = new MigrateDestinationFile('image', 'MigrateFileUri');

    $source_file = MigrationUtil::getSourceFile($arguments);

    $this->source = new MigrateSourceList(new OshaMigrateImagesListCSV($source_file),
      new OshaMigrateImagesItemCSV(osha_migration_get_data_dir(OSHA_MIGRATION_EXPORT_DIRECTORY)),
      array(
        'id' => 'Primary Key (URL pattern)',
        'path' => 'URL pattern without language',
        'language' => 'Row language',
        'workflow_state' => '',
        'creation_date' => '',
        'modification_date' => '',
        'publication_date' => '',
        'creator' => 'Author user id from the old website',
        'aliases' => 'Image redirects',
        'title' => '',
        'description' => '',
        'subject' => 'Categories/Tags',
        'country' => '',
        'subcategory' => 'Merged into categories',
        'multilingual_thesaurus' => '',
        'nace' => 'Nace codes taxonomy',
        'image' => 'Image path',
        'image_uri' => 'Image URI',
        'timestamp' => 'Timestamp',
      )
    );

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'varchar',
          'length' => 200,
          'not null' => TRUE,
          'description' => 'Image old path',
        ),
      ),
      MigrateDestinationFile::getKeySchema()
    );

    $this->addFieldMapping('source_dir')->defaultValue(osha_migration_get_data_dir(OSHA_MIGRATION_EXPORT_DIRECTORY));
    $this->addFieldMapping('destination_file', OSHA_MIGRATION_REPLACED_PATH_PREFIX . 'image');
    $this->addFieldMapping('value', 'image_uri');
    $this->addFieldMapping('destination_dir')->defaultValue(OSHA_MIGRATE_IMAGES_DEST_DIR);
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

    $this->addUnmigratedSources(
      array(
        'country',
        'creator',
      )
    );

    $this->addUnmigratedDestinations(
      array(
        'uid',
        'field_file_image_alt_text',
        'field_file_image_alt_text:language',
        'field_file_image_title_text',
        'field_file_image_title_text:language',
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
    return OSHA_MIGRATION_IMAGES;
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
    $row->image_uri = $row->image;
    $row->timestamp = time();

    if (strlen($row->title) > 255) {
      $row->description = $row->title . ' ' . $row->description;
      $row->title = '';
    }

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
    $destination = MigrationUtil::cleanMigratedFile($row, 'image', OSHA_MIGRATE_FILES_DEST_DIR);
    if (empty($destination)) {
      return FALSE;
    }    if (!is_file(osha_migration_get_data_dir(OSHA_MIGRATION_EXPORT_DIRECTORY) . $row->image)) {
      $this->saveMessage("Image could not be found, ignoring {$row->image}", MigrationBase::MESSAGE_WARNING);
      return FALSE;
    }
    return TRUE;
  }

  public function prepare($entity, $row) {
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
    if (substr($row->path, 1, 2) == $language) {
      $path = substr($row->path, 4);
    }
    else {
      $path = substr($row->path, 1);
    }
    $alias = array(
      'source' => 'file/' . $entity->fid,
      'alias' => $path,
      'language' => $language,
    );
    path_save($alias);

    // create redirect
    MigrationUtil::createRedirects($entity, $row->aliases);
  }
}

class OshaMigrateImagesListCSV extends MigrateList {

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
    $fields = $data = fgetcsv($handle, NULL, ';');
    $final = array();
    while (($data = fgetcsv($handle, NULL, ';')) !== FALSE) {
      $row_id = $data[0];
      foreach ($fields as $key => $field) {
        $final[$row_id][$field] = $data[$key];
      }
      $final[$row_id]['id'] = $row_id;
    }

    foreach (array_keys($final) as $row_id) {
      if ($final[$row_id]['workflow_state'] !== 'published' ||
        strlen($final[$row_id]['image']) > 224 ||
        empty($final[$row_id]['image'])
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
    $file->uri = OSHA_MIGRATE_IMAGES_DEST_DIR . $source[0];
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

class OshaMigrateImagesItemCSV extends MigrateItemFile {

  protected $data;

  /**
   * {@inheritdoc}
   */
  public function getItem($item_id) {
    if (empty($this->data)) {
      $csv_data = OshaMigrateImagesListCSV::$csvData;
      foreach ($csv_data as $csv_id => $item) {
        $this->data[$csv_id] = (object) $item;
      }
    }
    return isset($this->data[$item_id]) ? $this->data[$item_id] : NULL;
  }
}
