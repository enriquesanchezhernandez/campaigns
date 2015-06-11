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
      ),
      'publications' => array(
        'group_name' => 'ncw',
        'dependencies' => array(),
        'class_name' => 'NCWPublicationsMigration',
      ),
      'news' => array(
        'group_name' => 'ncw',
        'dependencies' => array(),
        'class_name' => 'NCWNewsMigration',
      ),
      'note_to_editor' => array(
        'group_name' => 'ncw',
        'dependencies' => array(),
        'class_name' => 'NCWNoteMigration',
      ),
      'press_release' => array(
        'group_name' => 'ncw',
        'dependencies' => array(),
        'class_name' => 'NCWPressMigration',
      ),
      'highlight' => array(
        'group_name' => 'ncw',
        'dependencies' => array(),
        'class_name' => 'NCWHighlightMigration',
      ),
      'infographic' => array(
        'group_name' => 'ncw',
        'dependencies' => array(),
        'class_name' => 'NCWInfographicMigration',
      ),
      'press_contact' => array(
        'group_name' => 'ncw',
        'dependencies' => array(),
        'class_name' => 'NCWPressContactMigration',
      ),
      'tax_country' => array(
        'group_name' => 'ncw',
        'dependencies' => array(),
        'class_name' => 'NCWTaxonomyCountryMigration',
      ),
      'tax_country_status' => array(
        'group_name' => 'ncw',
        'dependencies' => array(),
        'class_name' => 'NCWTaxonomyCountryStatusMigration',
      ),
      'tax_fop_link_sections' => array(
        'group_name' => 'ncw',
        'dependencies' => array(),
        'class_name' => 'NCWTaxonomyFOPLinkSectionsMigration',
      ),
      'tax_newsletter_sections' => array(
        'group_name' => 'ncw',
        'dependencies' => array(),
        'class_name' => 'NCWTaxonomyNewsletterSectionsMigration',
      ),
      'tax_publication_types' => array(
        'group_name' => 'ncw',
        'dependencies' => array(),
        'class_name' => 'NCWTaxonomyPublicationTypeMigration',
      ),
      'tax_tags' => array(
        'group_name' => 'ncw',
        'dependencies' => array(),
        'class_name' => 'NCWTagsMigration',
      ),
    ),
  );
}

/**
 * Class AbstractNCWNodeMigration is used to migrate nodes from NCW.
 */
abstract class AbstractNCWNodeMigration extends Migration {

  protected $endpoint_url = NULL;
  protected $bundle = NULL;

  public function __construct($arguments, $source_klass, $bundle, $endpoint_url) {
    parent::__construct($arguments);
    $this->bundle = $bundle;
    if (!empty($arguments['dependencies'])) {
      $this->dependencies = $arguments['dependencies'];
    }
    $this->endpoint_url = $endpoint_url;
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'nid' => array(
          'type'        => 'varchar',
          'length'      => 255,
          'not null'    => TRUE,
          'description' => 'Original nid in the NCW website',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );
    $this->source = new $source_klass(array('endpoint_url' => $this->endpoint_url));
    $this->destination = new MigrateDestinationNode($bundle);
    $this->addFieldMappings();
  }

