<?php

class NCWNoteMigration extends AbstractNCWNodeMigration {

  public function __construct($arguments) {
    $endpoint_url = osha_migration_url_data_source('/export/notetoeditor');
    parent::__construct($arguments, 'NCWNoteSource', 'note_to_editor', $endpoint_url);
    $this->description = 'Import notes to editor from NCW';
  }

  function addFieldMappings() {
    parent::addFieldMappings();
    $this->addUnmigratedDestinations(array(

    ));
    $this->ignoreMetatagMigration();
  }
}


class NCWNoteSource extends AbstractNCWNodeSource {

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
      'field_character_count',
      'field_page_count',
    );
    return array_combine($fields, $fields);
  }
}
