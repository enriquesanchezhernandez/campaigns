<?php

/* Add new stuff for deployment of sprint-5 branch here. To avoid conflicts, add them after your name 
 * Also include the ticket number, see example below
 */

osha_update_menu_links();

/**
 * Update menu links
 */
function osha_update_menu_links(){
  db_update('menu_links')
    ->fields(array(
      'link_path' => 'tools-and-publications/publications',
      'router_path' => 'tools-and-publications/publications'))
    ->condition('mlid', '652')
    ->execute();

  db_update('menu_links')
    ->fields(array(
      'link_path' => 'inside-eu-osha/press-room',
      'router_path' => 'inside-eu-osha/press-room'))
    ->condition('mlid', '673')
    ->execute();

  db_update('menu_links')
    ->fields(array(
      'link_path' => 'inside-eu-osha/press-room',
      'router_path' => 'inside-eu-osha/press-room'))
    ->condition('mlid', '1704')
    ->execute();

  db_update('menu_links')
    ->fields(array(
      'link_path' => 'tools-and-publications/events',
      'router_path' => 'tools-and-publications/events'))
    ->condition('mlid', '1513')
    ->execute();

  db_update('block')
    ->fields(array('pages' => 'tools-and-publications/events'))
    ->condition('delta', '5322')
    ->execute();

  // Flush cache.
  cache_clear_all();
}
