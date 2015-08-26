<?php

function hwc_workflow_node_cpm_assign_form($form, &$form_state, $node) {
  $form =  array();
  $form['#tree'] = TRUE;
  $form['#theme'] = 'hwc_workflow_node_cpm_assign_form';

  if (empty($node->workbench_access)) {
    drupal_set_message('No section assigned to the node.');
    return $form;
  }
  $can_edit = OshaWorkflowPermissions::userCanEditApprovers($node);
  $form['#node'] = $node;
  $users = OshaWorkflowPermissions::getUsersByRole(OSHA_WORKFLOW_ROLE_PROJECT_MANAGER);
  $options = array('' => t('-- Please select --'));
  foreach ($users as $uid => $user) {
    $options[$uid] = $user->name;
  }
  $project_managers = _hwc_workflow_get_project_managers($node->nid);
  if (!empty($project_managers)) {
    $weight = 0;
    $form['rows']['#tree'] = TRUE;
    foreach ($project_managers as $uid => $pm) {
      $form['rows'][$uid]['name'] = array(
        '#markup' => $pm->name,
      );
      $form['rows'][$uid]['weight'] = array(
        '#type' => 'weight',
        '#title' => t('Weight'),
        '#title_display' => 'invisible',
        '#default_value' => $weight,
        '#access' => $can_edit,
        '#attributes' => array('class' => array('user-weight')),
      );
      $form['rows'][$uid]['uid'] = array(
        '#type' => 'hidden',
        '#value' => $uid,
      );
      $form['rows'][$uid]['approved'] = array(
        '#markup' => 'Waiting for approval',
      );
      if (!empty($pm->approved)) {
        $form['rows'][$uid]['approved']['#markup'] = ($pm->approved == 'approved') ? 'Approved' : 'Rejected';
      }
      $form['rows'][$uid]['remove'] = array(
        '#type' => 'submit',
        '#name' => $uid,
        '#value' => t('Remove'),
        '#access' => $can_edit,
        '#submit' => array('_hwc_workflow_admin_approvers_remove_row_submit'),
      );
      $weight++;
    }
  }
  $form['add']['uid'] = array(
    '#type' => 'select',
    '#title' => t('Add a CPM'),
    '#options' => $options,
  );
  $form['add']['submit'] = array(
    '#type' => 'submit',
    '#name' => 'adduser',
    '#value' => t('Add to queue'),
    '#access' => $can_edit,
    '#attributes' => array('class' => array('container-inline')),
    '#submit' => array('_hwc_workflow_admin_approvers_add_row_submit'),
  );
  $form['help'] = array(
    '#type' => 'markup',
    '#markup' =>
      t('<div><strong>Tip:</strong> Use the drag handlers to sort the users in the order you want them to have the content reviewed.
<br />Press Save to confirm your reordering!</div>'),
  );
  $form['content'] = array(
    'actions' => array(
      '#type' => 'actions',
      '#weight' => 20,
      'submit' => array(
        '#type' => 'submit',
        '#value' => t('Save'),
        '#access' => $can_edit,
      ),
    ),
  );
  return $form;
}

function hwc_workflow_node_cpm_assign_form_submit($form, $form_state) {
  if (!empty($form_state['input']['rows'])) {
    $entries = _hwc_workflow_get_project_managers_entries($form['#node']->nid);
    foreach ($form_state['input']['rows'] as $row) {
      if (!empty($entries[$row['uid']])) {
        $entries[$row['uid']]->weight = $row['weight'];
        _hwc_workflow_admin_approvers_save_row($entries[$row['uid']]);
      }
    }
  }
}

/**
 * Form theme callback
 */
function theme_hwc_workflow_node_cpm_assign_form($variables) {
  $form = $variables['form'];

  // Initialize the variable which will store our table rows.
  $rows = array();

  // Iterate over each element in our $form['example_items'] array.
  foreach (element_children($form['rows']) as $id) {
    $form['rows'][$id]['weight']['#attributes']['class'] = array('user-item-weight');
    $rows[] = array(
      'data' => array(
        // Add our 'name' column.
        drupal_render($form['rows'][$id]['name']),
        // Add our 'weight' column.
        drupal_render($form['rows'][$id]['approved']),

        drupal_render($form['rows'][$id]['remove']),

        drupal_render($form['rows'][$id]['weight']),
      ),
      'class' => array('draggable'),
    );
  }
  $header = array(t('Name'), t('Approval'), t('Actions'), t('Weight'));

  $table_id = 'users-items-table';

  // We can render our tabledrag table for output.
  $output = theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => $table_id),
  ));

  $output .= drupal_render_children($form);

  drupal_add_tabledrag($table_id, 'order', 'sibling', 'user-item-weight');

  return $output;
}

/**
 * Get cpm users assigned for a node
 */
function _hwc_workflow_get_project_managers($nid) {
  return user_load_multiple(array_keys(_hwc_workflow_get_project_managers_entries($nid)));
}

/**
 * Get database entries for a node from osha_workflow_node_project_managers.
 */
function _hwc_workflow_get_project_managers_entries($nid) {
  return db_select('osha_workflow_node_project_managers', 'p')
    ->fields('p')
    ->condition('nid', $nid)
    ->orderBy('weight', 'ASC')
    ->execute()
    ->fetchAllAssoc('uid');
}

/**
 * Submit callback for remove button from a row.
 */
function _hwc_workflow_admin_approvers_remove_row_submit($form, &$form_state) {
  if (isset($form_state['triggering_element'])) {
    $triggering_element = $form_state['triggering_element'];
    if (isset($triggering_element['#name'])) {
      $uid = $triggering_element['#name'];
      db_delete('osha_workflow_node_project_managers')
        ->condition('nid', $form['#node']->nid)
        ->condition('uid', $uid)
        ->execute();
    }
  }
}

/**
 * Submit callback for Add user button.
 */
function _hwc_workflow_admin_approvers_add_row_submit($form, &$form_state) {
  if (!empty($form_state['values']['add']['uid'])) {
    $moderator = user_load($form_state['input']['add']['uid']);
    if (!empty($moderator)) {
      $existing_entries = _hwc_workflow_get_project_managers_entries($form['#node']->nid);
      if ($existing_entries[$moderator->uid]) {
        drupal_set_message('This user is already assigned', 'warning');
        return;
      }
      $weight = 0;
      if (!empty($existing_entries)) {
        $last = end($existing_entries);
        $weight = $last->weight > 0 ? $last->weight + 1 : $last->weight -1;
      }
      $row = array(
        'nid' => $form['#node']->nid,
        'uid' => $moderator->uid,
        'weight' => $weight,
      );
      _hwc_workflow_admin_approvers_save_row($row);
    }
  }
}

/**
 * Insert or update an osha_workflow_node_project_managers entry.
 */
function _hwc_workflow_admin_approvers_save_row($row) {
  if (is_object($row)) {
    $row = (array) $row;
  }
  if (isset($row['npmid'])) {
    return drupal_write_record('osha_workflow_node_project_managers', $row, array('npmid'));
  }
  else {
    return drupal_write_record('osha_workflow_node_project_managers', $row);
  }
}
