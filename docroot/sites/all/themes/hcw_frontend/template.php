<?php


/**
 * Render footer menu as nav-pills.
 */
function bootstrap_menu_tree__menu_footer_menu(&$variables) {
  return '<ul class="menu nav nav-pills">' . $variables['tree'] . '</ul>';
}

function hcw_frontend_preprocess_page(&$vars) {
    if (drupal_is_front_page()) {
        unset($vars['page']['content']['system_main']['default_message']);
        drupal_set_title('');
    }
}
