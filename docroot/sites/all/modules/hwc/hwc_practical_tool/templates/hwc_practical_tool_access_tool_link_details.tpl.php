<?php
global $language;
$separator = ', ';
$shown = FALSE;
$en_link = FALSE;
$entities_to_load = array();
foreach ($items as $item) {
  $entities_to_load[] = $item['value'];
}
$entities = entity_load('field_collection_item', $entities_to_load);
?>
<div class="field field-access-tool-link field-type-field-collection field-label-inline clearfix">
  <div class="field-label"><?php print $label_1; ?>&nbsp;</div>
  <div class="field-items">
    <?php foreach ($entities as $key => $entity): ?>
        <?php
        $language_code = $entity->field_available_languages['und'][0]['langcode'];
        if ($language_code == 'en') {
          $en_link = $entity->field_access_tool_link['und'][0]['url'];
        }
        if ($language_code == $language->language): ?>
          <?php
          $link = $entity->field_access_tool_link['und'][0]['url'];
          $shown = TRUE;
          ?>
          <a href="<?php print $link; ?>" class="access-tool-link">
            <?php print $node->title->value(); ?>
          </a>
        <?php endif; ?>
    <?php endforeach; ?>
    <?php if (!$shown): ?>
      <?php if ($en_link): ?>
        <a href="<?php print $en_link; ?>" class="access-tool-link">
          <?php print $node->title->value(); ?>
        </a>
      <?php else: ?>
        <a href="<?php print reset($entities)->field_access_tool_link['und'][0]['url']; ?>" class="access-tool-link">
          <?php print $node->title->value(); ?>
        </a>
      <?php endif; ?>
    <?php endif; ?>
  </div>
</div>

<div class="field field-access-tool-link field-type-field-collection access-tool-languages field-label-inline clearfix">
  <div class="field-label"><?php print $label_2; ?>&nbsp;</div>
  <div class="field-items">
    <?php $key = 1; ?>
    <?php foreach ($entities as $entity): ?>
        <?php
        $language_name = $entity->field_available_languages['und'][0]['name'];
        $language_code = $entity->field_available_languages['und'][0]['langcode'];
        ?>
        <span>
          <span class="access-tool-language-name">
            <?php print $language_name; ?>
          </span>
          <span class="access-tool-language-code">
            <?php
            print ' (' . strtoupper($language_code) . ')';
            print $key < count($entities) ? $separator : '';
            $key++;
            ?>
          </span>
        </span>
    <?php endforeach; ?>
  </div>
</div>
