<?php
/**
 * @file
 * hwc_homepage.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function hwc_homepage_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: management.
  $menus['management'] = array(
    'menu_name' => 'management',
    'title' => 'Management',
    'description' => 'The <em>Management</em> menu contains links for administrative tasks.',
    'language' => 'und',
    'i18n_mode' => 0,
  );
  // Exported menu: menu-social-links.
  $menus['menu-social-links'] = array(
    'menu_name' => 'menu-social-links',
    'title' => 'Social Links',
    'description' => 'A list of social links.',
    'language' => 'und',
    'i18n_mode' => 0,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('A list of social links.');
  t('Management');
  t('Social Links');
  t('The <em>Management</em> menu contains links for administrative tasks.');


  return $menus;
}
