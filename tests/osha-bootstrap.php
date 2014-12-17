<?php

require_once 'bootstrap.php';

class OshaWebTestCase extends DrupalWebTestCase {

  public function setUp() {
    $this->cookieFile = '/tmp/cookie.txt';
    $this->cookies = array();
    parent::setUp();
  }

}
