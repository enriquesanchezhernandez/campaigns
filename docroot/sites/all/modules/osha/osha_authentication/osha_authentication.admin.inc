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

function osha_authentication_user_roles_sync($user, $proposed_roles) {
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

function osha_map_ldap_role_to_drupal_role($ldap_groups) {
  $ret = array();
  $smart_mappings = array(
    'EDT' => 'Editor',
    'PM' => 'Project Manager',
    'RVMN' => 'Review Manager',
    'APPROVER' => 'Approver',
    'LAYVAL' => 'Layout Validator',
    'TRLIAS' => 'Translation Liaison',
    'TRLMN' => 'Translation Manager',
  );
  foreach ($ldap_groups as $group_dn) {
    $ldap_group_cn = array();
    // LDAP group DN patterns:
    // * cn=SECTION_ROLE,ou=MainSite,ou=Sites,dc=osha,dc=europa,dc=eu
    // * cn=ROLE,ou=MainSite,ou=Sites,dc=osha,dc=europa,dc=eu
    if (preg_match('/[A-Z\_]*/i', $group_dn, $ldap_group_cn, 0, 3) && count($ldap_group_cn) == 1) {
      list($section, $role) = explode('_', $ldap_group_cn[0]);
      if (empty($role)) {
        $role = $section;
      }
      if (array_key_exists($role, $smart_mappings)) {
        $ret[$group_dn] = $smart_mappings[$role];
      }
      else {
        //@todo: watchdog
      }
    }
  }
  return $ret;
}
