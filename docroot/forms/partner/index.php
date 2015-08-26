<?php

/* Drupal bootstrap procedure */
define('DRUPAL_ROOT', realpath(__DIR__ . '/../../'));
require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
global $user;
print "<strong>You are currently logged as: <span style='color: red;'>{$user->mail} ($user->uid)</span></strong>";


// Enviroment constants
define('APP_ROOT', dirname($_SERVER['SCRIPT_FILENAME']) . '/');
$phpSelf = pathinfo($_SERVER['PHP_SELF']);
define('APP_URL', 'http://'.$_SERVER['HTTP_HOST'] . $phpSelf['dirname'] . '/');
define('APP_CONFIG', APP_ROOT . 'config/');
// Autoloader
require(APP_ROOT . 'lib/dwoo/lib/dwooAutoload.php');
require(APP_ROOT . 'Autoloader.php');
// Session start
$session = Session::getInstance();
$session->start();
// Dispatcher
$dispatcher = new Dispatcher();
$dispatcher->dispatch();