  /**
   * Configure field mappings, reads bundle field information
   */
  protected function addFieldMappings() {
    // Node base fields
    $this->addFieldMapping('uid')->defaultValue(0);
    $this->addFieldMapping('comment')->defaultValue(0);
    $this->addFieldMapping('status', 'status');
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('changed', 'changed');
    $this->addFieldMapping('created', 'created');
    $this->addFieldMapping('promote', 'promote');
    $this->addFieldMapping('sticky', 'sticky');
    $this->addFieldMapping('log', 'log');
    $this->addFieldMapping('language', 'language');
    $this->addFieldMapping('path', 'path');
    $this->addFieldMapping('workbench_access')->defaultValue(1); // Assign default section

    // Handle field migration in a generic way
    $fields = field_info_instances('node', $this->bundle);
    $exposed = $this->source->fields();
    foreach($fields as $field_name => $field_info) {
      if (array_key_exists($field_name, $exposed)) {
        $this->addFieldMapping($field_name, $field_name);

        // Extra mappings depending on field type
        $fi = field_info_field($field_name);
        if ($fi['translatable'] == 1 && $fi['type'] != 'taxonomy_term_reference' /* field_organised_by */) {
          $this->addFieldMapping("$field_name:language", $field_name . '_language');
        }
        if ($fi['type'] == 'taxonomy_term_reference') {
          $this->addFieldMapping("$field_name:create_term")->defaultValue(TRUE);
        }
        if ($fi['type'] == 'link_field') {
          $this->addFieldMapping("$field_name:title", $field_name . '_title');
          $this->addFieldMapping("$field_name:attributes", $field_name . '_attributes');
        }
        if ($fi['type'] == 'text_with_summary') {
          $this->addFieldMapping("$field_name:summary", $field_name . '_summary');
          $this->addFieldMapping("$field_name:format", $field_name . '_format');
        }
        if ($fi['type'] == 'text_long') {
          $this->addFieldMapping("$field_name:format", $field_name . '_format');
        }
        if ($fi['type'] == 'datetime') {
          $this->addFieldMapping("$field_name:to", $field_name . '_value2');
          $this->addFieldMapping("$field_name:timezone", $field_name . '_timezone');
        }
        if ($fi['type'] == 'file' || $fi['type'] == 'image') {
          $this->addFieldMapping("$field_name:file_replace")->defaultValue(TRUE);
        }
      }
    }

    //@todo: metatag migration - which is sob
    $this->addUnmigratedDestinations(
      array(
        'revision', 'tnid', 'translate', 'revision_uid', 'is_new'
      )
    );
  }


  protected function ignoreMetatagMigration() {
    $this->addUnmigratedDestinations(array(
      'metatag_title',
      'metatag_description',
      'metatag_abstract',
      'metatag_keywords',
      'metatag_robots',
      'metatag_news_keywords',
      'metatag_standout',
      'metatag_generator',
      'metatag_rights',
      'metatag_image_src',
      'metatag_canonical',
      'metatag_shortlink',
      'metatag_publisher',
      'metatag_author',
      'metatag_original-source',
      'metatag_revisit-after',
      'metatag_content-language',
      'metatag_dcterms.title',
      'metatag_dcterms.creator',
      'metatag_dcterms.subject',
      'metatag_dcterms.description',
      'metatag_dcterms.publisher',
      'metatag_dcterms.contributor',
      'metatag_dcterms.date',
      'metatag_dcterms.modified',
      'metatag_dcterms.type',
      'metatag_dcterms.format',
      'metatag_dcterms.identifier',
      'metatag_dcterms.source',
      'metatag_dcterms.language',
      'metatag_dcterms.relation',
      'metatag_dcterms.coverage',
      'metatag_dcterms.rights',
    ));
  }

  /**
   * Implements Migration::prepareRow() to adapt JSON fields data to what migrate expects in the field.
   */
  public function prepareRow($row) {
    $row->path = !empty($row->path['alias']) ? $row->path['alias']:  NULL;
    // Normalize JSON structure, to match migrate expectations for field data
    $fields = field_info_instances('node', $this->bundle);
    foreach($fields as $field_name => $field_info) {
      $fi = field_info_field($field_name);
      $normalizer = 'osha_migration_normalize_field_' . $fi['type'];
      if(function_exists($normalizer)) {
        $normalizer($row, $field_name, $fi);
      }
      else {
        $name = $this->currentMigration()->getMachineName();
        watchdog('ncw_migration', "[BUG][$name] Cannot find normalization '$normalizer', skipping field $field_name", array(), WATCHDOG_ERROR);
        $row->{$field_name} = array();
      }
    }
  }

