<?php

/**
 * Implements hook_migrate_api().
 *
 * Set the API level to 2, for migration classes to be recognized by Migrate.
 */
function ncw_migration_migrate_api() {
  return array(
    'api' => 2,
    'groups' => array(
      'ncw' => array(
        'title' => 'Import data from NCW'
      ),
    ),
    'migrations' => array(
      'events' => array(
        'group_name' => 'ncw',
        'dependencies' => array(),
        'class_name' => 'NCWEventsMigration',
      )
    ),
  );
}


abstract class AbstractNCWMigration extends Migration {

  protected $endpoint_url = NULL;

  public function __construct($arguments, $source_klass) {
    parent::__construct($arguments);
    if (!empty($arguments['dependencies'])) {
      $this->dependencies = $arguments['dependencies'];
    }
    if (empty($arguments['endpoint_url'])) {
      $this->endpoint_url = $arguments['endpoint_url'];
    }

    $this->map         = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type'        => 'varchar',
          'length'      => 255,
          'not null'    => TRUE,
          'description' => 'Original nid in the NCW website',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );
    $this->source      = new $source_klass($this->endpoint_url);
    $this->destination = new MigrateDestinationNode('event');
  }

  abstract function addFieldMappings();
}

/**
 * Class AbstractNCWSource base for all NCW imports
 */
abstract class AbstractNCWSource extends MigrateSource {

  protected $endpoint_url = NULL;
  protected $rows = array();

  public function __construct($options) {
    parent::__construct($options);
    $this->endpoint_url = $options['endpoint_url'];
  }

  /**
   * Return a string representing the source, for display in the UI.
   */
  public function __toString() {
    return 'Extract data from NCW endpoint';
  }

  /**
   * Total number of entities.
   */
  public function computeCount() {
    if (empty($this->rows)) {
      $this->readData();
    }
    return count($this->rows);
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
    //@todo: the remote loading using cURL?
    $this->rows = array();
    reset($this->rows);
  }
}
