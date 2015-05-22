<?php

class NCWPublicationsMigration extends AbstractNCWNodeMigration {

  public function __construct($arguments) {
    $endpoint_url = osha_migration_url_data_source('/export/list/publication/road_transport');
    parent::__construct($arguments, 'NCWPublicationsSource', 'publication', $endpoint_url);
    $this->description = 'Import publications from NCW';
  }

  function addFieldMappings() {
    parent::addFieldMappings();
    $this->addUnmigratedDestinations(array(
      'field_activity:source_type',
      'field_activity:ignore_case',
      'field_tags:source_type',
      'field_tags:ignore_case',
      'field_cover_image:file_class',
      'field_cover_image:preserve_files',
      'field_cover_image:destination_dir',
      'field_cover_image:destination_file',
      'field_cover_image:urlencode',
      'field_cover_image:source_dir',
      'field_cover_image:alt',
      'field_file:file_class',
      'field_file:preserve_files',
      'field_file:destination_dir',
      'field_file:destination_file',
      'field_file:source_dir',
      'field_file:urlencode',
      'field_file:description',
      'field_file:display',
      'field_publication_date:rrule',
      'field_publication_related_res:file_class',
      'field_publication_related_res:preserve_files',
      'field_publication_related_res:destination_dir',
      'field_publication_related_res:destination_file',
      'field_publication_related_res:source_dir',
      'field_publication_related_res:urlencode',
      'field_publication_related_res:description',
      'field_publication_related_res:display',
      'field_publication_type:source_type',
      'field_publication_type:ignore_case',
      'field_related_oshwiki_articles',
      'field_thesaurus:source_type',
      'field_thesaurus:ignore_case',
      'field_expiration_date:rrule',
    ));
  }
}


class NCWPublicationsSource extends AbstractNCWNodeSource {

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
      'field_activity',
      'field_archived',
      'field_author',
      'field_author_language',
      'field_character_count',
      'field_cover_image',
      'field_cover_image_language',
      'field_file',
      'field_file_language',
      'field_expiration_date',
      'field_expiration_date_timezone',
      'field_expiration_date_value2',
      'field_page_count',
      'field_publication_bookshop_id',
      'field_publication_bookshop_id_language',
      'field_publication_date',
      'field_publication_date_timezone',
      'field_publication_date_value2',
      'field_publication_related_res',
      'field_publication_related_res_language',
      'field_publication_type',
      'field_thesaurus',
      'field_tags',
      //@todo: 'field_nace_codes',
      //@todo: 'field_aditional_resources',
      //@todo: 'field_related_publications',
    );
    return array_combine($fields, $fields);
  }
}
