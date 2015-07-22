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
   * Executes after import.
   */
  public function postImport() {
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
          $this->addFieldMapping("$field_name:create_term")->defaultValue(TRUE);
          $this->addFieldMapping("$field_name:ignore_case")->defaultValue(TRUE);
        }
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
