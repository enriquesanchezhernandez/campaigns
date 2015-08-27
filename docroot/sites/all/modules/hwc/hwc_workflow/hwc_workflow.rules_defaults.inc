<?php
/**
 * @file
 * hwc_workflow.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function hwc_workflow_default_rules_configuration() {
  $items = array();
  $items['rules_hwc_workflow_notification_after_approval'] = entity_import('rules_config', '{ "rules_hwc_workflow_notification_after_approval" : {
      "LABEL" : "Notification after approval",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "hwc_workflow" ],
      "ON" : { "node_cpm_approve" : [] },
      "DO" : [
        { "hwc_mail_to_remaining_cpm_approvers" : {
            "node" : [ "node" ],
            "subject" : "Content needs approval",
            "message" : "This content needs approval: \\u003Ca href=\\u0022[node:url]\\u0022\\u003E[node:title]\\u003C\\/a\\u003E\\r\\nNext person to approve is [user:name]."
          }
        }
      ]
    }
  }');
  $items['rules_hwc_workflow_notification_partner_content_created'] = entity_import('rules_config', '{ "rules_hwc_workflow_notification_partner_content_created" : {
      "LABEL" : "Notification partner content created (CMW_ED_US_02)",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "hwc_workflow" ],
      "ON" : { "node_insert" : [] },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "node" ],
            "type" : "node",
            "bundle" : { "value" : { "events" : "events", "news" : "news" } }
          }
        }
      ],
      "DO" : [
        { "hwc_mail_to_users_of_partner" : {
            "node" : [ "node" ],
            "subject" : "HWC Workflow: New content created for you company",
            "message" : "New content has been created for your company: \\u003Ca href=\\u0022[node:url]\\u0022\\u003E[node:title]\\u003C\\/a\\u003E"
          }
        }
      ]
    }
  }');
  $items['rules_hwc_workflow_notification_partner_content_published'] = entity_import('rules_config', '{ "rules_hwc_workflow_notification_partner_content_published" : {
      "LABEL" : "Notification when published (CMW_ED_US_05, CMW_RM_US_06, , CMW_SU_US_05)",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "hwc_workflow", "workbench_moderation" ],
      "ON" : { "workbench_moderation_after_moderation_transition" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "new-state" ], "value" : "published" } },
        { "entity_is_of_bundle" : {
            "entity" : [ "node" ],
            "type" : "node",
            "bundle" : { "value" : { "events" : "events", "news" : "news" } }
          }
        },
        { "node_has_partner_section" : { "entity" : [ "node" ] } }
      ],
      "DO" : [
        { "hwc_mail_to_users_of_partner" : {
            "node" : [ "node" ],
            "subject" : "HWC Workflow: New content has been published for your company",
            "message" : "New content has been published for your company: \\u003Ca href=\\u0022[node:url]\\u0022\\u003E[node:title]\\u003C\\/a\\u003E"
          }
        }
      ]
    }
  }');
  $items['rules_hwc_workflow_notification_to_be_approved'] = entity_import('rules_config', '{ "rules_hwc_workflow_notification_to_be_approved" : {
      "LABEL" : "Notification when to be approved",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "hwc_workflow" ],
      "ON" : { "node_to_be_approved" : [] },
      "DO" : [
        { "hwc_mail_to_remaining_cpm_approvers" : {
            "node" : [ "node" ],
            "subject" : "Content needs approval",
            "message" : "This content needs approval: \\u003Ca href=\\u0022[node:url]\\u0022\\u003E[node:title]\\u003C\\/a\\u003E\\r\\nNext person to approve is [user:name]."
          }
        }
      ]
    }
  }');
  $items['rules_hwc_workflow_notification_to_be_reviewed'] = entity_import('rules_config', '{ "rules_hwc_workflow_notification_to_be_reviewed" : {
      "LABEL" : "Notification when to be reviewed (RM_US_02, SU_US_04)",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "workbench_moderation" ],
      "ON" : { "workbench_moderation_after_moderation_transition" : [] },
      "IF" : [ { "data_is" : { "data" : [ "new-state" ], "value" : "needs_review" } } ],
      "DO" : [
        { "mail_to_users_of_role" : {
            "roles" : { "value" : { "13" : "13", "14" : "14" } },
            "subject" : "HWC Workflow: New content needs your review",
            "message" : "The content \\u003Ca href=\\u0022[node:url]\\u0022\\u003E[node:title]\\u003C\\/a\\u003E needs your review"
          }
        }
      ]
    }
  }');
  return $items;
}
