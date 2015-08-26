<?php


/**
 * Render footer menu as nav-pills.
 */
function bootstrap_menu_tree__menu_footer_menu(&$variables) {
  return '<ul class="menu nav nav-pills">' . $variables['tree'] . '</ul>';
}

/**
 * Implements theme_menu_link__menu_block().
 */
function hwc_frontend_menu_link__menu_block($variables) {
  $element = &$variables['element'];
  $delta = $element['#bid']['delta'];

  // Add homepage Icon.
  /*$attr = drupal_attributes($element['#attributes']);
  if (isset($variables['element']['#href']) &&
    $variables['element']['#href'] == '<front>' &&
    isset($element['#localized_options']['content']['image'])
  ) {
    $path = file_create_url($element['#localized_options']['content']['image']);
    $link = l('<img src="' . $path . '" />', $element['#href'],
      array('html' => TRUE, 'attributes' => $element['#localized_options']['attributes'])
    );
    return sprintf("\n<li %s>%s</li>", $attr, $link);
  }*/

  // Render or not the Menu Image.
  // Get the variable provided by osha_menu module.
  $render_img = variable_get('menu_block_' . $delta . '_' . HWC_MENU_RENDER_IMG_VAR_NAME, 0);
  if (!$render_img) {
    return theme_menu_link($variables);
  }
  // $element['#attributes']['data-image-url'] = $image_url;
  $output_link = l($element['#title'], $element['#href'], $element['#localized_options']);

  $output_image = "";
  if (!empty($element['#localized_options']['content']['image'])
    && $image_url = file_create_url($element['#localized_options']['content']['image'])) {
    $image = '<img src="' . $image_url . '"/>';
    $output_image = l($image, $element['#href'], array('html' => TRUE));
  }

  return '<li' . drupal_attributes($element['#attributes']) . '>
    <div class="introduction-title">' . $output_link . '</div>
    <div class="introduction-image">' . $output_image . '</div>
    </li>';
}

/**
 * Overrides theme_menu_link().
 */
function hwc_frontend_menu_link(array $variables) {
  $element = $variables['element'];
  $sub_menu = '';

  if ($element['#below']) {
    // Prevent dropdown functions from being added to management menu so it
    // does not affect the navbar module.
    if (($element['#original_link']['menu_name'] == 'management') && (module_exists('navbar'))) {
      $sub_menu = drupal_render($element['#below']);
    }
    elseif ((!empty($element['#original_link']['depth'])) && ($element['#original_link']['depth'] == 1)) {
      // Add our own wrapper.
      unset($element['#below']['#theme_wrappers']);
      $sub_menu = '<ul class="dropdown-menu">' . drupal_render($element['#below']) . '</ul>';
      // Generate as standard dropdown.
      $element['#title'] .= ' <span class="caret"></span>';
      $element['#attributes']['class'][] = 'dropdown';
      $element['#localized_options']['html'] = TRUE;

      // Set dropdown trigger element to # to prevent inadvertant page loading
      // when a submenu link is clicked.
//      $element['#localized_options']['attributes']['data-target'] = '#';
      $element['#localized_options']['attributes']['class'][] = 'dropdown-toggle';
//      $element['#localized_options']['attributes']['data-toggle'] = 'dropdown';
    }
  }
  // On primary navigation menu, class 'active' is not set on active menu item.
  // @see https://drupal.org/node/1896674
  if (($element['#href'] == $_GET['q'] || ($element['#href'] == '<front>' && drupal_is_front_page())) && (empty($element['#localized_options']['language']))) {
    $element['#attributes']['class'][] = 'active';
  }

  // Add image to menu item
//  if (isset($variables['element']['#href']) && isset($element['#localized_options']['content']['image'])) {
//    $path = file_create_url($element['#localized_options']['content']['image']);
//    $link = l('<img src="' . $path . '" />', $element['#href'],
//      array('html' => TRUE, 'attributes' => $element['#localized_options']['attributes'])
//    );
//    return '<li' . drupal_attributes($element['#attributes']) . '>' . $link . "</li>\n";
//  }

  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
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
        case 'publication':
          $link_title = t('Back to publications list');
          $link_href = 'publications';
          $vars['page']['above_title']['title-alternative'] = array(
            '#type' => 'item',
            '#markup' => t('Publications'),
            '#prefix' => '<strong class="title-alt">', '#suffix' => '</strong>'
          );
          break;
        case 'press_release':
          $link_title = t('Back to press releases list');
          $link_href = 'press-room';
          $vars['page']['above_title']['title-alternative'] = array(
            '#type' => 'item',
            '#markup' => t('Press releases'),
            '#prefix' => '<strong class="title-alt">', '#suffix' => '</strong>'
          );
          break;
        case 'news':
          $link_title = t('Back to news');
          $link_href = 'news';
          $vars['page']['above_title']['title-alternative'] = array(
            '#type' => 'item',
            '#markup' => t('News'),
            '#prefix' => '<strong class="title-alt">', '#suffix' => '</strong>'
          );
          break;
        case 'infographic':
          $link_title = t('Back to infographics list');
          $link_href = 'infographics';
          $vars['page']['above_title']['title-alternative'] = array(
            '#type' => 'item',
            '#markup' => t('Infographics'),
            '#prefix' => '<strong class="title-alt">', '#suffix' => '</strong>'
          );
          break;

        case 'campaign_materials':
          $link_title = t('Back to campaign materials list');
          $link_href = 'campaign-materials';
          $vars['page']['above_title']['title-alternative'] = array(
            '#type' => 'item',
            '#markup' => t('Campaign materials'),
            '#prefix' => '<strong class="title-alt">', '#suffix' => '</strong>'
          );
          break;

      }
      if (isset($link_title)) {
        $vars['page']['above_title']['back-to-link'] = array(
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
    if ($node->type == 'practical_tool') {
      ctools_include('plugins');
      ctools_include('context');
      $pb = path_breadcrumbs_load_by_name('practical_tools_details_page');
      $breadcrumbs = _path_breadcrumbs_build_breadcrumbs($pb);
      drupal_set_breadcrumb($breadcrumbs);
    }
    if ($node->type == 'campaign_materials') {
      ctools_include('plugins');
      ctools_include('context');
      $pb = path_breadcrumbs_load_by_name('campaign_materials_details_page');
      $breadcrumbs = _path_breadcrumbs_build_breadcrumbs($pb);
      drupal_set_breadcrumb($breadcrumbs);
    }
  }
}

