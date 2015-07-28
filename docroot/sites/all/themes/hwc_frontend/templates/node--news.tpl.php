<?php
/**
 * @file
 * Returns the HTML for speakers.
 */
?>

<?php
  print render($content['title_field']);
  print render($content['links']['#links']['addtoany']['title']);
  // We hide the comments and links now so that we can render them later.
  hide($content['comments']);
  hide($content['links']);
  print render($content);
?>
