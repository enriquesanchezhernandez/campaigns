<?php
/**
 * @file
 * Simple test that shows that PHPUnit works.
 */

/**
 * Author: Cristian Romanescu <cristi _at_ eaudeweb dot ro>
 * Created: 201412151936
 */

class TestFrameworkBootstrapTest extends DrupalWebTestCase {

  public function setUp() {
    global $base_url;
    $base_url = UPAL_WEB_URL;
    $base_url = 'http://osha.localhost:8000';
    $this->cookieFile = '/tmp/cookie.txt';
    $this->cookies = array();
    parent::setUp();
  }

  /**
   * Test Drupal API availability.
   */
  public function testBootstrap() {
    $this->assertNotNull(user_load(1));
  }

  public function testLogin() {
    global $language, $language_url;
    $language_url = $language = i18n_language_load('en');

    $admin = (object) array('name' => 'admin', 'pass_raw' => 'password');
    $this->drupalLogin($admin);

    $data = $this->drupalGet('admin/config');
    $this->assertText('AddToAny');
  }
}

