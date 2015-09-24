<?php
$class = 'facetapi-checkbox facetapi-inactive facetapi-makeCheckbox-processed facetapi-disableClick-processed';
$query = array();
if (isset($_GET['form_token'])) {
  $query['form_token'] = $_GET['form_token'];
}
if (isset($_GET['search_block_form'])) {
  $query['search_block_form'] = $_GET['search_block_form'];
}
if (isset($_GET['sort_by'])) {
  $query['sort_by'] = $_GET['sort_by'];
}
$link = l(t('All'),'/search',array(
  'attributes' => array(
    'class' => $class,
  ),
  'query' => $query,
));
?>
<h2 class="block-title"><?php print $title; ?></h2>
<ul class="facetapi-facetapi-checkbox-links facetapi-facet-type facetapi-processed no-margin-bottom">
  <li class="leaf first">
    <input type="checkbox" class="facetapi-checkbox" id="facetapi-link--all--checkbox" <?php print !isset($_GET['f']) ? 'checked' : ''; ?>>
    <?php print $link; ?>
  </li>
</ul>
<?php print $content; ?>
<script>
  jQuery('#facetapi-link--all--checkbox').click(function(){
    window.location.href = jQuery(this).next().attr('href');
  });
</script>
