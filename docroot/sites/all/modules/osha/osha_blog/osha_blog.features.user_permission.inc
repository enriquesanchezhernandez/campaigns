<?php
/**
 * @file
 * osha_blog.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function osha_blog_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create blog content'.
  $permissions['create blog content'] = array(
    'name' => 'create blog content',
    'roles' => array(
      'Approver' => 'Approver',
      'Content Validator' => 'Content Validator',
      'Editor' => 'Editor',
      'Events Coordinator' => 'Events Coordinator',
      'Layout Validator' => 'Layout Validator',
      'Project Manager' => 'Project Manager',
      'Review Manager' => 'Review Manager',
      'Translation Liaison' => 'Translation Liaison',
      'Translation Manager' => 'Translation Manager',
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own blog content'.
  $permissions['edit own blog content'] = array(
    'name' => 'edit own blog content',
    'roles' => array(
      'Approver' => 'Approver',
      'Content Validator' => 'Content Validator',
      'Editor' => 'Editor',
      'Events Coordinator' => 'Events Coordinator',
      'Layout Validator' => 'Layout Validator',
      'Project Manager' => 'Project Manager',
      'Review Manager' => 'Review Manager',
      'Translation Liaison' => 'Translation Liaison',
      'Translation Manager' => 'Translation Manager',
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
