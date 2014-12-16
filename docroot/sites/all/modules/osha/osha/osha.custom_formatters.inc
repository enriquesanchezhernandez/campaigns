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
  $formatter->name = 'call_contract_notice';
  $formatter->label = 'Call special file';
  $formatter->description = '';
  $formatter->mode = 'php';
  $formatter->field_types = 'file';
  $formatter->code = 'global $language;
$curr_lang = $language->language ;
$output = \'\';
$field_name =$variables[\'#field\'][\'field_name\'];
$field = $variables[\'#object\']->{$field_name};
$file= isset($field[$curr_lang]) ? $field[$curr_lang] : NULL;

if (isset($file[0])) {   
    $output .= \' <a href = "\' . file_create_url($file[0][\'uri\']) . \'">\';
    $output .= \'<span>\' . t($variables[\'#instance\'][\'label\']) . \'</span> - \';
    $output .= theme_file_icon(
		   array(
		       "file" => file_load($file[0][\'fid\']),
		       "icon_directory" => drupal_get_path(\'theme\', \'osha_frontend\') . \'/images/file_icons\'
		   ));
    $output .= \'<span>\' . format_size(filesize($file[0][\'uri\'])). \'</span>\';
    $output .= \'</a>\'; 
}

return $output;';
  $formatter->fapi = '';
  $export['call_contract_notice'] = $formatter;

  $formatter = new stdClass();
  $formatter->disabled = FALSE; /* Edit this to true to make a default formatter disabled initially */
  $formatter->api_version = 2;
  $formatter->name = 'file_as_title';
  $formatter->label = 'File as title';
  $formatter->description = 'Link to file using node title as link title';
  $formatter->mode = 'php';
  $formatter->field_types = 'file';
  $formatter->code = 'global $language ;
$curr_lang = $language->language ;
$node = $variables[\'#object\'];
$title = isset($node->title_field[$curr_lang][0]) ? $node->title_field[$curr_lang][0][\'value\'] : $node->title_field[\'en\'][0][\'value\'];
$file = isset($node->field_file[$curr_lang][0]) ? $node->field_file[$curr_lang][0] : $node->field_file[\'en\'][0];
$output = \' <a href = "\' . file_create_url($file[\'uri\']) . \'"><span>\' . $title.\'</span>\';
$output .= theme_file_icon(
   array(
       "file" => file_load($file[\'fid\']),
       "icon_directory" => drupal_get_path(\'theme\', \'osha_frontend\') . \'/images/file_icons\'
   ));
$output .= \'<span>\' . format_size(filesize($file[\'uri\'])). \'</span>\';
$output .= \'</a>\';
return $output;';
  $formatter->fapi = '';
  $export['file_as_title'] = $formatter;

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
$output = "<span class=\'label_multilang_file\'>Download</span>";
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

  $formatter = new stdClass();
  $formatter->disabled = FALSE; /* Edit this to true to make a default formatter disabled initially */
  $formatter->api_version = 2;
  $formatter->name = 'publication_bookshop_id';
  $formatter->label = 'publication_bookshop_id';
  $formatter->description = '';
  $formatter->mode = 'php';
  $formatter->field_types = 'text';
  $formatter->code = 'global $language ;
$curr_lang = $language->language;
$object = isset($variables[\'#object\']->field_publication_bookshop_id[$curr_lang]) ? $variables[\'#object\']->field_publication_bookshop_id[$curr_lang] :$variables[\'#object\']->field_publication_bookshop_id[\'en\'];
$code = $object[0][\'value\'];
return empty($code)?\'\':\'<span>\'.t(\'Order a printed copy\').\'<a href="http://bookshop.europa.eu/is-bin/INTERSHOP.enfinity/WFS/EU-Bookshop-Site/en_GB/-/EUR/ViewPublication-Start?PublicationKey=\' . $code . \'"><img src="\' . $GLOBALS[\'base_url\'] . \'/sites/all/themes/osha_frontend/images/content/eu_bookshop.gif" alt="\'.t(\'EU Bookshop: You can order a printed copy of this document\').\'" title="\'.t(\'EU Bookshop: You can order a printed copy of this document\').\'"></a></span>\';';
  $formatter->fapi = '';
  $export['publication_bookshop_id'] = $formatter;

  $formatter = new stdClass();
  $formatter->disabled = FALSE; /* Edit this to true to make a default formatter disabled initially */
  $formatter->api_version = 2;
  $formatter->name = 'publication_file';
  $formatter->label = 'publication_file';
  $formatter->description = '';
  $formatter->mode = 'php';
  $formatter->field_types = 'file';
  $formatter->code = 'global $language;
$curr_lang = $language->language ;
$node = $variables[\'#object\'];
$file = isset($node->field_file[$curr_lang][0]) ? $node->field_file[$curr_lang][0] : $node->field_file[\'en\'][0];
$output = "<span class=\'label_publication_file\'>Download</span>";
$output .= theme_file_icon(
  array(
    "file" => file_load($file[\'fid\']),
    "icon_directory" => drupal_get_path(\'theme\', \'osha_frontend\') . \'/images/file_icons\'
));
$output .="<span class=\'label_publication_file\'>in:</span>";

foreach($node->field_file as $lang => $object) {
    $output .=  \'<a href="\' . file_create_url($object[0][\'uri\']) . \'">\' . strtoupper($lang) . \'</a> | \';
}
$output = substr($output, 0, -3);
return $output;';
  $formatter->fapi = '';
  $export['publication_file'] = $formatter;

  $formatter = new stdClass();
  $formatter->disabled = FALSE; /* Edit this to true to make a default formatter disabled initially */
  $formatter->api_version = 2;
  $formatter->name = 'publication_related_publications';
  $formatter->label = 'publication_related_publications';
  $formatter->description = '';
  $formatter->mode = 'php';
  $formatter->field_types = 'entityreference';
  $formatter->code = 'global $language ;
$curr_lang = $language->language ;
$output = \'<h3>Summary &amp; Resources</h3>\';
$output .= \'<ul id="publication_related_publications">\';
$related_pubs = $variables[\'#object\']->field_related_publications[\'und\'];
foreach ($related_pubs as $pub) {
  $output .= \'<li>\';
  $node = node_load($pub[\'target_id\']);
  $title = isset($node->title_field[$curr_lang][0]) ? $node->title_field[$curr_lang][0][\'value\'] : $node->title_field[\'en\'][0][\'value\'];
  $output .=  \'<a href="\' . url(\'node/\' . $node->nid, array(\'absolute\' => TRUE)) . \'">\' . $title . \'</a>\';
  $output .= \'<span>Download</span>\';
  $file = isset($node->field_file[$curr_lang][0]) ? $node->field_file[$curr_lang][0] : $node->field_file[\'en\'][0];
  $output .= theme_file_icon(
    array(
      "file" => file_load($file[\'fid\']),
      "icon_directory" => drupal_get_path(\'theme\', \'osha_frontend\') . \'/images/file_icons\'
  ));
  $output .=\'<span>in:</span>\';
  foreach ($node->field_file as $lang => $object) {
    $output .=  \' <a href="\' . file_create_url($object[0][\'uri\']) . \'">\' . strtoupper($lang) . \'</a> | \';
  }
  $output = substr($output, 0, -3);
  $output .= \'</li>\';
}
$output .= \'</ul>\';
return $output;';
  $formatter->fapi = '';
  $export['publication_related_publications'] = $formatter;

  $formatter = new stdClass();
  $formatter->disabled = FALSE; /* Edit this to true to make a default formatter disabled initially */
  $formatter->api_version = 2;
  $formatter->name = 'publication_related_res';
  $formatter->label = 'publication_related_res';
  $formatter->description = '';
  $formatter->mode = 'php';
  $formatter->field_types = 'file';
  $formatter->code = '$output = \'<ul id="publication_related_res">\';
global $language ;
$curr_lang = $language->language;
$object = isset($variables[\'#object\']->field_publication_related_res[$curr_lang]) ? $variables[\'#object\']->field_publication_related_res[$curr_lang] :$variables[\'#object\']->field_publication_related_res[\'en\'];
foreach ($object as $obj) {
	$name = ($obj[\'description\'] != NULL) ? $obj[\'description\'] : $obj[\'filename\'];
	$output .= \'<li><a href="\' . file_create_url($obj[\'uri\']) . \'">\';
	$output .= theme_file_icon(
		   array(
		       "file" => file_load($obj[\'fid\']),
		       "icon_directory" => drupal_get_path(\'theme\', \'osha_frontend\') . \'/images/file_icons\'
		   ));
	$output .= \'<span>\'.$name.\'</span></a></li>\';
}
$output .= \'</ul>\';

return $output;';
  $formatter->fapi = '';
  $export['publication_related_res'] = $formatter;

  $formatter = new stdClass();
  $formatter->disabled = FALSE; /* Edit this to true to make a default formatter disabled initially */
  $formatter->api_version = 2;
  $formatter->name = 'seminar_related_resources';
  $formatter->label = 'Seminar related resources';
  $formatter->description = '';
  $formatter->mode = 'php';
  $formatter->field_types = 'file';
  $formatter->code = '$output = \'<ul id="seminar_related_resources">\';
global $language ;
$curr_lang = $language->language;
$object = isset($variables[\'#object\']->field_related_resources[$curr_lang]) ? $variables[\'#object\']->field_related_resources[$curr_lang] :$variables[\'#object\']->field_related_resources[\'en\'];
foreach ($object as $obj) {
        $description = !empty($obj[\'description\']) ? $obj[\'description\'] : $obj[\'filename\'];
	$output .= \'<li><a href="\' . file_create_url($obj[\'uri\']) . \'">\' . $description;
	$output .= \' - \';
        $output .= theme_file_icon(
           array(
               "file" => file_load($obj[\'fid\']),
               "icon_directory" => drupal_get_path(\'theme\', \'osha_frontend\') . \'/images/file_icons\'
           ));
	$output .= \'<span>\' . format_size(filesize($obj[\'uri\'])) . \'</span>\';
	$output .= \'</a></li>\'; 
}
$output .= \'</ul>\';

return $output;';
  $formatter->fapi = '';
  $export['seminar_related_resources'] = $formatter;

  $formatter = new stdClass();
  $formatter->disabled = FALSE; /* Edit this to true to make a default formatter disabled initially */
  $formatter->api_version = 2;
  $formatter->name = 'vacancies_related_resources';
  $formatter->label = 'Vacancies related resources';
  $formatter->description = '';
  $formatter->mode = 'php';
  $formatter->field_types = 'file';
  $formatter->code = 'global $language;
$curr_lang = $language->language ;
$output = \'<ul id="job_vacancies_related_resources">\';

$files = isset($variables[\'#object\']->field_related_resources[$curr_lang]) ? $variables[\'#object\']->field_related_resources[$curr_lang] : $variables[\'#object\']->field_related_resources[\'en\'];

$field_name = $variables[\'#field\'][\'field_name\'];
$field = $variables[\'#object\']->{$field_name};
$file= isset($field[$curr_lang]) ? $field[$curr_lang] : NULL;

foreach ($files as $file) {
  $description = !empty($file[\'description\']) ? $file[\'description\'] : $file[\'filename\'];
    $output .= \' <li><a href = "\' . file_create_url($file[\'uri\']) . \'">\' . $description;
    $output .= \' - \';
    $output .= theme_file_icon(
       array(
           "file" => file_load($file[\'fid\']),
           "icon_directory" => drupal_get_path(\'theme\', \'osha_frontend\') . \'/images/file_icons\'
       ));
    $output .= \'<span>\' . format_size(filesize($file[\'uri\'])). \'</span>\';
    $output .= \'</a></li>\';
}

$output .= \'</ul>\';

return $output;';
  $formatter->fapi = '';
  $export['vacancies_related_resources'] = $formatter;

  return $export;
}
