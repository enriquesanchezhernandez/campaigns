<?php

/**
 * Class MigrateOshaBlogComments migrates blog_comments.txt. The data
 * is stored inside the <em>Blog</em> comments.
 */
class MigrateOshaBlogComments extends OSHADynamicMigration {

  /**
   * {@inheritdoc}
   */
  public function __construct($arguments) {
    parent::__construct(MigrateGroup::getInstance('OSHA Content types'));
    $this->description = 'Import "Blog" comments from CSV file';

    /* Remove limits on time/memory, slower machines will fail */
    $this->timeLimit = 0;
    $this->memoryLimit = PHP_INT_MAX;

    $source_file = MigrationUtil::getSourceFile($arguments);
    $this->source = new MigrateSourceList(
      new BlogCommentsListCSV($source_file),
      new BlogCommentsItemCSV(),
      $this->fields()
    );

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'Id of the comment',
        ),
      ),
      MigrateDestinationComment::getKeySchema()
    );

    $this->destination = new MigrateDestinationComment('comment_node_blog');

    $this->addFieldMapping('nid' , 'nid');
    $this->addFieldMapping('name', 'author_name');
    $this->addFieldMapping('mail', 'author_email');
    $this->addFieldMapping('created', 'date');
    $this->addFieldMapping('comment_body', 'text');
    $this->addFieldMapping('status')
      ->defaultValue(COMMENT_PUBLISHED);
    $this->addFieldMapping('comment_body:format')
      ->defaultValue('full_html');

    $this->addUnmigratedSources(array(
      'path',
    ));

    $this->addUnmigratedDestinations(array(
      'pid',
      'uid',
      'subject',
      'hostname',
      'changed',
      'thread',
      'homepage',
      'language',
      'comment_body:language',
    ));
  }

  /**
   * Migration machine name.
   *
   * {@inheritdoc}
   */
  protected function generateMachineName() {
    return OSHA_MIGRATION_COMMENTS_BLOG;
  }

  /**
   * Prepare raw data pulled from source.
   *
   * {@inheritdoc}
   */
  public function prepareRow($row) {
    // Format date according to UTC timezone
    $row->date = MigrationUtil::getUTCTimestamp($row->date);
    $row->text = MigrationUtil::decodeHTMLText($row->text);

    // Get nid based on node alias
    $alias = substr($row->path, 4);
    $result = db_query("SELECT DISTINCT {redirect}  FROM redirect WHERE source = :alias AND redirect LIKE 'node/%'",
      array(':alias' => $alias));
    $nid = $result->fetchField();

    $row->nid = substr($nid, 5);

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
    $entity_type = $migration->getDestination()->getEntityType();
    $translation_handler = entity_translation_get_handler($entity_type, $entity);

    $entity->translations = $translation_handler->getTranslations();
  }

  /**
   * Return the list of available source fields.
   *
   * @return array
   *   An array o fields with their description
   */
  public function fields() {
    return array(
      'nid' => 'Node Id',
      'path' => 'Blog URL',
      'author_name' => 'Author',
      'author_email' => 'Author email',
      'date' => 'Created date',
      'text' => 'Comment body',
    );
  }
}

class BlogCommentsListCSV extends MigrateList {
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
    while (($raw_data = fgetcsv($handle, 100000, ';')) !== FALSE) {
      $language = 'en';
      $path = self::getIDFromSourceRow($raw_data);
      self::$data[$path]['id'] = $path;

      foreach ($fields as $key => $field) {
        switch ($field) {
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
   * Removes language prefix from ID
   *
   * @param object $row
   *   Migrated source row
   * @return string
   *   Unique row ID
   */
  public static function getIDFromSourceRow($row) {
    $url = $row[0];
    $url = substr($url, 4);
    if (strlen($url) > 255) {
      $url= substr($url, 0, 255);
    }
    return $url.':'.md5($row[3]);
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

class BlogCommentsItemCSV extends MigrateItem {

  /**
   * {@inheritdoc}
   */
  public function getItem($item_id) {
    if (array_key_exists($item_id, BlogCommentsListCSV::$data)) {
      return (object) BlogCommentsListCSV::$data[$item_id];
    }
    return NULL;
  }
}
