<?php
  $node = menu_get_object();
  if (isset($node)) {
    if ($node->type == 'publication' || ($node->type == 'article' && $node->article_type_code == 'section')) {
      if (!empty($tagged_wikis)) {?>
  <div id="related-wiki" class="<?php print $classes; ?>"<?php print $attributes; ?>>
      <?php
        foreach ($tagged_wikis as $wiki) {
          print render($wiki);
        }?>
  </div>
      <?php
      }
    }
  }
?>
