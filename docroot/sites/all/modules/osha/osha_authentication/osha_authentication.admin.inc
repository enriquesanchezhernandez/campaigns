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