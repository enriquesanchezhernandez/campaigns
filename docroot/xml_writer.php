<?php

if ($xml = simplexml_load_file('/home/dragosd/Downloads/translation_job_id_147_request.xml')) {
  // To be used for board and bureau memebers, to merge the details.
//    $xml_board = simplexml_load_file($this->file_board);
//    $xml_bureau = simplexml_load_file($this->file_bureau);
  $parent = $xml->xpath('//TranslationDetails');
  $translations = clone $parent[0]->Translation;
  unset($parent[0]->Translation);
  $dom=dom_import_simplexml($parent[0]);
  foreach ($translations as $idx => $translation) {
    foreach ($translation->TranslationTargetLanguage as $lang) {
      $xml_trans_obj = clone $translation;
      unset($xml_trans_obj->TranslationTargetLanguage);
      $xml_trans_obj->addChild('TranslationTargetLanguage', $lang);
//      echo $xml_trans_obj->asXML();
//      exit;
      $dom->appendChild(dom_import_simplexml($xml_trans_obj));
    }
  }
  unset($parent[0]->Translation2);
  $xml->saveXML();
  $xml->asXML('/home/dragosd/Downloads/translation_job_id_147_resp.xml');
}
