<?php foreach ($items as $item): ?>
  <a href="<?php print $item['url']; ?>" class="external-link">
    <?php print $item['title']; ?>
  </a>
<?php endforeach; ?>
