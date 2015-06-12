<?php

/**
 * Class NCWPressContactMigration migrates press contacts
 *
 * Set hwc_migration_press_contacts_url variable for explicit source URL.
 */
class NCWPressContactMigration extends AbstractNCWNodeMigration {

  public function __construct($arguments) {
    $endpoint_url = $this->getMigrationURL('/export/presscontact');
    parent::__construct($arguments, 'NCWPressContactSource', 'press_contact', $endpoint_url);
    $this->description = 'Import press contacts from NCW';
  }

  function addFieldMappings() {
    parent::addFieldMappings();
    $this->addUnmigratedDestinations(array(
      'field_city:language',
      'field_contact_type:source_type',
      'field_contact_type:ignore_case',
      'field_country:source_type',
      'field_country:ignore_case',
      'field_personal_title:language',
      'field_press_contact_organization:language',
      'field_press_contact_phone:language',
      'field_website:language',
      'field_wg_category:source_type',
      'field_wg_category:ignore_case',
      'field_wg_role_1:source_type',
      'field_wg_role_1:ignore_case',
      'field_wg_role_2:source_type',
      'field_wg_role_2:ignore_case',
      'field_zip_code:language',
    ));
    $this->ignoreMetatagMigration();
  }
}


class NCWPressContactSource extends AbstractNCWNodeSource {

  /**
   * The list of available fields to map from the source, keyed by field name.
   */
  public function contentFields() {
    $fields = array(
      'title_field',
      'title_field_language',
      //@todo: 'field_contact_type',
      'field_press_contact_job_title',
      'field_press_contact_job_title_language',
      'field_personal_title',
      'field_press_contact_organization',
      'field_press_contact_location',
      'field_press_contact_location_language',
      'field_press_contact_location_format',
      'field_city',
      'field_country',
      'field_zip_code',
      'field_press_contact_email',
      'field_press_contact_phone',
      'field_wg_role_1',
      'field_wg_role_2',
      'field_wg_category',
      'field_website',
      'field_website_title',
      'field_website_attributes',
    );
    return array_combine($fields, $fields);
  }
}
