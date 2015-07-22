<?php
/**
 * @file
 * Returns the HTML for speakers.
 */
?>

  <?php
  if ($view_mode === 'full') {
    print '<h1>' . t('News') . '</h1>';
  }
  // We hide the comments and links now so that we can render them later.
  hide($content['comments']);
  hide($content['links']);
  print render($content);
  ?>
