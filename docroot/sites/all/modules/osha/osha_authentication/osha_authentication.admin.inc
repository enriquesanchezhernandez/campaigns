<?php

/**
 * Ensure if user is approver, exists in the default list of approvers
 *
 * @param $is_approver
 */
function osha_authentication_user_login_approver($account, $is_approver) {
  $approvers_collection = entity_collection_load('approvers');
  /** @var EntityCollectionTreeNode $users */
  $users = $approvers_collection->getTree();
  if ($is_approver && !array_key_exists('user:' . $account->uid, $users->list)) {
    $entity_id = entity_id('user', $account);
    $item = new EntityCollectionTreeNode('user', $entity_id, $account);
    entity_collection_append_item($approvers_collection, $item);
  }
  if (!$is_approver && array_key_exists('user:' . $account->uid, $users->list)) {
    entity_collection_content_delete($approvers_collection, 'user', array($account->uid));
  }
}

function osha_authentication_extract_user_roles($user, $proposed_roles) {
  $ret = array();
  $roles_names = array('authenticated user');
  if (in_array('administrator', $user->roles)) {
    $roles_names[] = 'administrator';
  }
  $roles_names = array_merge($roles_names, array_values($proposed_roles));
  // Load the actual roles from DB
  foreach($roles_names as $role_name) {
    if ($r = user_role_load_by_name($role_name)) {
      $ret[$r->rid] = $role_name;
    }
    else {
      // @todo:
    }
  }
  return $ret;
}

function osha_authentication_map_role_and_sections($ldap_groups) {
  $roles = array();
  $sections = array();
  $smart_mappings = array(
    'EDT' => 'Editor',
    'PM' => 'Project Manager',
    'RVMN' => 'Review Manager',
    'APPROVER' => 'Approver',
    'LAYVAL' => 'Layout Validator',
    'TRLIAS' => 'Translation Liaison',
    'TRLMN' => 'Translation Manager',
  );
  $provisional_sections = array();
  foreach ($ldap_groups as $group_dn) {
    $ldap_group_cn = array();
    if (strpos($group_dn, 'cn=') !== 0) {
      watchdog('osha_authentication',
        'Invalid group DN: !dn. Must start with cn=',
        array('!dn' => $group_dn),
        WATCHDOG_ERROR
      );
      continue;
    };
    // LDAP group DN patterns:
    // * cn=SECTION_ROLE,ou=MainSite,ou=Sites,dc=osha,dc=europa,dc=eu
    // * cn=ROLE,ou=MainSite,ou=Sites,dc=osha,dc=europa,dc=eu
    if (preg_match('/[A-Z\_]*/i', $group_dn, $ldap_group_cn, 0, 3) && count($ldap_group_cn) == 1) {
      list($section, $role) = explode('_', $ldap_group_cn[0]);
      if (empty($role)) {
        $role = $section;
      }
      else {
        $provisional_sections[] = $section;
      }
      if (array_key_exists($role, $smart_mappings)) {
        if (!in_array($role, $roles)) {
          $roles[] = $smart_mappings[$role];
        }
      }
      else {
        watchdog('osha_authentication',
          'Unable to extract role !role from group DN: !dn, please check naming scheme syntax (cn=$SECTION_$ROLE or cn=$ROLE)',
          array('!role' => $role, '!dn' => $group_dn),
          WATCHDOG_ERROR
        );
      }
    }
  }
  // Decode the sections according to mappings done in taxonomy
  foreach($provisional_sections as $section) {
    if ($tid = osha_authentication_map_section($section)) {
      if (!in_array($tid, $sections)) {
        $sections[] = $tid;
      }
    }
  }
  return array($roles, $sections);
}

function osha_authentication_map_section($ldap_section) {
  //@TODO: Implement when the access is mapped to taxonomy instead of menu
  return 1717;
}
