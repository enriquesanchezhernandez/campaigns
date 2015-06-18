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
    var jssor_slider1 = new $JssorSlider$("home_slider", options);
  });
</script>
<div class="separator_recomended_resources_home">&nbsp;</div>
<div id="home_slider" style="position: relative; top: 0px; left: 0px; width: 1138px; height: 160px; overflow: hidden;">
  <!-- Slides Container -->
  <div id="num_slides" u="slides" style="cursor: move; position: absolute; left: 5em; top: 0px; width: 1138px; height: 160px; overflow: hidden;">
    <?php print $rows ?>
  </div>
  <!--#region Bullet Navigator Skin Begin -->
  <style>
    /* jssor slider bullet navigator skin 12 css */
    .jssorb12 {
      position: absolute;
    }
    .jssorb12 div, .jssorb12 div:hover, .jssorb12 .av {
      position: absolute;
      /* size of bullet elment */
      width: 16px;
      height: 16px;
      background: url(sites/all/libraries/jquery-slider-master/img/b12.png) no-repeat;
      overflow: hidden;
      cursor: pointer;
    }
    .jssorb12 div { background-position: -7px -7px; }
    .jssorb12 div:hover, .jssorb12 .av:hover { background-position: -37px -7px; }
    .jssorb12 .av { background-position: -67px -7px; }
    .jssorb12 .dn, .jssorb12 .dn:hover { background-position: -97px -7px; }
  </style>
  <!-- bullet navigator container -->
  <div u="navigator" class="jssorb12" style="bottom: 16px; right: 6px;">
    <!-- bullet navigator item prototype -->
    <div u="prototype"></div>
  </div>
  <!--#endregion Bullet Navigator Skin End -->
</div>
