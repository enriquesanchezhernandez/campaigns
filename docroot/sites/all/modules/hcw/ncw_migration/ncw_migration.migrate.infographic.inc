<?php

class NCWInfographicMigration extends AbstractNCWNodeMigration {

  public function __construct($arguments) {
    $endpoint_url = osha_migration_url_data_source('/export/list/infographic/ageing_and_osh');
    parent::__construct($arguments, 'NCWInfographicSource', 'infographic', $endpoint_url);
    $this->description = 'Import infographics from NCW';
  }

  function addFieldMappings() {
    parent::addFieldMappings();
    $this->addUnmigratedDestinations(array(
      'field_activity:source_type',
      'field_activity:ignore_case',
      'field_tags:source_type',
      'field_tags:ignore_case',
      'field_image:file_class',
      'field_image:preserve_files',
      'field_image:destination_dir',
      'field_image:destination_file',
      'field_image:source_dir',
      'field_image:urlencode',
      'field_image:alt',
      'field_image:title',
      'field_publication_date:rrule',
    ));
    $this->ignoreMetatagMigration();
  }
}


class NCWInfographicSource extends AbstractNCWNodeSource {

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
      'field_summary',
      'field_summary_format',
      'field_summary_language',
      'field_image',
      'field_image_language',
      'field_thumbnail',
      'field_thumbnail_language',
      'field_file',
      'field_file_language',
      'field_publication_date',
      'field_publication_date_timezone',
      'field_publication_date_value2',
      'field_tags',
      //@todo: 'field_twin_infographics',
    );
    return array_combine($fields, $fields);
  }
}
