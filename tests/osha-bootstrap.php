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

    global $language, $language_url, $language_content;
    $language_content = $language_url = $language = i18n_language_load('en');

    $this->cleanup();
  }

  /**
   * Login with admin account.
   */
  public function loginAsAdmin() {
    $admin = (object) array('name' => 'admin', 'pass_raw' => 'password');
    $this->drupalLogin($admin);
  }

  /**
   * Login as custom account.
   *
   * @param string $username
   *   Username to login with
   * @param string $password
   *   Password. By default all dev instance are set to 'password'.
   */
  public function loginAs($username, $password = 'password') {
    $admin = (object) array('name' => $username, 'pass_raw' => $password);
    $this->drupalLogin($admin);
  }


}
