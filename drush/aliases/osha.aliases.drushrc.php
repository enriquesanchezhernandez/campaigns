<?php

$aliases['osha.staging'] = array(
  'uri' => 'osha-corp-staging03.mainstrat.com',
  'db-allows-remote' => TRUE,
  'remote-host' => 'osha-corp-staging03.mainstrat.com',
  'remote-user' => 'root',
  'root' => '/expert/osha/docroot',
  'path-aliases' => array(
    '%files' => 'sites/default/files',
  ),
  'command-specific' => array(
    'sql-sync' => array(
      'simulate' => '1',
    ),
  ),
);

$aliases['osha.production'] = array(
  'uri' => 'osha-corp.mainstrat.com',
  'db-allows-remote' => TRUE,
  'remote-host' => '194.30.34.9',
  'remote-user' => 'root',
  'root' => '/expert/osha/docroot',
  'path-aliases' => array(
    '%files' => 'sites/default/files',
  ),
  'command-specific' => array(
    'sql-sync' => array(
      'simulate' => '1',
    ),
  ),
);

// This alias is used in install and update scripts.
// Rewrite it in your aliases.local.php as you need.
$aliases['osha.staging.sync'] = $aliases['osha.staging'];

// Example of local setting.
// $aliases['osha.local'] = array(
//   'uri' => 'osha.localhost',
//   'root' => '/home/my_user/osha-website/docroot',
// );

// Add your local aliases.
if (file_exists(dirname(__FILE__) . '/aliases.local.php')) {
  include dirname(__FILE__) . '/aliases.local.php';
}
