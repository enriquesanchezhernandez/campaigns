<?php
/** @var array $variables */
$content = $variables['content'];
$node = $variables['node'];
$view = node_view($node, 'teaser');
$q = db_select('languages', 'l');
$q->fields('l', array('language', 'name', 'native'));
$q->innerJoin('entity_translation', 'a', 'l.language = a.language');
$q->condition('a.entity_id', $node->nid);
$q->condition('a.entity_type', 'node');
$languages = $q->execute()->fetchAll();
?>
<div class="practical-tool-item">
  <?php print render($view); ?>
  <?php print theme('hwc_practical_tool_language_list', array('languages' => $languages)); ?>
</div>
