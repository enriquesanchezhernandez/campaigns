<?php

function osha_workflow_workbench_review_managers($access_type = NULL, $access_type_id = NULL) {
  if (is_null($access_type) || is_null($access_type_id)) {
    // Set proper breadcrumb trails.
    $breadcrumb[] = t('Review Managers');
    $current = drupal_get_breadcrumb();
    $current = array_merge($current, $breadcrumb);
    drupal_set_breadcrumb($current);

    // Ensure that we have configured access controls.
    if (!$active = workbench_access_get_active_tree()) {
      return workbench_access_configuration_needed_message();
    }
    $active['access_scheme']['access_id'] = NULL;
    $output = '<h2>' . t('Editorial assignments by review manager') . '</h2>';
    $output .= '<p>' . t('The following sections are currently active.');
    if (user_access('administer workbench access')) {
      $output .= ' ' . t('You may <a href="!url">enable or disable sections</a>.', array('!url' => url('admin/config/workbench/access/sections'))) . '</p>';
    }
    $rows = array();
    foreach ($active['tree'] as $access_id => $section) {
      if (!isset($active['active'][$access_id])) {
        continue;
      }
      // Nest the children so the user understands the hierarchy.
      if ($section['depth'] == 0 || !isset($active['active'][$section['parent']])) {
        $parent = $section['name'];
      }
      $row = array(
        str_repeat('-', $section['depth'] ) . ' ' . l($section['name'], 'admin/config/workbench/access/review-managers/' . $active['access_scheme']['access_type'] . '/' . $access_id),
      );
      $roles = workbench_access_get_roles('access workbench access by role');
      if (empty($roles)) {
        if (user_access('administer permissions')) {
          return t('To continue, at least one role must be have the <a href="!url">Allow all members of this role to be assigned to Workbench Access sections</a> permission', array('!url' => url('admin/people/permissions', array('fragment' => 'module-workbench_access'))));
        }
        else {
          return t('There are no roles who have permission to edit sections. Please contact a site administrator.');
        }
      }
      if (!isset($roles[DRUPAL_AUTHENTICATED_RID])) {
        $pms = db_query("SELECT wau.uid as uid, us.name as name FROM {osha_workflow_access_rm} wau
            INNER JOIN {users_roles} ur ON wau.uid = ur.uid
            INNER JOIN {users} us ON wau.uid = us.uid
            WHERE wau.access_scheme = :access_scheme AND wau.access_id = :access_id
            AND ur.rid IN (:rids)",
          array(':access_scheme' => $active['access_scheme']['access_type'], ':access_id' => $access_id, ':rids' => array_keys($roles))
        )->fetchField();
      }
      else {
        $pms = db_query("SELECT wau.uid as uid, us.name as name FROM {osha_workflow_access_rm} wau
            INNER JOIN {users} us ON wau.uid = us.uid
            WHERE wau.access_scheme = :access_scheme AND wau.access_id = :access_id",
          array(':access_scheme' => $active['access_scheme']['access_type'], ':access_id' => $access_id)
        )->fetchAllKeyed();
      }
      $count = count($pms);
      $new_row = l(format_plural($count, '1 Review Manager', '@count Review Managers'), 'admin/config/workbench/access/review-managers/' . $active['access_scheme']['access_type'] . '/' . $access_id);
      if (!empty($pms)) {
        $new_row .= ' (' . implode(', ',$pms ) . ') ';
      }
      $row[] = $new_row;

      $rows[] = $row;
    }
    $header = array(t('Section'), t('Managers'));
    $output .= theme('table', array('header' => $header, 'rows' => $rows));
    $build['content']['#markup'] = $output;
    return $build;
  }
  return NULL;
}

/**
 * Function to retrieve default Project Manager for a section.
 *
 *   It searches UP in the section tree for an assigned PM.
 *
 * @param int|string $section
 *   Section ID
 *
 * @return object|FALSE
 *   User Object
 */
function osha_workflow_get_default_review_manager($section) {
  $section_tree = workbench_access_get_active_tree();
  if (osha_workflow_access_rm_check_root()) {
    if (!empty($section_tree['tree'])) {
      $users = osha_workflow_access_find_rm($section_tree, $section);
      if (!empty($users)) {
        return current($users);
      }
    }
  }
  return FALSE;
}

/**
 * Recursion Function to get the project manager from sections tree.
 *
 * @param array $section_tree
 *   active tree array
 * @param int|string $section_id
 *   Id of the section to search PM for
 *
 * @return array
 *   Array of Users Objects
 */
function osha_workflow_access_find_rm(&$section_tree, $section_id) {
  $access = $section_tree['tree'][$section_id];
  $users = osha_workflow_access_rm_get_rm($access['access_id'],
    $section_tree['access_scheme']['access_scheme']);
  if (empty($users)&& !empty($access['parent'])) {
    $users = osha_workflow_access_find_rm($section_tree, $access['parent']);
  }
  else {
    return $users;
  }
  return $users;
}

/**
 * Get PM of a section.
 */
function osha_workflow_access_rm_get_rm($access_id, $access_scheme) {
  return user_load_multiple(
    osha_workflow_access_rm_get_rm_uid($access_id, $access_scheme));
}

/**
 * Get PM of a section.
 */
function osha_workflow_access_rm_get_rm_uid($access_id, $access_scheme) {
  $users = db_select('osha_workflow_access_rm', 'owa')
    ->fields('owa', array('uid'))
    ->condition('access_id', $access_id)
    ->condition('access_scheme', $access_scheme)
    ->execute()
    ->fetchAllAssoc('uid');
  return array_keys($users);
}

/**
 * Get sections ids of a pm.
 */
function osha_workflow_access_get_rm_sections($uid) {
  $sections = db_select('osha_workflow_access_rm', 'owa')
    ->fields('owa', array('access_id'))
    ->condition('uid', $uid)
    ->execute()
    ->fetchAllAssoc('access_id');
  return array_keys($sections);
}

/**
 * Checks for PM to be assigned to root Section.
 *
 * @return bool
 *   If a PM is assigned for root Section or not.
 */
function osha_workflow_access_rm_check_root() {
  $section_tree = workbench_access_get_active_tree();
  $access = current($section_tree['tree']);
  if (!empty($access)) {
    $users = osha_workflow_access_rm_get_rm($access['access_id'],
      $section_tree['access_scheme']['access_scheme']);
    if (!empty($users)) {
      return TRUE;
    }
    else {
      drupal_set_message(t("Workflow: You haven't assigned a PM for root Section"), 'error');
      return FALSE;
    }
  }
  return FALSE;
}
