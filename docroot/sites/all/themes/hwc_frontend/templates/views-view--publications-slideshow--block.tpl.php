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
?>
<script>
jQuery(document).ready(function ($) {
  var options = {
    $AutoPlay: false,
    $AutoPlaySteps: 1,
    $SlideDuration: 160,
    $SlideWidth: 800,
    $SlideHeight: 230,
    $SlideSpacing: 1,
    $DisplayPieces: 1,
    $HWA: false,
    $BulletNavigatorOptions: {
      $Class: $JssorBulletNavigator$,
      $ChanceToShow: 1,
      $AutoCenter: 1
    },
    $ArrowNavigatorOptions: {
      $Class: $JssorArrowNavigator$,
      $ChanceToShow: 1,
      $AutoCenter: 2,
      $Steps: 1
    }
  };
  new $JssorSlider$("publications_slideshow", options);
});
</script>
<div id="publications_slideshow">
    <div id="num_slides" u="slides" style="">
      <?php print $rows ?>
    </div>
    <?php if ($intNumberOfItems > 1): ?>
    <div u="navigator" class="jssorb03">
        <div class="prototype" u="prototype"></div>
    </div>	
    <span u="arrowleft" class="jssora03l publications"></span>
    <span u="arrowright" class="jssora03r publications"></span>
    <?php endif; ?>
</div>
