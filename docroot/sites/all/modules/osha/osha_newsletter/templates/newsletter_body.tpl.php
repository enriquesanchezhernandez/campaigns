<?php
  if (isset($campaign_id)) {
    $url_query = array('pk_campaign' => $campaign_id);
  } else {
    $url_query = array();
  }
  ?>
<link href='http://fonts.googleapis.com/css?family=Oswald:400,300,700' rel='stylesheet' type='text/css'>
<style>
a{
	text-decoration: none !important;
	color: #003399 !important;
}
	a:before{
		content: ">";
		padding-left: 10px;
	}

table, tr, td{
	border: 0px;
	border-color: #FFFFFF;
}
</style>

<?php if(!empty($newsletter_intro)){ ?>
 <div style="width: 400px; margin-top: -130px; margin-left: 420px; margin-bottom: 100px; color: white; font-style: italic;"> <?php print($newsletter_intro);?></div>
<?php } ?>

<table border="0" cellpadding="20" cellspacing="0" width="800" style="margin-left: 25px;">
  <tbody>
	<tr>
	   <td width="550" style="padding-top: 0px; vertical-align: top; padding-right: 50px;" class="left-column">
		<?php
		  $elements_no = sizeof($items);
		  // Delete title 'News'.
		  unset($items[0]);
		  foreach ($items as $idx => $item) {
			if ($item['#entity_type'] == 'taxonomy_term' && ($idx+1 <= $elements_no)) {
			  if (($idx == $elements_no-1) && ($items[$idx]['#entity_type'] == 'taxonomy_term')) {
				continue;
			  } else if (($items[$idx+1]['#entity_type'] == 'taxonomy_term')) {
				continue;
			  } else {
				if ($idx != 0) {?>
				  <table border="0" cellpadding="0" cellspacing="0" class="blue-line" width="100%">
					<tbody>
					<tr>
					  <td style="padding-top: 15px;"></td>
					</tr>
					<tr>
					  <td width="100%" style="background-color:#003399; height: 4px;" valign="top"></td>
					</tr>
					</tbody>
				  </table>
				<?php
				}
				print(render($item));
			  }
			} else {
			  if ($idx != 1 && $item["#view_mode"] == "highlights_item") {?>
				<table border="0" cellpadding="0" cellspacing="0" width="100%">
				  <tbody>
				  <tr>
					<td style="border-bottom:2px dotted #CFDDEE;padding-top:0px;"></td>
				  </tr>
				  <tr>
					<td></td>
				  </tr>
				  </tbody>
				</table>
			  <?php
			  }
			  print(render($item));
			}
		  }
		?>
	  </td>

	  <td width="180" style="vertical-align: top; padding-top: 0px; padding-right: 0px;" class="right-column">
		<?php
		if (!empty($events) && sizeof($events) > 1) {
			foreach ($events as $item) {
			  print(render($item));
			}?>
			
		<table border="0" cellpadding="0" cellspacing="0" width="100%" style="padding-bottom: 15px;" class="pink-arrow">
		  <tbody>
		  <tr>
			<td style="font-family: Oswald, Arial, sans-serif; font-size: 16px; color: #003399; text-align: right; font-weight: bold">
			  <span>
				  <?php
				  $directory = drupal_get_path('module','osha_newsletter');
				  $site_url = variable_get('site_base_url', 'http://osha.europa.eu');
				  /*print l(theme('image', array(
					'path' => $directory . '/images/pink-arrow.png',
					'width' => 19,
					'height' => 11,
					'alt' => 'link arrow',
				  )), $site_url, array(
					'html' => TRUE,
					'external' => TRUE
				  ));*/
				  print l(t('More events'), url('events', array('absolute' => TRUE)), array(
					'attributes' => array('style' => 'color: #003399; text-decoration: none;'),
					'query' => $url_query,
					'external' => TRUE)
				  );

				  ?>
				</span>
			</td>
		  </tr>
		  </tbody>
		</table>
		<?php
		}
		?>
	  </td>
	</tr>
  </tbody>
</table>




