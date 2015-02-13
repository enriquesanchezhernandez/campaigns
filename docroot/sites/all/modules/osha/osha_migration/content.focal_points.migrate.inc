<?php
/**
 * Class MigrateOshaBlog migrates blog.txt contents. The data
 * is stored inside the <em>Blog</em> content type.
 */
class MigrateOshaFocalPoints extends OSHADynamicMigration {

  /**
   * {@inheritdoc}
   */
  public function __construct($arguments) {
    parent::__construct(MigrateGroup::getInstance('OSHA Content types'));
    $this->description = 'Import "Focal Points" contents from CSV file';

    /* Remove limits on time/memory, slower machines will fail */
    $this->timeLimit = 0;
    $this->memoryLimit = PHP_INT_MAX;

    $source_file = MigrationUtil::getSourceFile($arguments);
//    $source_file_bureau = MigrationUtil::getSourceFileByKey($arguments, 'file_name_bureau');
//    $source_file_board = MigrationUtil::getSourceFileByKey($arguments, 'file_name_board');
    $this->source = new MigrateSourceList(
      new FocalPointsContentListXML($source_file),
      new FocalPointsContentItemXML(),
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
    $this->destination = new MigrateDestinationNode('press_contact', $node_options);

    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('field_press_contact_organization', 'field_press_contact_organization');
    $this->addFieldMapping('field_personal_title', 'field_personal_title');
    $this->addFieldMapping('title_field', 'title_field');
    $this->addFieldMapping('field_press_contact_phone', 'field_press_contact_phone');
    $this->addFieldMapping('field_press_contact_location', 'field_press_contact_location');
//    $this->addFieldMapping('field_country', 'field_country');
    $this->addFieldMapping('field_zip_code', 'field_zip_code');
    $this->addFieldMapping('field_city', 'field_city');
    $this->addFieldMapping('field_contact_type', 'field_contact_type');
    $this->addFieldMapping('uid')->defaultValue(1);

    $this->addUnmigratedSources(array(
      'path',
      'language',
      'workflow_state',
      'country',
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
      //'body:summary',
      'field_image:language',
      'field_image:destination_dir',
      'field_image:title',
      'field_image:alt',
      'field_nace_codes:create_term',
      'field_nace_codes:ignore_case',
      'field_publication_date:timezone',
      'field_publication_date:rrule',
      'field_publication_date:to',
      'field_summary',
      'field_summary:format',
      'field_tags:create_term',
      'field_tags:ignore_case',
      'field_thesaurus:create_term',
      'field_thesaurus:ignore_case',
      'field_country',
      'comment',
    ));
  }

  /**
   * Migration machine name.
   *
   * {@inheritdoc}
   */
  protected function generateMachineName() {
    return OSHA_MIGRATION_CONTENT_TYPE_FOCAL_POINT;
  }

  /**
   * Prepare raw data pulled from source.
   *
   * {@inheritdoc}
   */
  public function prepareRow($row) {
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
    $country = MigrationUtil::getCountryIso2ByName($row->field_country_iso2);
    if ($country == NULL) {
      $this->displayMessage('Focal Points Country '
        . $row->field_country_iso2 . ' not found', 'warning');
      $row->field_country_iso2 = NULL;
    }
    else {
      $tid = MigrationUtil::getCountryTermByISO2($country);
      if (empty($tid)) {
        $voc = taxonomy_vocabulary_machine_name_load('country');
        $term = new stdClass();
        $term->vid = $voc->vid;
        $term->name = ucwords(strtolower($row->field_country_iso2));
        $term->field_iso2[LANGUAGE_NONE][0]['value'] = $country;
        taxonomy_term_save($term);
        $tid = $term->tid;
      }
      $entity->field_country[LANGUAGE_NONE][0] = array('tid' => $tid);
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
      'text' => 'Body of the blog',
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
}

class FocalPointsContentListXML extends MigrateList {
  protected $file = '';
  public static $data = array();

  /**
   * {@inheritdoc}
   */
  public function __construct($file, $file_board = "", $file_bureau = "") {
    parent::__construct($file);
    $this->file = $file;
//    $this->file_board = $file_board;
//    $this->file_bureau = $file_bureau;
    $this->parseSourceFile();
  }

  /**
   * {@inheritdoc}
   */
  public function __toString() {
    return $this->file;
  }

  /**
   * Parse the XML file and populate the local cache.
   */
  protected function parseSourceFile() {
    $xml = simplexml_load_file($this->file);
    // To be used for board and bureau memebers, to merge the details.
//    $xml_board = simplexml_load_file($this->file_board);
//    $xml_bureau = simplexml_load_file($this->file_bureau);
    self::$data = array();
    foreach ($xml->getDocNamespaces() as $str_prefix => $str_namespace) {
      if (strlen($str_prefix) == 0) {
        // Assign an namespace prefix.
        $str_prefix = "fp";
      }
      $xml->registerXPathNamespace($str_prefix, $str_namespace);
    }
    // Contact fields are attributes of Detail.
    foreach ($xml->xpath('//fp:Detail') as $focalpoint) {
      $data = new stdClass();
      $attributes = $focalpoint->attributes();
      $data->title = (string) $attributes['Table0_Details5'];
      $data->title_field = (string) $attributes['Table0_Details5'];
      $data->field_press_contact_organization = (string) $attributes['Table0_Details1'];
      $data->field_personal_title = (string) $attributes['Table0_Details3'];
      $data->field_press_contact_phone = (string) $attributes['Table0_Details6'];
      $data->field_press_contact_location = (string) $attributes['a_osh_phaddress'];
      $data->field_country_iso2 = (string) $attributes['a_osh_phcountryid'];
      $data->field_zip_code = (string) $attributes['a_osh_phcp'];
      $data->field_city = (string) $attributes['a_osh_phtown'];
      $data->field_contact_type = 'Focal Point';
      $id = $this->idFromName((string) $data->title);
      self::$data[$id] = $data;
    }
  }


  /**
   * Convert to ID from contact name.
   */
  public function idFromName($name) {
    return strtolower(str_replace(' ', '_', $name));
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

class FocalPointsContentItemXML extends MigrateItem {

  /**
   * {@inheritdoc}
   */
  public function getItem($item_id) {
    if (array_key_exists($item_id, FocalPointsContentListXML::$data)) {
      return (object) FocalPointsContentListXML::$data[$item_id];
    }
    return NULL;
  }
}
