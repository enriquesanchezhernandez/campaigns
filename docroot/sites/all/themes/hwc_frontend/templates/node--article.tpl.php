<?php
/**
 * @file
 * Returns the HTML for an article node.
 */
?>

<article class="node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php if ($title_prefix || $title_suffix || $display_submitted || $unpublished || !$page && $title): ?>
    <header>
      <?php print render($title_prefix); ?>
      <?php if (!$page && $title): ?>
        <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
      <?php endif; ?>
      <?php print render($title_suffix); ?>

      <?php if ($display_submitted): ?>
        <p class="submitted">
          <?php print $user_picture; ?>
          <?php print $submitted; ?>
        </p>
      <?php endif; ?>
    </header>
  <?php endif; ?>

  <?php
  // We hide the comments and links now so that we can render them later.
  hide($content['comments']);
  hide($content['links']);

  $content['field_recommended_articles']['#title'] = t('Recommended for you');

  print render($content['field_image']);
  print render($content['title_field']);
  print render($content['field_summary']);
  print render($content['body']);

  print render($content['links']['#links']['addtoany']['title']);

  print render($content['field_recommended_articles']);

  unset($content['links']['#links']['addtoany']);

  ?>

  <?php print render($content['links']); ?>
  <?php print render($content['comments']); ?>

</article>
