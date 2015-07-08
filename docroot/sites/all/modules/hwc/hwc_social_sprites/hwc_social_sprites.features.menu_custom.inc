<?php
/**
 * @file
 * hwc_social_sprites.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function hwc_social_sprites_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-footer-menu.
  $menus['menu-footer-menu'] = array(
    'menu_name' => 'menu-footer-menu',
    'title' => 'Footer',
    'description' => '',
    'language' => 'und',
    'i18n_mode' => 5,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Footer');


  return $menus;
}
