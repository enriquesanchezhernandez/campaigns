<?php

/**
 * Implements hook_rules_event_info() on behalf of the node module.
 */
function hwc_workflow_rules_event_info() {
  $items = array(
    'node_cpm_approve' => array(
      'label' => t('After approving a node as CPM'),
      'group' => t('HWC workflow'),
      'variables' => array(
        'node' => array(
          'type' => 'node',
          'label' => t('Approved node'),
        ),
        'user' => array(
          'type' => 'user',
          'label' => t('Next approver'),
        ),
        'users' => array(
          'type' => 'list<user>',
          'label' => t('Remaining CPMs'),
        ),
      ),
      'access callback' => 'rules_node_integration_access',
    ),
    'node_to_be_approved' => array(
      'label' => t('When setting a node to be approved CPM'),
      'group' => t('HWC workflow'),
      'variables' => array(
        'node' => array(
          'type' => 'node',
          'label' => t('Node'),
        ),
        'user' => array(
          'type' => 'user',
          'label' => t('Next CPM'),
        ),
        'users' => array(
          'type' => 'list<user>',
          'label' => t('Remaining CPMs'),
        ),
      ),
      'access callback' => 'rules_node_integration_access',
    ),
  );
  return $items;
}


/**
 * Implements hook_rules_action_info() on behalf of the system module.
 */
function hwc_workflow_rules_action_info() {
  return array(
    'hwc_mail_to_users_of_partner' => array(
      'label' => t('Send mail to all users of a partner'),
      'group' => t('HWC workflow'),
      'parameter' => array(
        'node' => array(
          'type' => 'node',
          'label' => t('Node'),
          'description' => t("The current node"),
        ),
        'subject' => array(
          'type' => 'text',
          'label' => t('Subject'),
          'description' => t("The mail's subject."),
        ),
        'message' => array(
          'type' => 'text',
          'label' => t('Message'),
          'description' => t("The mail's message body."),
        ),
      ),
      'base' => 'hwc_workflow_rules_mail_to_partners',
      'access callback' => 'rules_system_integration_access',
    ),
  );
}

/**
 * Implements hook_rules_condition_info() on behalf of the entity module.
 */
function hwc_workflow_rules_condition_info() {
  return array(
    'node_has_partner_section' => array(
      'label' => t('Node has a partner section'),
      'parameter' => array(
        'entity' => array(
          'type' => 'node',
          'label' => t('Node'),
          'description' => t('Specifies the node for which to evaluate the condition.'),
        ),
      ),
      'group' => t('HWC workflow'),
      'base' => 'hwc_workflow_rules_condition_node_has_partner_section',
    ),
  );
}

/**
 * Condition: Entity is of type.
 */
function hwc_workflow_rules_condition_node_has_partner_section($node) {
  if (!empty($node->workbench_access)) {
    $section_id = current($node->workbench_access);
    // If it's a partner section.
    if ($section_id != 'section') {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Action: Send mail to all users of a partner.
 */
function hwc_workflow_rules_mail_to_partners($node, $subject, $message, $settings, RulesState $state, RulesPlugin $element) {
  if (!empty($node->workbench_access)) {
    reset($node->workbench_access);
    $section_id = current($node->workbench_access);
    // If it's a partner section.
    if ($section_id != 'section') {
      $users = _hwc_workflow_load_users_by_section($section_id);
      $params = array(
        'subject' => $subject,
        'message' => $message,
      );
      // Set a unique key for this mail.
      $name = isset($element->root()->name) ? $element->root()->name : 'unnamed';
      $key = 'rules_action_hwc_workflow_rules_mail_to_partners_' . $name . '_' . $element->elementId();  $languages = language_list();

      $message = array('result' => TRUE);
      foreach ($users as $user) {
        $message = drupal_mail('rules', $key, $user->mail, language_default(), $params);
        // If $message['result'] is FALSE, then it's likely that email sending is
        // failing at the moment, and we should just abort sending any more. If
        // however, $mesage['result'] is NULL, then it's likely that a module has
        // aborted sending this particular email to this particular user, and we
        // should just keep on sending emails to the other users.
        // For more information on the result value, see drupal_mail().
        if ($message['result'] === FALSE) {
          break;
        }
      }
      if ($message['result'] !== FALSE) {
        watchdog('rules', 'Successfully sent email to the users of the partner %partner.', array('%partner' => $section_id));
      }
    }
  }
}