  /**
   * Implements Migration::prepare()
   */
  public function prepare($entity, stdClass $row) {
    if(!empty($row->workbench_moderation)) {
      $entity->workbench_moderation_state_new = $row->workbench_moderation['current']['state'];
    }
  }

  /**
   * Implements Migration::complete() to configure translations
   */
  public function complete($entity, stdClass $row) {
    unset($row->translations['data']['en']);
    if (!empty($row->translations['data'])) {
      $handler = entity_translation_get_handler('node', $entity);
      foreach($row->translations['data'] as $language => $data) {
        $handler->setTranslation(array(
          'language' => $data['language'],
          'source' => $data['source'],
          'status' => $data['status'],
          'translate' => $data['translate'],
          'uid' => osha_migration_author_uid(),
        ));
      }
      $handler->saveTranslations();
    }
  }
}


/**
 * Class AbstractNCWNodeSource base for all NCW JSON node imports.
 */
abstract class AbstractNCWNodeSource extends MigrateSource {

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
   * @todo: the remote loading using cURL?
   */
  public function readData() {
    $this->rows = array();
    $content = file_get_contents($this->endpoint_url);
    if ($data = json_decode($content)) {
      foreach ($data->items as $ob) {
        $ob = $ob->item;
        $id = $this->itemIdentifier($ob);
        $node_url = $this->itemUrl($id);
        if ($rowd = file_get_contents($node_url)) {
          if ($row_ob = json_decode($rowd, TRUE)) {
            $row = new stdClass();
            foreach($row_ob as $k => $v) {
              $row->$k = $v;
            }
            $this->rows[$id] = $row;
          }
        }
        else {
          //@todo: var_dump($node_url);
        }
      }
    }
    reset($this->rows);
  }

