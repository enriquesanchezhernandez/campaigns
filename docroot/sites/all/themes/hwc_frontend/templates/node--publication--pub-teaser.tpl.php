<?php
/**
 * @file node--publication--pub--teaser.tpl.php
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
/** @var array $variables */
$content = $variables['content'];
$node = $variables['node'];
global $language;
foreach($content as $field_name => $field) {
  if ($field_name != 'field_file') {
    print render($field);
  }
}
// List files
$languages = !empty($node->filter_languages) ? $node->filter_languages : array($language->language);
$languages[] = 'en';
$items = array();
if (!empty($node->field_file)) {
  foreach($node->field_file as $lang => $files) {
    foreach($files as $f) {
      if (in_array($lang, $languages)) {
        $items[] = sprintf('<a href="%s">Download in %s</a><i class="glyphicon glyphicon-circle-arrow-down"></i>', url($f['uri']), i18n_language_name($lang));
      }
    }
  }
  print theme('item_list', array('items' => $items));
}
