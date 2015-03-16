<?php
/**
 * @file
 * osha_blog.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function osha_blog_default_rules_configuration() {
  $items = array();
  $items['rules_send_email_on_new_blog_comment'] = entity_import('rules_config', '{ "rules_send_email_on_new_blog_comment" : {
      "LABEL" : "Send Email on New Blog Comment",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "comment" ],
      "ON" : { "comment_insert--comment_node_blog" : { "bundle" : "comment_node_blog" } },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "comment:node" ],
            "type" : "node",
            "bundle" : { "value" : { "blog" : "blog" } }
          }
        }
      ],
      "DO" : [
        { "mail" : {
            "to" : [ "comment:node:field-project-manager:mail" ],
            "subject" : "New comment for \\u0022[comment:node]\\u0022",
            "message" : "New comment on Blog post \\u0022[comment:node]\\u0022: \\u003Cbr \\/\\u003E\\u003Cbr \\/\\u003E\\r\\n[comment:body] \\u003Cbr \\/\\u003E\\r\\nSee comment: [comment:url]",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  return $items;
}
