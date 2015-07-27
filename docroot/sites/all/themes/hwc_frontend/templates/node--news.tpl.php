<?php
/**
 * @file
 * Returns the HTML for speakers.
 */
?>

<?php
  if ($view_mode === 'full') {
    print '<h1>' . t('News') . '</h1>';
    print l(t('Back to news'), 'news', array('attributes' => array('class' => 'back-to-link pull-right')));
  }

  print render($content['title_field']);
  print render($content['links']['#links']['addtoany']['title']);
  // We hide the comments and links now so that we can render them later.
  hide($content['comments']);
  hide($content['links']);
  print render($content);
?>
