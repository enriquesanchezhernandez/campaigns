<?php

class NCWEventsMigration extends AbstractNCWMigration {

  public function __construct($arguments) {
    parent::__construct($arguments, 'NCWEventsSource');
    $this->description = 'Import Events from NCW';
  }

  function addFieldMappings() {
    $this->addFieldMapping('field_original_id', 'id');
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('title_field', 'title');
    $this->addFieldMapping('title_field:language', 'title_languages');
    $this->addFieldMapping('field_treaty', 'treaty');
    $this->addFieldMapping('field_country', 'country');

    $this->addFieldMapping('field_sorting_date', 'submission');
    $this->addFieldMapping('field_document_url', 'url');
    // $this->addFieldMapping('field_report_type', 'type');
    $this->addFieldMapping('changed', 'updated');
  }
}


class NCWEventsSource extends AbstractNCWSource {

  /**
   * The list of available fields to map from the source, keyed by field name.
   */
  public function fields() {
    return array(
      'id' => 'Remote primary key',
      //@todo: all fields
    );
  }
}
