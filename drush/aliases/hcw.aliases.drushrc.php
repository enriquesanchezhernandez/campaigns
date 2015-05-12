<?php

$aliases['staging'] = array(
  'uri' => 'osha-campaigns.edw.ro',
  'db-allows-remote' => TRUE,
  'remote-host' => 'osha-campaigns.edw.lan',
  'remote-user' => 'php',
  'root' => '/var/www/html/docroot',
  'path-aliases' => array(
    '%files' => 'sites/default/files',
  ),
);

// Add your local aliases.
if (file_exists(dirname(__FILE__) . '/aliases.local.php')) {
  include dirname(__FILE__) . '/aliases.local.php';
}
