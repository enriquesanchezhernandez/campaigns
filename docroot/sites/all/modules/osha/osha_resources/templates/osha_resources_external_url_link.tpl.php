<?php foreach ($items as $item): ?>
  <a href="<?php print $item['url']; ?>" class="external-link">
    <?php
    if (strpos($item['url'],substr($item['title'], 0, -3)) === false) {
      print $item['title'];
    } else {
      $name = isset($entity->title_field[$language->language][0])
        ? $entity->title_field[$language->language][0]['value']
        : $entity->title_field['en'][0]['value'];
      print $name;
    }?>
  </a>
<?php endforeach; ?>