  public function itemUrl($id) {
    return osha_migration_url_data_source('/export/node/' . $id);
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

  public abstract function contentFields();
}

////////////////////////////////// Utilities ///////////////////////////////////

function osha_migration_url_data_source($suffix = '') {
  return variable_get('hcw_ncw_root_url', 'http://osha.localhost') . $suffix;
}

function osha_migration_url_files($suffix = '') {
  return variable_get('hcw_ncw_root_url', 'http://osha.localhost') . '/sites/default/files/' . $suffix;
}

function osha_migration_author_uid() {
  return 0;
}


////////////////////////////// Normalization functions /////////////////////////
function osha_migration_normalize_field_list_text($row, $field_name) {
  $field = array();
  if (!empty($row->{$field_name}) && is_array($row->{$field_name})) {
    foreach ($row->{$field_name} as $language => $values) {
      foreach($values as $v) {
        $field[] = $v['value'];
      }
    }
  }
  $row->{$field_name} = $field;
}

function osha_migration_normalize_field_number_integer($row, $field_name) {
  $field = array();
  if (!empty($row->{$field_name}) && is_array($row->{$field_name})) {
    foreach ($row->{$field_name} as $language => $values) {
      foreach($values as $v) {
        $field[] = $v['value'];
      }
    }
  }
  $row->{$field_name} = $field;
}

function osha_migration_normalize_field_text_long($row, $field_name) {
  $field = array();
  $languages = array();
  if (!empty($row->{$field_name}) && is_array($row->{$field_name})) {
    foreach ($row->{$field_name} as $language => $values) {
      foreach($values as $v) {
        $field[] = $v['value'];
        $languages[] = $language;
        $format = $v['format'];
      }
    }
  }
  $row->{$field_name} = $field;
  $row->{$field_name . '_language'} = $languages;
  $row->{$field_name . '_format'} = $format;
}

function osha_migration_normalize_field_text_with_summary($row, $field_name, $field_info) {
  $field = array();
  $languages = array();
  if (!empty($row->{$field_name}) && is_array($row->{$field_name})) {
    foreach ($row->{$field_name} as $language => $values) {
      foreach($values as $v) {
        $field[$language] = $v['value'];
        $languages[] = $language;
        $format = $v['format'];
      }
    }
  }
  $row->{$field_name} = $field;
  $row->{$field_name . '_language'} = $languages;
  $row->{$field_name . '_format'} = $format;
}

function osha_migration_normalize_field_link_field($row, $field_name, $field_info) {
  $field = array(
    'url' => array(),
    'title' => array(),
  );
  if (!empty($row->{$field_name}) && is_array($row->{$field_name})) {
    if ($field_info['translatable'] == 0) {
      $data = array_pop($row->{$field_name});
      foreach ($data as $link) {
        $field['url'][] = $link['url'];
        $field['title'][] = $link['title'];
        $field['attributes'][] = $link['attributes'];
      }
    }
  }
  $row->{$field_name} = $field['url'];
  $row->{$field_name . '_title'} = $field['title'];
  $row->{$field_name . '_attributes'} = $field['attributes'];//@todo not tested
}

function osha_migration_normalize_field_text($row, $field_name, $field_info) {
  $field = array();
  $languages = array();
  if (!empty($row->{$field_name}) && is_array($row->{$field_name})) {
    foreach ($row->{$field_name} as $language => $values) {
      foreach($values as $v) {
        $field[] = $v['value'];
        $languages[] = $language;
      }
    }
  }
  $row->{$field_name} = $field;
  $row->{$field_name . '_language'} = $languages;
}

function osha_migration_normalize_field_email($row, $field_name, $field_info) {
  $field = array();
  $languages = array();
  if (!empty($row->{$field_name}) && is_array($row->{$field_name})) {
    foreach ($row->{$field_name} as $language => $values) {
      foreach($values as $v) {
        $field[] = $v['email'];
        $languages[] = $language;
      }
    }
  }
  $row->{$field_name} = $field;
  $row->{$field_name . '_language'} = $languages;
}

function osha_migration_normalize_field_datetime($row, $field_name, $field_info) {
  $field = array(
    'value' => NULL,
    'timezone' => NULL,
    'value2' => NULL,
  );
  if (!empty($row->{$field_name}) && is_array($row->{$field_name})) {
    $field = array_pop($row->{$field_name});
    if (!empty($field[0])) {
      $field = $field[0];
    }
  }
  $row->{$field_name} = $field['value'];
  $row->{$field_name . '_value2'} = $field['value2'];
  $row->{$field_name . '_timezone'} = $field['timezone'];
}

function osha_migration_normalize_field_taxonomy_term_reference($row, $field_name, $field_info) {
  $field = array();
  if (isset($row->{$field_name}['name_original'])) { // cardinality 1
    $field[] = $row->{$field_name}['name_original'];
  }
  else if (!empty($row->{$field_name}) && is_array($row->{$field_name})) {
    foreach ($row->{$field_name} as $value) {
      if (isset($value['name_original'])) {
        $field[] = $value['name_original'];
      }
    }
  }
  else {
    // @todo: show error watchdog ...
  }
  $row->{$field_name} = $field;
}

function osha_migration_normalize_field_file($row, $field_name) {
  $field = array();
  $languages = array();
  if (!empty($row->{$field_name}) && is_array($row->{$field_name})) {
    foreach ($row->{$field_name} as $language => $values) {
      foreach($values as $f) {
        $field[] = osha_migration_url_files(str_replace('public://', '', $f['uri']));
        $languages[] = $language;
      }
    }
  }
  $row->{$field_name} = $field;
  $row->{$field_name . '_language'} = $languages;
}

function osha_migration_normalize_field_image($row, $field_name) {
  $field = array();
  $languages = array();
  if (!empty($row->{$field_name}) && is_array($row->{$field_name})) {
    foreach ($row->{$field_name} as $language => $values) {
      foreach($values as $f) {
        $field[] = osha_migration_url_files(str_replace('public://', '', $f['uri']));
        $languages[] = $language;
      }
    }
  }
  $row->{$field_name} = $field;
  $row->{$field_name . '_language'} = $languages;
}
