<?php

function hwc_crm_migration_migrate_api() {
  $crm_data_dir = variable_get('hwc_crm_data_dir', '');
  return array(
    'api' => 2,
    'groups' => array(
      'hwc_crm' => array(
        'title' => 'Import data from CRM',
      ),
    ),
    'migrations' => array(
      'partner' => array(
        'group_name' => 'hwc_crm',
        'class_name' => 'PartnerMigration',
        'destination' => 'partner',
        'file_name' => $crm_data_dir . '/PublicProfile.xml'
      ),
    ),
  );
}

/**
 *
 */
class HwcCrmMigration extends Migration {

  /**
   * {@inheritdoc}
   */
  public function __construct($arguments) {
    parent::__construct($arguments);

    /* Remove limits on time/memory, slower machines will fail */
    $this->timeLimit = 0;
    $this->memoryLimit = PHP_INT_MAX;

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
    $this->destination = new MigrateDestinationNode($arguments['destination'], $node_options);
    $this->bundle = $arguments['destination'];
    $this->addFieldMappings();
  }

  /**
   * Executes before Import.
   */
  public function preImport() {
//    self::activateOshaFilesHandler();
  }

  /**
   * Executes after import.
   */
  public function postImport() {
//    self::deactivateOshaFilesHandler();
    parent::postImport();
    $this->removeNeedsUpdateItems();
  }

  /**
   * Configure field mappings, reads bundle field information
   */
  protected function addFieldMappings() {
    // Node base fields
    $this->addFieldMapping('uid')->defaultValue(0);
    $this->addFieldMapping('comment')->defaultValue(0);
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('workbench_access')->defaultValue(1); // Assign default section

    // Handle field migration in a generic way
    $fields = field_info_instances('node', $this->bundle);
    $exposed = $this->source->fields();
    foreach($fields as $field_name => $field_info) {
      if (in_array($field_name, $exposed) && !in_array($field_name, $this->getManuallyMigratedFields())) {
        $this->addFieldMapping($field_name, $field_name);

        // Extra mappings depending on field type
        $fi = field_info_field($field_name);
        if ($fi['type'] == 'taxonomy_term_reference') {
          var_dump($field_name);
          $this->addFieldMapping("$field_name:create_term")->defaultValue(TRUE);
          $this->addFieldMapping("$field_name:ignore_case")->defaultValue(TRUE);
        }
//        if ($fi['type'] == 'link_field') {
//          $this->addFieldMapping("$field_name:title", $field_name . '_title');
//          $this->addFieldMapping("$field_name:attributes", $field_name . '_attributes');
//        }
//        if ($fi['type'] == 'text_with_summary') {
//          $this->addFieldMapping("$field_name:summary", $field_name . '_summary');
//          $this->addFieldMapping("$field_name:format", $field_name . '_format');
//        }
//        if ($fi['type'] == 'text_long') {
//          $this->addFieldMapping("$field_name:format", $field_name . '_format');
//        }
//        if ($fi['type'] == 'datetime') {
//          $this->addFieldMapping("$field_name:to", $field_name . '_value2');
//          $this->addFieldMapping("$field_name:timezone", $field_name . '_timezone');
//        }
        if ($fi['type'] == 'file' || $fi['type'] == 'image') {
          $this->addFieldMapping("$field_name:file_replace")->defaultValue(0);
          $this->addFieldMapping("$field_name:file_class")->defaultValue('MigrateFileBlob');
          $this->addFieldMapping("$field_name:value", $field_name);
          $this->addFieldMapping("$field_name:destination_file", $field_name . "_file");
        }
      }
    }
    $this->addUnmigratedDestinations(
      array(
        'revision', 'tnid', 'translate', 'revision_uid', 'is_new', 'status', 'changed', 'created',
        'sticky', 'log', 'language', 'path',
      )
    );
  }

  protected function getManuallyMigratedFields() {
    return array();
  }

  public function removeNeedsUpdateItems() {
    // Remove non-existing sources.
    $removed = $this->getMap()->getRowsNeedingUpdate(10000);
    if (!empty($removed)) {
      $nodes = array();
      foreach ($removed as $to_remove) {
        $nodes[] = $to_remove->destid1;
        $this->getMap()->delete(array($to_remove->sourceid1));
      }
      node_delete_multiple($nodes);
    }
  }

