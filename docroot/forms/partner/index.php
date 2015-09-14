<?php


function osha_get_drupal_parameters() {
  $ret = array(
    'appform_id' => NULL,
    'mf' => FALSE,
    'partner_guid' => NULL,
  );

  /* Drupal bootstrap procedure */
  define('DRUPAL_ROOT', realpath(__DIR__ . '/../../'));
  require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
  $base_url = 'http://' . $_SERVER['HTTP_HOST'];
  drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
  global $user;

  try {
    $wrapper = entity_metadata_wrapper('user', $user);
    $ret['partner_guid'] = $wrapper->field_crm_guid->value();
  }
  catch(Exception $e) {}

  if (!empty($_SESSION['appform_id'])) {
    $ret['appform_id'] = $_SESSION['appform_id'];
  }

  if (!empty($_SESSION['mf'])) {
    $ret['mf'] = $_SESSION['mf'];
  }

  return $ret;
}

$config = osha_get_drupal_parameters();
var_dump($config);

//error_reporting(E_ERROR | E_WARNING | E_PARSE);
// Enviroment constants
define('APP_ROOT', dirname($_SERVER['SCRIPT_FILENAME']) . '/');
$phpSelf = pathinfo($_SERVER['PHP_SELF']);
define('APP_URL', 'http://'.$_SERVER['HTTP_HOST'] . $phpSelf['dirname'] . '/');
define('APP_PORT', intval($_SERVER['SERVER_PORT']) != 80 ? ':' . $_SERVER['SERVER_PORT'] : '');
define('APP_CONFIG', APP_ROOT . 'config/');
// Autoloader
require(APP_ROOT . 'lib/dwoo/lib/dwooAutoload.php');
require(APP_ROOT . 'Autoloader.php');
// Session start
$session = Session::getInstance();
$session->start();

// Security nonce
$nonce = chr(mt_rand(97, 122)) . substr(md5(time()), 1);
$params = Parameters::getInstance();
$params->set('nonce', $nonce);
// Dispatcher
$dispatcher = new Dispatcher();
$dispatcher->dispatch();
