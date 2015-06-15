<?php

class NCWTaxonomyCountryMigration extends AbstractNCWTaxonomyTermMigration {

  public function __construct($arguments) {
    parent::__construct($arguments, 'CountryNCWTaxonomyTermSource', 'country', '/export/taxonomy/country');
    $this->description = 'Import taxonomy "country" from NCW';
  }
}

class NCWTaxonomyCountryStatusMigration extends AbstractNCWTaxonomyTermMigration {

  public function __construct($arguments) {
    parent::__construct($arguments, 'SimpleNCWTaxonomyTermSource', 'country_status', '/export/taxonomy/country_status');
    $this->description = 'Import taxonomy "country_status" from NCW';
  }
}

class NCWTaxonomyFOPLinkSectionsMigration extends AbstractNCWTaxonomyTermMigration {

  public function __construct($arguments) {
    parent::__construct($arguments, 'SimpleNCWTaxonomyTermSource', 'fop_link_sections', '/export/taxonomy/fop_link_sections');
    $this->description = 'Import taxonomy "fop_link_sections" from NCW';
  }
}

class NCWTaxonomyNewsletterSectionsMigration extends AbstractNCWTaxonomyTermMigration {

  public function __construct($arguments) {
    parent::__construct($arguments, 'SimpleNCWTaxonomyTermSource', 'newsletter_sections', '/export/taxonomy/newsletter_sections');
    $this->description = 'Import taxonomy "newsletter_sections" from NCW';
  }
}

class NCWTaxonomyPublicationTypeMigration extends AbstractNCWTaxonomyTermMigration {

  public function __construct($arguments) {
    parent::__construct($arguments, 'PublicationTypeNCWTaxonomyTermSource', 'publication_types', '/export/taxonomy/publication_types');
    $this->description = 'Import taxonomy "publication_types" from NCW';
  }
}

class NCWTaxonomyTagsMigration extends AbstractNCWTaxonomyTermMigration {

  public function __construct($arguments) {
    parent::__construct($arguments, 'TagsNCWTaxonomyTermSource', 'tags', '/export/taxonomy/tags');
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
