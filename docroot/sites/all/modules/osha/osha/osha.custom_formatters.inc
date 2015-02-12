<?php
/**
 * @file
 * osha.custom_formatters.inc
 */

/**
 * Implements hook_custom_formatters_defaults().
 */
function osha_custom_formatters_defaults() {
  $export = array();

  $formatter = new stdClass();
  $formatter->disabled = FALSE; /* Edit this to true to make a default formatter disabled initially */
  $formatter->api_version = 2;
  $formatter->name = 'multilanguage_file';
  $formatter->label = 'Multilanguage File';
  $formatter->description = 'Download file in: EN, BG ...';
  $formatter->mode = 'php';
  $formatter->field_types = 'file';
  $formatter->code = 'global $language;
$curr_lang = $language->language ;
$node = $variables[\'#object\'];
$file = isset($node->field_file[$curr_lang][0]) ? $node->field_file[$curr_lang][0] : $node->field_file[\'en\'][0];
$output = "<span class=\'label_multilang_file\'>Download</span>";
$output .= theme_file_icon(
  array(
    "file" => file_load($file[\'fid\']),
    "icon_directory" => drupal_get_path(\'theme\', \'osha_frontend\') . \'/images/file_icons\'
));
$output .="<span class=\'label_multilang_file\'>in:</span>";

foreach($node->field_file as $lang => $object) {
    $output .=  \'<a href="\' . file_create_url($object[0][\'uri\']) . \'" target="_blank">\' . strtoupper($lang) . \'</a> | \';
}
$output = substr($output, 0, -3);
return $output;';
  $formatter->fapi = '';
  $export['multilanguage_file'] = $formatter;

  $formatter = new stdClass();
  $formatter->disabled = FALSE; /* Edit this to true to make a default formatter disabled initially */
  $formatter->api_version = 2;
  $formatter->name = 'multilanguage_image';
  $formatter->label = 'Multilanguage Image';
  $formatter->description = 'Download image in EN, BG ...';
  $formatter->mode = 'php';
  $formatter->field_types = 'image';
  $formatter->code = 'global $language;
$curr_lang = $language->language ;
$node = $variables[\'#object\'];
$file = isset($node->field_image[$curr_lang][0]) ? $node->field_image[$curr_lang][0] : $node->field_image[\'en\'][0];
$output = "<span class=\'label_multilang_file\'>Open</span>";
$output .= theme_file_icon(
  array(
    "file" => file_load($file[\'fid\']),
    "icon_directory" => drupal_get_path(\'theme\', \'osha_frontend\') . \'/images/file_icons\'
));
$output .="<span class=\'label_multilang_file\'>in:</span>";

foreach($node->field_image as $lang => $object) {
    $output .=  \'<a href="\' . file_create_url($object[0][\'uri\']) . \'" target="_blank">\' . strtoupper($lang) . \'</a> | \';
}
$output = substr($output, 0, -3);
return $output;';
  $formatter->fapi = '';
  $export['multilanguage_image'] = $formatter;


  return $export;
}
