<?php


/**
 * Render footer menu as nav-pills.
 */
function bootstrap_menu_tree__menu_footer_menu(&$variables) {
  return '<ul class="menu nav nav-pills">' . $variables['tree'] . '</ul>';
}

function hwc_frontend_preprocess_page(&$vars) {
    if (drupal_is_front_page()) {
        unset($vars['page']['content']['system_main']['default_message']);
        drupal_set_title('');
    }

    // add back to links (e.g. Back to news)
    if (isset($vars['node'])) {
      $node = $vars['node'];
      switch ($node->type) {
        case 'news':
          $link_title = 'Back to news';
          $link_href = 'news';
          break;
      }
      if (isset($link_title)) {
        $vars['page']['content']['back-to-link'] = array(
            '#type' => 'item',
            '#markup' => l($link_title, $link_href, array('attributes' => array('class' => array('back-to-link pull-right')))),
        );
      }
    }
  if ($node = menu_get_object()) {
    if ($node->type == 'publication') {
      ctools_include('plugins');
      ctools_include('context');
      $pb = path_breadcrumbs_load_by_name('publications_detail_page');
      $breadcrumbs = _path_breadcrumbs_build_breadcrumbs($pb);
      drupal_set_breadcrumb($breadcrumbs);
    }
  }
}
