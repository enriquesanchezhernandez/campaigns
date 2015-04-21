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
  private static $GROUP_DN = 'cn=%s,ou=MainSite,ou=Sites,dc=osha,dc=europa,dc=eu';
  /** @var LDAPServer $ldap_server */
  private $ldap_server = NULL;

  function all_tests($testName = NULL, $debug = FALSE) {
    /** @var LDAPServer $ldap_server */
    $this->ldap_server = ldap_servers_get_servers(self::$SID, NULL, TRUE);
    foreach (get_class_methods('OSHALDAPTests') as $method) {
      if ((!$testName && strpos($method, 'test_') !== FALSE) || ($testName && $method == $testName)) {
        $username = 'TEST';
        try {
          // Perform cleanup before starting the test
          if (!$debug) {
            $this->deleteLDAPUser($username);
            $this->deleteDrupalUser($username);
          }
          $this->$method($username);
          drush_log($method, 'ok');
          $this->logout();
        }
        catch(Exception $e) {
          drush_set_error('ldap', $method . ' failed (' . $e->getMessage() . ')');
          if (!$debug) {
            $this->deleteLDAPUser($username);
            $this->deleteDrupalUser($username);
          }
        }
      }
    }
  }

  function createLDAPUser($uid, $groups = array()) {
    $ldap_server = $this->ldap_server;
    $result = $ldap_server->search('ou=people,dc=osha,dc=europa,dc=eu', 'uid=' . $uid);
    $udn = sprintf(self::$USER_DN, $uid);
    if (!$result['count']) {
      $entry = array();
      $entry['objectClass'][0] = 'top';
      $entry['objectClass'][1] = 'posixaccount';
      $entry['objectClass'][2] = 'inetOrgPerson';
      $entry['cn'] = $uid;
      $entry['mail'] = user_password() . '@eaudeweb.ro';
      $entry['userpassword'] = 'test';
      $entry['sn'] = $uid;
      $entry['uid'] = $uid;
      $entry['gidNumber'] = 9991;
      $entry['uidNumber'] = 9992;
      $entry['homeDirectory'] = 'ou=Contractors';
      $result = $ldap_server->createLdapEntry($entry, $udn);
      if (!$result) {
        drush_set_error(ldap_errno($ldap_server->connection));
        throw new Exception('Cannot create LDAP user:' . $uid);
      }
    }
    $this->ldapAddUserToGroups($uid, $groups);
  }

  function ldapAddUserToGroups($uid, $groups = array()) {
    $ldap_server = $this->ldap_server;
    foreach($groups as $gcn) {
      $gdn = sprintf(self::$GROUP_DN, $gcn);
      $members = array(
        'memberUid' => array($uid)
      );
      if (!$ldap_server->modifyLdapEntry($gdn, $members)) {
        throw new Exception('Cannot assign user to LDAP group, user:' . $uid, ', group:' . $gcn);
      }
    }
  }

  function ldapRemoveUserFromGroups($uid, $groups) {
    $ldap_server = $this->ldap_server;
    foreach($groups as $gcn) {
      $gdn = sprintf(self::$GROUP_DN, $gcn);
      $members = array('memberUid' => array());
      if (!$ldap_server->modifyLdapEntry($gdn, $members)) {
        throw new Exception('Cannot remove user from LDAP group, user:' . $uid . ', group:' . $gcn);
      }
    }
  }

  function ldapRemoveUser($uid) {
    $ldap_server = $this->ldap_server;
    $result = $ldap_server->search('ou=people,dc=osha,dc=europa,dc=eu', 'uid=' . $uid);
    if ($result['count']) {
      $udn = sprintf(self::$USER_DN, $uid);
      if (!$ldap_server->delete($udn)) {
        throw new Exception('Cannot delete user from LDAP, user:' . $uid);
      }
    }
  }

  function login($username, $password = 'test') {
    global $user;
    $form_state = array(
      'values' => array(
        'name' => $username,
        'pass' => $password,
      )
    );
    drupal_form_submit('user_login', $form_state);
    if ($user->uid < 2) {
      throw new Exception('Failed to login user: ' . $username);
    }
  }

  function deleteDrupalUser($username) {
    $user = user_load_by_name($username);
    if (!empty($user->uid)) {
      user_delete($user->uid);
    }
  }

  function deleteLDAPUser($uid) {
    $ldap_server = $this->ldap_server;
    // Detach from all groups
    $result = $ldap_server->search('ou=MainSite,ou=Sites,dc=osha,dc=europa,dc=eu', 'memberUid=' . $uid);
    if ($result['count'] > 0) {
      unset($result['count']);
      foreach($result as $group) {
        if (!$ldap_server->modifyLdapEntry($group['dn'], array('memberUid' => array()))) {
          throw new Exception('Failed to remove user from LDAP group, user:' . $uid, ', group:' . $group['cn']);
        }
      }
    }
    // Remove the account
    $users = $ldap_server->search('ou=Contractors,ou=people,dc=osha,dc=europa,dc=eu', 'uid=' . $uid);
    if ($users['count'] > 0) {
      $dn = sprintf(self::$USER_DN, $uid);
      if (!$ldap_server->delete($dn)) {
        throw new Exception('Failed to delete user from LDAP:' . $uid);
      }
    }
  }

  function logout() {
    global $user;
    $tmp = NULL;
    user_module_invoke('logout', $tmp, $user);
    $user = drupal_anonymous_user();
  }

  function test_LDAP_US_US_01($username = 'TEST') {
    $this->createLDAPUser($username);
    $this->login($username);
  }

  function test_LDAP_US_US_02($username = 'TEST') {
    $this->createLDAPUser($username);
    // Login with the user so the account can be provisioned inside Drupal
    $this->login($username);
    $this->logout();
    $this->deleteLDAPUser($username);
    // Try to authenticated when the user no longer exists in LDAP
    global $user;
    try {
      $this->login($username);
    }
    catch(Exception $e) {
      // Expected.
    }
    if ($user->uid != 0) {
      throw new ErrorException('User was still able to login');
    }
  }

  function test_LDAP_APPRV_US_01($username = 'TEST') {
    global $user;
    $this->createLDAPUser($username, array('APPROVER'));
    $this->login($username);
    // User has gained Approver role in Drupal
    if (!in_array('Approver', $user->roles)) {
      throw new Exception('User is missing Approver role');
    }
  }

  function test_LDAP_APPRV_US_02($username = 'TEST') {
    global $user;
    $this->createLDAPUser($username, array('APPROVER'));
    $this->login($username);
    // User has gained Approver role in Drupal
    if (!in_array('Approver', $user->roles)) {
      throw new Exception('User is missing Approver role');
    }
    $count = db_select('entity_collection_storage', NULL)
      ->condition('name', 'approvers')->condition('eid', $user->uid)->countQuery()
      ->execute()->fetchField();
    if ($count != 1 ) {
      throw new Exception('User is NOT in the "approvers" entity collection');
    }

    $this->logout();
    $this->ldapRemoveUserFromGroups($username, array('APPROVER'));

    // Reset the entity collection static cache and entity cache
    drupal_static_reset('entity_collection_load');
    entity_get_controller('entity_collection')->resetCache();

    // User is revoked Approver is removed from the approvers entity_collection
    $this->login($username);
    $count = db_select('entity_collection_storage', NULL)
      ->condition('name', 'approvers')->condition('eid', $user->uid)->countQuery()
      ->execute()->fetchField();
    if ($count != 0) {
      throw new Exception('User is Approver after being revoked from LDAP');
    }
    $this->logout();
  }

  function test_LDAP_EDT_US_01($username = 'TEST') {
    global $user;
    $this->createLDAPUser($username, array('CAREER_EDT', 'CONTUS_EDT'));
    $this->login($username);
    // User has gained Editor role in Drupal
    if (count($user->roles) != 2 || !in_array('Editor', $user->roles) || !in_array('authenticated user', $user->roles)) {
      throw new Exception('User has wrong roles:' . print_r(array_values($user->roles), TRUE));
    }
  }

  function test_LDAP_EDT_US_02($username = 'TEST') {
    global $user;
    $this->createLDAPUser($username, array('CAREER_EDT', 'CONTUS_EDT'));
    $this->login($username);
    // User has gained Editor role in Drupal
    if (count($user->roles) != 2 || !in_array('Editor', $user->roles) || !in_array('authenticated user', $user->roles)) {
      throw new Exception('User has wrong roles:' . print_r(array_values($user->roles), TRUE));
    }
    // Check section assignment
    module_load_include('admin.inc', 'workbench_access');
    workbench_access_user_load_data($user);
    $sections = $user->workbench_access;
    //@todo fix when switching to taxonomy access from menu
    if (count($sections) != 1 || !array_key_exists(1717, $sections)) {
      throw new Exception('User assigned to wrong sections:' . print_r(array_values($sections), TRUE));
    }
  }

  function test_LDAP_EDT_US_04($username = 'TEST') {
    global $user;
    $this->createLDAPUser($username, array('CAREER_EDT', 'CONTUS_EDT'));
    $this->login($username);
    // User has gained Editor role in Drupal
    if (count($user->roles) != 2 || !in_array('Editor', $user->roles) || !in_array('authenticated user', $user->roles)) {
      throw new Exception('User has wrong roles:' . print_r(array_values($user->roles), TRUE));
    }

    $this->logout();
    $this->deleteLDAPUser($username);
    $this->createLDAPUser($username);
    $this->login($username);
    // User has gained Editor role in Drupal
    if (count($user->roles) != 1 || !in_array('authenticated user', $user->roles)) {
      throw new Exception('User has wrong roles:' . print_r(array_values($user->roles), TRUE));
    }
  }

  function test_osha_authentication_map_section() {
    $sid = osha_authentication_map_section('BLOG');
    //@todo fix when switching to taxonomy access from menu
    if ($sid != 1717) {
      throw new Exception('Wrong section mapped');
    }
  }

  function test_osha_authentication_map_role_and_sections() {
    $data = array(
      'cn=AWRACT_EDT,ou=MainSite,ou=Sites,dc=osha,dc=europa,dc=eu',
      'cn=AWRACT_PM,ou=MainSite,ou=Sites,dc=osha,dc=europa,dc=eu',
      'cn=APPROVER,ou=MainSite,ou=Sites,dc=osha,dc=europa,dc=eu',
      'cn=RVMN,ou=MainSite,ou=Sites,dc=osha,dc=europa,dc=eu',
    );
    list($roles, $sections) = osha_authentication_map_role_and_sections($data);
    if (count($roles) != 4
        || !in_array('Editor', $roles)
        || !in_array('Project Manager', $roles)
        || !in_array('Approver', $roles)
        || !in_array('Review Manager', $roles)) {
      throw new Exception('Wrong roles mapped: ' . print_r($roles, TRUE));
    }
    if (count($sections) != 1 && !in_array(1717, $sections)) {
      throw new Exception('Wrong section mapped:' . print_r($sections, TRUE));
    }
  }

  function test_osha_authentication_map_role_and_sections_invalid_dn() {
    $data = array(
      'cn=_INVALID,ou=MainSite,ou=Sites,dc=osha,dc=europa,dc=eu',
      'cn=INVALID_,ou=MainSite,ou=Sites,dc=osha,dc=europa,dc=eu',
      'cn=PM_INVALID,ou=MainSite,ou=Sites,dc=osha,dc=europa,dc=eu',
      'BLOG_PM,ou=MainSite,ou=Sites,dc=osha,dc=europa,dc=eu',
    );
    list($roles, $sections) = osha_authentication_map_role_and_sections($data);
    if (count($roles) != 0) {
      throw new Exception('Failed to filter invalid roles/sections');
    }
  }

  function test_password_change() {

  }
}
