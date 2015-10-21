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
<div class="publication-item">
<?php
/** @var array $variables */
$content = $variables['content'];
$node = $variables['node'];
global $language;
print render($content['field_publication_date']);
foreach($content as $field_name => $field) {
  if (!in_array($field_name, array('field_file', 'field_publication_date'))) {
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
        $items[] = sprintf(round($f['filesize']/1000000,1) . 'MB ' . strtoupper(pathinfo($f['uri'], PATHINFO_EXTENSION)) . ' ' . taxonomy_term_load($node->field_publication_type[LANGUAGE_NONE][0][tid])->name . ' <a href="%s">' . t('Download in') . ' %s</a><i class="glyphicon glyphicon-circle-arrow-down"></i>', file_create_url($f['uri']), i18n_language_name($lang));
      }
    }
  }
  print theme('item_list', array('items' => $items));
}
?>
</div>
