<?php
/**
 * @file
 * mytodo.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function mytodo_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create post content'.
  $permissions['create mytodo content'] = array(
    'name' => 'create mytodo content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any mytodo content'.
  $permissions['delete any mytodo content'] = array(
    'name' => 'delete any mytodo content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own mytodo content'.
  $permissions['delete own mytodo content'] = array(
    'name' => 'delete own mytodo content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any mytodo content'.
  $permissions['edit any mytodo content'] = array(
    'name' => 'edit any mytodo content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own mytodo content'.
  $permissions['edit own mytodo content'] = array(
    'name' => 'edit own mytodo content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