  /**
   * Get iso2 code of a Country name (from standard Drupal list)
   */
  public static function getCountryIso2ByName($name) {
    $countries = country_get_list();
    foreach($countries as $iso2 => $country) {
      if (strtoupper($country) == strtoupper($name)) {
        return $iso2;
      }
    }
    return self::getNonStandardCountry($name);
  }

  /**
   * Get iso2 code for Country names that are not in the standard list.
   */
  public static function getNonStandardCountry($name) {
    $countries = array(
      'MK' => 'THE FORMER YUGOSLAV REPUBLIC OF MACEDONIA',
      'XK' => 'KOSOVO UNDER UNSCR 1244',
    );
    foreach($countries as $iso2 => $country) {
      if (strtoupper($country) == strtoupper($name)) {
        return $iso2;
      }
    }
    return NULL;
  }

  /**
   * Get tids of the Term Countries with a specified iso2.
   */
  public static function getCountryTermByISO2($iso2) {
    $voc = taxonomy_vocabulary_machine_name_load('country');
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'taxonomy_term')
      ->propertyCondition('vid', $voc->vid)
      ->fieldCondition('field_iso2', 'value', strtoupper($iso2));
    $result = $query->execute();
    if (isset($result['taxonomy_term'])) {
      $tids = array_keys($result['taxonomy_term']);
      return current($tids);
    }
    return NULL;
  }

  /**
   *  Activate Osha files handler
   */
  public static function activateOshaFilesHandler() {
    // Remove default Handlers for Field and Image and let OSHA Handlers to take
    // care of these fields.
    $default_file_handler = 'MigrateFileFieldHandler';
    $default_image_handler = 'MigrateImageFieldHandler';
    $handlers = unserialize(variable_get('migrate_disabled_handlers', ''));
    if (!is_array($handlers)) {
      $handlers[] = $default_file_handler;
      $handlers[] = $default_image_handler;

    }
    else {
      if (!in_array($default_file_handler, $handlers)) {
        $handlers[] = $default_file_handler;
      }
      if (!in_array($default_image_handler, $handlers)) {
        $handlers[] = $default_image_handler;
      }
    }
    variable_set('migrate_disabled_handlers', serialize($handlers));
  }

  /**
   * Deactivate Osha files handler
   */
  public static function deactivateOshaFilesHandler() {
    // Reset migrate_disabled_handlers variable.
    $default_file_handler = 'MigrateFileFieldHandler';
    $handlers = unserialize(variable_get('migrate_disabled_handlers', ''));
    if (is_array($handlers)) {
      $key = array_search($default_file_handler, $handlers);
      if ($key !== FALSE) {
        unset($handlers[$key]);
      }
      $default_image_handler = 'MigrateImageFieldHandler';
      $key = array_search($default_image_handler, $handlers);
      if ($key !== FALSE) {
        unset($handlers[$key]);
      }
      variable_set('migrate_disabled_handlers', serialize($handlers));
    }
  }
}

abstract class AbstractCrmMigrateListXml extends MigrateList {
  public static $data = array();

  protected $file = '';

  /**
   * {@inheritdoc}
   */
  public function __construct($file) {
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
   * Parse the XML file and populate the local cache.
   */
  abstract protected function parseSourceFile();

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

  /**
   * Extract source file for the migration.
   *
   * @param array $arguments
   *   Migration arguments
   *
   * @return string
   *   Path to the migration data file
   * @throws Exception If the file is not accessible
   */
  public static function getSourceFile($arguments) {
    $file = NULL;
    if (isset($arguments['file_name'])) {
      $file = $arguments['file_name'];
      if (!file_exists($file) || !is_readable($file)) {
        Migration::displayMessage(t('Cannot read migration file @file', array('@file' => $file)), 'error');
      }
    }
    else {
      Migration::displayMessage(t('Invalid migration setup: missing `file_name` parameter (source)'));
    }
    return $file;
  }

  public static function getSourceFileByKey($arguments, $key) {
    $file = NULL;
    if (isset($arguments[$key])) {
      $file = $arguments[$key];
      if (!file_exists($file) || !is_readable($file)) {
        if (!file_exists($file) || !is_readable($file)) {
          Migration::displayMessage(t('Cannot read migration file @file', array('@file' => $file)), 'error');
        }
      }
    }
    else {
      Migration::displayMessage(t('Invalid migration setup: missing `'. $key. '` parameter (source)'));
    }
    return $file;
  }
}

/**
 * Class AbstractNCWNodeSource base for all NCW JSON node imports.
 */
abstract class AbstractHWCCRMSource extends MigrateSource {