/**
 * Theme flexible layout of panels.
 * Copied the panels function and removed the css files.
 */
function hwc_frontend_panels_flexible($vars) {
  $css_id = $vars['css_id'];
  $content = $vars['content'];
  $settings = $vars['settings'];
  $display = $vars['display'];
  $layout = $vars['layout'];
  $handler = $vars['renderer'];

  panels_flexible_convert_settings($settings, $layout);

  $renderer = panels_flexible_create_renderer(FALSE, $css_id, $content, $settings, $display, $layout, $handler);

  $output = "<div class=\"panel-flexible " . $renderer->base['canvas'] . " clearfix\" $renderer->id_str>\n";
  $output .= "<div class=\"panel-flexible-inside " . $renderer->base['canvas'] . "-inside\">\n";

  $output .= panels_flexible_render_items($renderer, $settings['items']['canvas']['children'], $renderer->base['canvas']);

  // Wrap the whole thing up nice and snug
  $output .= "</div>\n</div>\n";

  return $output;
}
function hwc_frontend_preprocess_node(&$vars) {
  if (isset($vars['content']['links']['node']['#links']['node-readmore'])) {
    $vars['content']['links']['node']['#links']['node-readmore']['title'] = t('See more');
  }

  $view_mode = $vars['view_mode'];
  $vars['theme_hook_suggestions'][] = 'node__' . $view_mode;
  $vars['theme_hook_suggestions'][] = 'node__' . $vars['node']->type . '__' . $view_mode;
  $vars['theme_hook_suggestions'][] = 'node__' . $vars['node']->nid . '__' . $view_mode;
}

function hwc_frontend_preprocess_image_style(&$variables) {
  $variables['attributes']['class'][] = 'img-responsive';
}

/**
 * Implements theme_on_the_web_image().
 *
 * @param $variables
 *   An associative array with generated variables.
 *
 * @return
 *   HTML for a social media icon.
 */

function hwc_frontend_on_the_web_image($variables) {
  $service = $variables['service'];
  $title   = $variables['title'];
  $size    = variable_get('on_the_web_size', 'sm');
  $variables = array(
    'alt'   => $title,
    'path'  => drupal_get_path('theme', 'hwc_frontend') . '/images/social_icons/' . $size . '/' . $service . '.png',
    'title' => $title
  );
  return theme('image', $variables);
}
