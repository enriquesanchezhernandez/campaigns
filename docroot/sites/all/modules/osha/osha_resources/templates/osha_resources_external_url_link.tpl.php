<?php foreach ($items as $item): ?>
  <a href="<?php print $item['url']; ?>" class="external-link">
    <?php print $item['title']; ?>
    <i class="glyphicon glyphicon-new-window"></i>
  </a>
<?php endforeach; ?>