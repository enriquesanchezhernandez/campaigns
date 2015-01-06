<?php

class OSHATMGMTNodeSourcePluginController extends TMGMTNodeSourcePluginController {

  /**
   * {@inheritdoc}
   */
  public function getData(TMGMTJobItem $job_item) {
    $node = node_load($job_item->item_id);
    // Get all the fields that can be translated and arrange their values into
    // a specific structure.
    return tmgmt_field_get_source_data('node', $node, $job_item->getJob()->source_language);
  }
}