<?php

/**
 * Class AbstractNCWNodeMigration is used to migrate nodes from NCW.
 */
abstract class AbstractNCWTaxonomyTermMigration extends AbstractNCWNodeMigration {

  public function __construct($arguments, $source_klass, $bundle, $endpoint_url) {
    parent::__construct($arguments, $source_klass, $bundle, $endpoint_url);
    $this->bundle = $bundle;
    if (!empty($arguments['dependencies'])) {
      $this->dependencies = $arguments['dependencies'];
    }
    $this->endpoint_url = $endpoint_url;
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'tid' => array(
          'type'        => 'varchar',
          'length'      => 255,
          'not null'    => TRUE,
          'description' => 'Original tid in the NCW website',
        ),
      ),
      MigrateDestinationTerm::getKeySchema()
    );
    $this->source = new $source_klass(array('endpoint_url' => $this->endpoint_url));
    $this->destination = new MigrateDestinationTerm($bundle, array('language' => 'en'));
    $this->ignoreMetatagMigration();
  }

  /**
   * Configure field mappings, reads bundle field information
   */
  protected function addFieldMappings() {
    // Taxnomy term base fields
    $this->addSimpleMappings(array('name', 'description', 'format', 'weight'));

    // Handle field migration in a generic way
    $fields = field_info_instances('taxonomy_term', $this->bundle);
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
  }

  /**
   * Implements Migration::prepareRow() to adapt JSON fields data to what migrate expects in the field.
   */
  public function prepareRow($row) {
    $row->language = 'en';
    $row->path = !empty($row->path['alias']) ? $row->path['alias']:  NULL;
    // Normalize JSON structure, to match migrate expectations for field data
    $fields = field_info_instances('taxonomy_term', $this->bundle);
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

    // Remove invalid values so we don't get field validation errors (ie. blog)
    if (!empty($row->field_excluded_from) && is_array($row->field_excluded_from)) {
      $whitelist = array(
        'article',
        'page',
        'job_vacancies',
        'news',
        'press_release',
        'publication',
        'infographic'
      );
      foreach($row->field_excluded_from as $k => $v) {
        if (!in_array($v, $whitelist)) {
          unset($row->field_excluded_from[$k]);
        }
      }
    }
  }

  /**
   * Implements Migration::complete() to configure translations
   */
  public function complete($entity, stdClass $row) {
    unset($row->translations['data']['en']);
    if (!empty($row->translations['data'])) {
      $handler = entity_translation_get_handler('taxonomy_term', $entity);
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

/* Actual migrations */
class NCWTaxonomyCountryMigration extends AbstractNCWTaxonomyTermMigration {

  public function __construct($arguments) {
    $endpoint_url = osha_migration_url_data_source('/export/taxonomy/country');
    parent::__construct($arguments, 'CountryNCWTaxonomyTermSource', 'country', $endpoint_url);
    $this->description = 'Import taxonomy "country" from NCW';
  }
}

class NCWTaxonomyCountryStatusMigration extends AbstractNCWTaxonomyTermMigration {

  public function __construct($arguments) {
    $endpoint_url = osha_migration_url_data_source('/export/taxonomy/country_status');
    parent::__construct($arguments, 'SimpleNCWTaxonomyTermSource', 'country_status', $endpoint_url);
    $this->description = 'Import taxonomy "country_status" from NCW';
  }
}

class NCWTaxonomyFOPLinkSectionsMigration extends AbstractNCWTaxonomyTermMigration {

  public function __construct($arguments) {
    $endpoint_url = osha_migration_url_data_source('/export/taxonomy/fop_link_sections');
    parent::__construct($arguments, 'SimpleNCWTaxonomyTermSource', 'fop_link_sections', $endpoint_url);
    $this->description = 'Import taxonomy "fop_link_sections" from NCW';
  }
}

class NCWTaxonomyNewsletterSectionsMigration extends AbstractNCWTaxonomyTermMigration {

  public function __construct($arguments) {
    $endpoint_url = osha_migration_url_data_source('/export/taxonomy/newsletter_sections');
    parent::__construct($arguments, 'SimpleNCWTaxonomyTermSource', 'newsletter_sections', $endpoint_url);
    $this->description = 'Import taxonomy "newsletter_sections" from NCW';
  }
}

class NCWTaxonomyPublicationTypeMigration extends AbstractNCWTaxonomyTermMigration {

  public function __construct($arguments) {
    $endpoint_url = osha_migration_url_data_source('/export/taxonomy/publication_types');
    parent::__construct($arguments, 'PublicationTypeNCWTaxonomyTermSource', 'publication_types', $endpoint_url);
    $this->description = 'Import taxonomy "publication_types" from NCW';
  }
}

class NCWTagsMigration extends AbstractNCWTaxonomyTermMigration {

  public function __construct($arguments) {
    $endpoint_url = osha_migration_url_data_source('/export/taxonomy/tags');
    parent::__construct($arguments, 'TagsNCWTaxonomyTermSource', 'tags', $endpoint_url);
    $this->description = 'Import taxonomy "tags" from NCW';
  }
}


/**
 * Class AbstractNCWTaxonomyTermSource - base for NCW taxonomy migration.
 */
abstract class AbstractNCWTaxonomyTermSource extends AbstractNCWNodeSource {

  public function itemIdentifier($ob) {
    return $ob->tid;
  }

  public function itemUrl($id) {
    return osha_migration_url_data_source('/export/taxonomy_term/' . $id);
  }

  public function fields() {
    return array(
             'tid' => 'tid',
             'name' => 'name',
             'name_field_language' => 'name_field:language',
             'name_field' => 'name_field',
             'format' => 'format',
             'weight' => 'weight',
             'description' => 'description',
             'description_field' => 'description_field',
             'description_field_language' => 'description_field:language',
             'description_field_format' => 'description_field:format',
             'description_field_summary' => 'description_field:summary',
             'field_excluded_from' => 'field_excluded_from',
           ) + $this->contentFields();
  }
}

class SimpleNCWTaxonomyTermSource extends AbstractNCWTaxonomyTermSource {

  public function contentFields() {
    return array();
  }
}

class TagsNCWTaxonomyTermSource extends AbstractNCWTaxonomyTermSource {

  public function contentFields() {
    return array(
      'field_tags_code' => 'field_tags_code',
    );
  }
}

class PublicationTypeNCWTaxonomyTermSource extends AbstractNCWTaxonomyTermSource {

  public function contentFields() {
    return array(
      'field_publication_type_code' => 'field_publication_type_code',
    );
  }
}

class CountryNCWTaxonomyTermSource extends AbstractNCWTaxonomyTermSource {

  public function contentFields() {
    return array(
      'field_iso2' => 'field_iso2',
      'field_flag' => 'field_flag',
      'field_country_status' => 'field_country_status',
    );
  }
}

