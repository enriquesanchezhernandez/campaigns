<?php

require_once 'bootstrap.php';

class OshaWebTestCase extends DrupalWebTestCase {

  /**
   * {@inheritdoc}
   */
  public function setUp() {

    $this->cookieFile = '/tmp/cookie.txt';
    $this->cookies = array();
    parent::setUp();

    global $language, $language_url;
    $language_url = $language = i18n_language_load('en');
  }
}
