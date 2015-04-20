<?php

/**
 * Class OSHALDAPTests tests LDAP use cases.
 *
 * Prerequisites:
 *
 * 1. Have a read test user: uid=TEST_READ,ou=Contractors,ou=people,dc=osha,dc=europa,dc=eu
 */
class OSHALDAPTests {

  private static $SID = 'edw';
  private static $USER_DN = 'uid=%s,ou=Contractors,ou=people,dc=osha,dc=europa,dc=eu';

  function all_tests($testName = NULL) {
    foreach (get_class_methods('OSHALDAPTests') as $method) {
      if ((!$testName && strpos($method, 'test_LDAP') !== FALSE) || ($testName && $method == $testName)) {
        try {
          $this->$method();
          drush_log($method, 'ok');
        }
        catch(Exception $e) {
          drush_set_error('ldap', $method . ' failed (' . $e->getMessage() . ')');
        }
      }
    }
  }

  function createLDAPUser($uid) {
    /** @var LDAPServer $ldap_server */
    $ldap_server = ldap_servers_get_servers(self::$SID, NULL, TRUE);
    $result = $ldap_server->search('ou=people,dc=osha,dc=europa,dc=eu', 'uid=' . $uid);
    if (!$result['count']) {
      $entry = array();
      $entry['objectClass'][0] = 'top';
      $entry['objectClass'][1] = 'posixaccount';
      $entry['objectClass'][2] = 'inetOrgPerson';
      $entry['cn'] = 'TEST_TEMP';
      $entry['mail'] = user_password() . '@eaudeweb.ro';
      $entry['userpassword'] = 'test';
      $entry['sn'] = 'TEST_TEMP';
      $entry['uid'] = 'TEST_TEMP';
      $entry['gidNumber'] = 9991;
      $entry['uidNumber'] = 9992;
      $entry['homeDirectory'] = 'ou=Contractors';
      return $ldap_server->createLdapEntry($entry, sprintf(self::$USER_DN, $uid));
    }
    return TRUE;
  }

  function login($username, $password) {
    global $user;
    $form_state = array(
      'values' => array(
        'name' => $username,
        'pass' => $password,
      )
    );
    drupal_form_submit('user_login', $form_state);
    if ($user->uid < 2) {
      return FALSE;
    }
    else {
      return $user->uid;
    }
  }

  function deleteDrupalUser($name) {
    $user = user_load_by_name($name);
    if (!empty($user->uid)) {
      user_delete($user->uid);
    }
  }

  function deleteLDAPUser($uid) {
    $result = FALSE;
    /** @var LDAPServer $ldap_server */
    $ldap_server = ldap_servers_get_servers(self::$SID, NULL, TRUE);
    $result = $ldap_server->search('ou=people,dc=osha,dc=europa,dc=eu', 'uid=' . $uid);
    if ($result['count'] > 0) {
      return $ldap_server->delete(sprintf(self::$USER_DN, $uid));
    }
    return TRUE;
  }

  function logout() {
    global $user;
    $user = NULL;
    session_regenerate_id();
  }

  function test_LDAP_US_US_01() {
    if ($this->login('TEST_READ', 'test')) {
      // Cleanup the test user after checking
      $this->deleteDrupalUser('TEST_READ');
      $this->logout();
    }
    else {
      throw new Exception('Cannot login user');
    }
  }

  function test_LDAP_US_US_02() {
    if (!$this->createLDAPUser('TEST_TEMP')) {
      throw new Exception('Cannot create LDAP temporary user');
    }
    try {
      // Login with the user so the account can be created inside Drupal
      if (!$this->login('TEST_TEMP', 'test')) {
        throw new Exception('Cannot login temporary user in Drupal');
      }
      $this->logout();
      // Delete user from LDAP
      if (!$this->deleteLDAPUser('TEST_TEMP')) {
        throw new Exception('Cannot delete LDAP temporary user');
      }
      // Try to authenticated even when the user no longer exists in LDAP
      if ($this->login('TEST_TEMP', 'test')) {
        throw new Exception('User was still able to login');
      }
    }
    catch (Exception $e) {
      $this->deleteLDAPUser('TEST_TEMP');
      throw $e;
    }
  }
}
