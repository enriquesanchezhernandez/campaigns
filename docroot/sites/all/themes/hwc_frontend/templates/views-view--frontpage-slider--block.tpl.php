<?php

/**
 * @file
 * Main view template.
 *
 * Variables available:
 * - $classes_array: An array of classes determined in
 *   template_preprocess_views_view(). Default classes are:
 *     .view
 *     .view-[css_name]
 *     .view-id-[view_name]
 *     .view-display-id-[display_name]
 *     .view-dom-id-[dom_id]
 * - $classes: A string version of $classes_array for use in the class attribute
 * - $css_name: A css-safe version of the view name.
 * - $css_class: The user-specified classes names, if any
 * - $header: The view header
 * - $footer: The view footer
 * - $rows: The results of the view query, if any
 * - $empty: The empty text to display if the view is empty
 * - $pager: The pager next/prev links to display, if any
 * - $exposed: Exposed widget form/info to display
 * - $feed_icon: Feed icon to display, if any
 * - $more: A link to view more, if any
 *
 * @ingroup views_templates
 */
?>
<?php
/** @var array $rows */
/** @var array $variables */
/** @var view $view */
$view = $variables['view'];
$intNumberOfItems = count($view->result);
setcookie('numberOfItems', $intNumberOfItems, time() + 3600);
?>
<script>
  jQuery(document).ready(function ($) {
    var options = {
      $AutoPlay: true,
      $SlideWidth: 1100,
      $SlideHeight: 200,
      $BulletNavigatorOptions: {
        $Class: $JssorBulletNavigator$,
        $ChanceToShow: 2,
        $AutoCenter: 1
      }
    };
    new $JssorSlider$('homepage_slider', options);
  });
</script>
<div class="separator_recomended_resources_home">&nbsp;</div>
<div id="homepage_slider" class="homepage-slider">
  <!-- Slides Container -->
  <div id="num_slides" u="slides">
    <?php print $rows ?>
  </div>
  <!-- Bullet navigator container -->
  <div u="navigator" class="jssorb12">
    <!-- Bullet navigator item prototype -->
    <div u="prototype"></div>
  </div>
  <!--#endregion Bullet Navigator Skin End -->
</div>
