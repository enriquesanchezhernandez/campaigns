<?php

require_once 'bootstrap.php';

// We set global language variables to avoid error:
// <h1>Uncaught exception thrown in shutdown function.</h1>
// <p>PHPUnit_Framework_Error_Notice: Trying to get property of non-object in
// PHPUnit_Util_ErrorHandler::handleError() (line 7674 of common.inc).</p><hr />
global $language, $language_url, $language_content;
$language_content = $language_url = $language = (object) array(
  'language' => 'en', 'name' => 'English',  'native' => 'English',
  'direction' => 0, 'enabled' => 1, 'plurals' => 0, 'formula' => '',
  'domain' => '', 'prefix' => 'en', 'weight' => 1, 'javascript' => '',
);


class OshaWebTestCase extends DrupalWebTestCase {

  /**
   * {@inheritdoc}
   */
  public function setUp() {
    $this->cookieFile = '/tmp/cookie.txt';
    $this->cookies = array();
    parent::setUp();
  }

  public function setupLanguage($language = 'en', $name = 'English') {
    global $language, $language_url, $language_content;
    $language_content = $language_url = $language = (object) array(
      'language' => 'en', 'name' => $name,  'native' => $name,
      'direction' => 0, 'enabled' => 1, 'plurals' => 0, 'formula' => '',
      'domain' => '', 'prefix' => 'en', 'weight' => 1, 'javascript' => '',
    );
  }

  /**
   * Login with admin account.
   */
  public function loginAsAdmin($password = 'password') {
    global $user;
    $user = user_load(1);
    $this->assertNotNull($user, "Could not login admin");
    $user->pass_raw = $password;
    $this->drupalLogin($user);
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
    global $user;
    $user = user_load_by_name($username);
    $this->assertNotNull($user, "Could not login $username");
    $user->pass_raw = $password;
    $this->drupalLogin($user);
  }

  /**
   * Executed when a single test is over.
   */
  public function tearDown() {
    $this->cleanup();
  }

  /**
   * This function is called in setUp and tearDown to ensure clean environment.
   *
   * Use this function to delete any content created by this test.
   */
  public function cleanup() {}
}
