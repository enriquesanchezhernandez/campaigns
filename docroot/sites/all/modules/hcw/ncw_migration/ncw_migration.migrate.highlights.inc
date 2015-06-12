<?php

/**
 * Class NCWHighlightMigration migrates highlights into news content type
 *
 * Set hwc_migration_highlights_url variable for explicit source URL.
 */
class NCWHighlightMigration extends AbstractNCWNodeMigration {

  public function __construct($arguments) {
    $endpoint_url = $this->getMigrationURL('/export/list/highlight/women_and_osh');
    parent::__construct($arguments, 'NCWHighlightSource', 'news', $endpoint_url);
    $this->description = 'Import highlights (into news) from NCW';
  }

  function addFieldMappings() {
    parent::addFieldMappings();

    $this->addFieldMapping('field_tags:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_tags:create_term')->defaultValue(FALSE);
    $this->addFieldMapping('field_tags', 'field_tags');

    $this->addUnmigratedDestinations(array(
      'field_activity:source_type',
      'field_activity:ignore_case',
      'field_tags:ignore_case',
      'field_expiration_date:rrule',
      'field_image:file_class',
      'field_image:preserve_files',
      'field_image:destination_dir',
      'field_image:destination_file',
      'field_image:source_dir',
      'field_image:urlencode',
      'field_image:alt',
      'field_image:title',
      'field_publication_date:rrule',
      'field_summary',
      'field_summary:format',
      'field_summary:language',
      'field_image_caption',
      'field_image_caption:language',
    ));
    $this->ignoreMetatagMigration();
  }

  protected function getManuallyMigratedFields() {
    return array('field_tags');
  }

  function prepareRow($row) {
    parent::prepareRow($row);
    $row->field_tags = osha_migration_normalize_migrated_term_reference($row->field_tags, 'tax_tags');
  }
}


class NCWHighlightSource extends AbstractNCWNodeSource {

  /**
   * The list of available fields to map from the source, keyed by field name.
   */
  public function contentFields() {
    $fields = array(
      'title_field',
      'title_field_language',
      'body',
      'body_language',
      'body_summary',
      'body_format',
      'field_image',
      'field_image_language',
      'field_publication_date',
      'field_publication_date_timezone',
      'field_publication_date_value2',
      'field_expiration_date',
      'field_expiration_date_timezone',
      'field_expiration_date_value2',
      'field_tags',
      'field_archived',
      'field_character_count',
      'field_page_count',
      //@todo: 'field_aditional_resources',
    );
    return array_combine($fields, $fields);
  }
}
