<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (!$label_hidden): ?>
    <div class="field-label"<?php print $title_attributes; ?>><?php print $label ?>:&nbsp;</div>
  <?php endif; ?>
  <div class="field-items"<?php print $content_attributes; ?>>
    <?php 
    $bundles = array(
      'youtube' => 'YouTube',
      'slideshare' => 'SlideShare',
      'flickr' => 'Flickr',
      'infographic' => 'Infographics',
      'external_url' => t('External resources'),
      'file' => t('Files'),
      'publication' => t('Publications'),
      'news' => t('News'),
      'highlights' => t('Highlights'),
      'events' => t('Events'),
    );
    $node_type = '';
    print '<div class="additional_resource_group '.$node_type.'">';
    foreach ($items as $delta => $item): ?>
      <?php
        if (isset($item['node'])) {
          $value = reset($item['node']);
          if ($node_type != $value['#bundle']) {
            // this is a new bundle type
            $node_type = $value['#bundle'];
            print '</div><div class="additional_resource_group '.$node_type.'"><span class="additional_resource_title">'.$bundles[$node_type].'</span>';
          }
        }
      ?>
      <div class="field-item <?php print $delta % 2 ? 'odd' : 'even'; ?>"<?php print $item_attributes[$delta]; ?>>
        <?php print render($item); ?>
      </div>
    <?php endforeach;?>
    </div>
  </div>
</div>
