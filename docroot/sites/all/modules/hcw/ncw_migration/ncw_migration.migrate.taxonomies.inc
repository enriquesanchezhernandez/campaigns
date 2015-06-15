<?php

class NCWTaxonomyCountryMigration extends AbstractNCWTaxonomyTermMigration {

  public function __construct($arguments) {
    $endpoint_url = $this->getMigrationURL('/export/taxonomy/country');
    parent::__construct($arguments, 'CountryNCWTaxonomyTermSource', 'country', $endpoint_url);
    $this->description = 'Import taxonomy "country" from NCW';
  }
}

class NCWTaxonomyCountryStatusMigration extends AbstractNCWTaxonomyTermMigration {

  public function __construct($arguments) {
    $endpoint_url = $this->getMigrationURL('/export/taxonomy/country_status');
    parent::__construct($arguments, 'SimpleNCWTaxonomyTermSource', 'country_status', $endpoint_url);
    $this->description = 'Import taxonomy "country_status" from NCW';
  }
}

class NCWTaxonomyFOPLinkSectionsMigration extends AbstractNCWTaxonomyTermMigration {

  public function __construct($arguments) {
    $endpoint_url = $this->getMigrationURL('/export/taxonomy/fop_link_sections');
    parent::__construct($arguments, 'SimpleNCWTaxonomyTermSource', 'fop_link_sections', $endpoint_url);
    $this->description = 'Import taxonomy "fop_link_sections" from NCW';
  }
}

class NCWTaxonomyNewsletterSectionsMigration extends AbstractNCWTaxonomyTermMigration {

  public function __construct($arguments) {
    $endpoint_url = $this->getMigrationURL('/export/taxonomy/newsletter_sections');
    parent::__construct($arguments, 'SimpleNCWTaxonomyTermSource', 'newsletter_sections', $endpoint_url);
    $this->description = 'Import taxonomy "newsletter_sections" from NCW';
  }
}

class NCWTaxonomyPublicationTypeMigration extends AbstractNCWTaxonomyTermMigration {

  public function __construct($arguments) {
    $endpoint_url = $this->getMigrationURL('/export/taxonomy/publication_types');
    parent::__construct($arguments, 'PublicationTypeNCWTaxonomyTermSource', 'publication_types', $endpoint_url);
    $this->description = 'Import taxonomy "publication_types" from NCW';
  }
}

class NCWTaxonomyTagsMigration extends AbstractNCWTaxonomyTermMigration {

  public function __construct($arguments) {
    $endpoint_url = $this->getMigrationURL('/export/taxonomy/tags');
    parent::__construct($arguments, 'TagsNCWTaxonomyTermSource', 'tags', $endpoint_url);
    $this->description = 'Import taxonomy "tags" from NCW';
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
