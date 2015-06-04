<?php

class NCWEventsMigration extends AbstractNCWNodeMigration {

  public function __construct($arguments) {
    $endpoint_url = osha_migration_url_data_source('/export/list/events/accident_prevention');
    parent::__construct($arguments, 'NCWEventsSource', 'events', $endpoint_url);
    $this->description = 'Import events from NCW';
  }

  function addFieldMappings() {
    parent::addFieldMappings();
    $this->addUnmigratedDestinations(array(
      'field_activity:source_type',
      'field_activity:ignore_case',
      'field_city:language',
      'field_tags:source_type',
      'field_agency_contact_reply:language',
      'field_agency_initial_contact:language',
      'field_agency_rep_confirmed:language',
      'field_organised_by:ignore_case',
      'field_organised_by:source_type',
      'field_organization:language',
      'field_start_date:rrule',
      'field_tags:ignore_case',
      'field_related_documents:file_class',
      'field_related_documents:preserve_files',
      'field_related_documents:destination_dir',
      'field_related_documents:destination_file',
      'field_related_documents:source_dir',
      'field_related_documents:urlencode',
      'field_related_documents:description',
      'field_related_documents:display',
      'field_website_of_event:language',
    ));
    $this->ignoreMetatagMigration();
  }
}


class NCWEventsSource extends AbstractNCWNodeSource {

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
      'field_country_code',
      'field_city',
      'field_agency_role',
      'field_tags',
      'field_adonis',
      'field_adonis_language',
      'field_agency_contact_reply',
      'field_agency_initial_contact',
      'field_agency_rep_confirmed',
      'field_color',
      'field_comments_summary_after_eve',
      'field_comments_summary_after_eve_language',
      'field_event_in_amp',
      'field_event_type',
      'field_for_the_web',
      'field_number_of_attendees',
      'field_organised_by',
      'field_organization',
      'field_satisfaction_rate',
      'field_start_date',
      'field_start_date_timezone',
      'field_start_date_value2',
      'field_unit_ref',
      'field_website_of_event',
      'field_website_of_event_title',
      'field_website_of_event_attributes',
      'field_related_documents',
      'field_related_documents_language',
    );
    return array_combine($fields, $fields);
  }
}
