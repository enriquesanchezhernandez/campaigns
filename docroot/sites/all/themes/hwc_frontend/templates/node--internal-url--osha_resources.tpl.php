<?php
/**
 * @file node--internal-url--osha_resources.tpl.php
 * Default template implementation to display the value of a publication listing field.
 *
 * Available variables:
 * - $variables['content']: An array of field values. Use render() to output them.
 * - $variables['node']: Actual publication node
 *
 * @ingroup themeable
 */
?>
<?php
/** @var stdClass $node */
/** @var array $variables */
$node = $variables['node'];
$wrapper = entity_metadata_wrapper('node', $node);
$title = NULL;
$link = NULL;
if (isset($content['title_field'])) {
  $title = $wrapper->title_field->value();
}
if (isset($content['title_field'])) {
  $link = $wrapper->field_external_url->value();
}
if ($link && $title) {
  print l($title, $link['url'], $link);
  $content['title_field']['#printed'] = TRUE;
  $content['field_external_url']['#printed'] = TRUE;
}
foreach(element_children($content) as $key) {
  print drupal_render($content[$key]);
}