  protected $file = NULL;
  protected $rows = array();
  protected $count = -1;

  public function __construct($options) {
    parent::__construct($options);
    $this->file = $options['file'];
  }

  /**
   * Return a string representing the source, for display in the UI.
   */
  public function __toString() {
    return 'Extract data from HWC CRM';
  }

  /**
   * Total number of entities.
   */
  public function computeCount() {
//    ncw_migration_debug('!klass: Starting counting !url', array('!klass' => get_class($this), '!url' => $this->endpoint_url));
    if ($this->count == -1) {
      $this->count = 0;
      if ($data = $this->getRawData()) {
        $this->count = count($data);
      }
    }
//    ncw_migration_debug('!klass: Found !count items', array('!klass' => get_class($this), '!count' => $this->count));
    return $this->count;
  }

  public function getRawData() {
    if (is_readable($this->file) && $xml = simplexml_load_file($this->file, 'SimpleXMLElement', LIBXML_COMPACT | LIBXML_PARSEHUGE)) {
      return $xml->xpath('//Detail');
    }
    else {
      return FALSE;
    }
  }

  /**
   * Do whatever needs to be done to start a fresh traversal of the source data.
   *
   * This is always called at the start of an import, so tasks such as opening
   * file handles, running queries, and so on should be performed here.
   */
  public function performRewind() {
    reset($this->rows);
  }

  /**
   * Fetch the next row of data, returning it as an object.
   *
   * @return object
   *   FALSE data as stdClass, FALSE when there is no more data available.
   */
  public function getNextRow() {
    if (empty($this->rows)) {
      $this->readData();
    }
    $item = NULL;
    if (count($this->rows)) {
      $item = current($this->rows);
      next($this->rows);
    }
    return $item;
  }

  /**
   * Remote call to load the data from the endpoint URL
   */
  public function readData() {
//    ncw_migration_debug('!klass: Starting reading items from !url', array('!klass' => get_class($this), '!url' => $this->endpoint_url));
    $this->rows = array();
    if ($data = $this->getRawData()) {
//      ncw_migration_debug('!klass:      * Processing !count items', array('!klass' => get_class($this), '!count' => count($data->items)));
      foreach ($data->items as $ob) {
        $ob = $ob->item;
        $id = $this->itemIdentifier($ob);
        $node_url = $this->itemURL($id);
        ncw_migration_debug('!klass:      * Reading item: !url', array('!klass' => get_class($this), '!url' => $node_url));
        if ($rowd = $this->fileGetContents($node_url)) {
          if ($row_ob = json_decode($rowd, TRUE)) {
            $row = new stdClass();
            foreach($row_ob as $k => $v) {
              $row->$k = $v;
            }
            $this->rows[$id] = $row;
          }
        }
        else {
          if ($this->activeMigration) {
            $this->activeMigration->saveMessage(format_string('Failed to read data from !url', array('!url' => $node_url)));
          }
        }
      }
    }
    ncw_migration_debug('!klass: Done reading items', array('!klass' => get_class($this)));
    reset($this->rows);
  }

  public function fileGetContents($url) {
    //@todo replace all instances of fileGetContents
    return ncw_migration_file_get_contents($url);
  }

  public function itemURL($id) {
    return ncw_migration_datasource_url() . '/export/node/' . $id;
  }

  public function itemIdentifier($ob) {
    return $ob->nid;
  }

  public function fields() {
    return array(
      'nid' => 'nid',
      'title' => 'title',
      'created' => 'created',
      'changed' => 'changed',
      'status' => 'status',
      'promote' => 'promote',
      'sticky' => 'sticky',
      'log' => 'log',
      'language' => 'language',
      'path' => 'path',
    ) + $this->contentFields();
  }

  /**
   * Check the provided ID exists in the migrated source.
   *
   * @param mixed $id
   *   ID to verify
   *
   * @return bool
   *   TRUE if the key exists, FALSE otherwise
   */
  public function containsKey($id) {
    return array_key_exists($id, $this->rows);
  }

  public abstract function contentFields();
}