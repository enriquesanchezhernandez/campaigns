<?php
$class = 'facetapi-checkbox facetapi-inactive facetapi-makeCheckbox-processed facetapi-disableClick-processed';
$link = l(t('All'),'/search',array(
  'attributes' => array(
    'class' => $class,
  ),
  'query' => array(
    'form_token' => $_GET['form_token'],
    'search_block_form' => $_GET['search_block_form'],
  ),
));
?>
<h2 class="block-title"><?php print $title; ?></h2>
<ul class="facetapi-facetapi-checkbox-links facetapi-facet-type facetapi-processed no-margin-bottom">
  <li class="leaf first">
    <input type="checkbox" class="facetapi-checkbox" id="facetapi-link--all--checkbox">
    <?php print $link; ?>
  </li>
</ul>
<?php print $content; ?>
