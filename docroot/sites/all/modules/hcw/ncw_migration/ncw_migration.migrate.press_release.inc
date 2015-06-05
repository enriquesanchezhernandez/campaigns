<?php

class NCWPressMigration extends AbstractNCWNodeMigration {

  public function __construct($arguments) {
    $endpoint_url = osha_migration_url_data_source('/export/list/press_release/campaign_2014_2015');
    parent::__construct($arguments, 'NCWPressSource', 'press_release', $endpoint_url);
    $this->description = 'Import press releases from NCW';
  }

  function addFieldMappings() {
    parent::addFieldMappings();
    $this->addUnmigratedDestinations(array(
      'field_activity:source_type',
      'field_activity:ignore_case',
      'field_tags:source_type',
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
      'field_pr_embargo_date:rrule',
    ));
    $this->ignoreMetatagMigration();
  }
}


class NCWPressSource extends AbstractNCWNodeSource {

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
      'field_image_language',
      'field_publication_date',
      'field_publication_date_timezone',
      'field_publication_date_value2',
      'field_pr_embargo_date',
      'field_pr_embargo_date_timezone',
      'field_pr_embargo_date_value2',
      'field_expiration_date',
      'field_expiration_date_timezone',
      'field_expiration_date_value2',
      'field_image',
      'field_quote',
      'field_quote_format',
      'field_quote_language',
      'field_tags',
      'field_archived',
      'field_character_count',
      'field_page_count',
      //'field_nace_codes',
      //'field_pr_notes_to_editor',
      //'field_aditional_resources',
    );
    return array_combine($fields, $fields);
  }
}
