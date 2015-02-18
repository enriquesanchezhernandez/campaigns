<div id="join_subscribers">
	<?php if($background_image_url != NULL) {
		print theme('image', array(
			'path' => $background_image_url,
			'alt' => 'Join OSHMail subscribers',
		));
	} else {
		$theme_path = drupal_get_path('theme', variable_get('theme_default', 'osha_frontend'));
		print theme('image', array(
			'path' => $theme_path . '/images/content/blocks/join_65000_subscribers.png',
			'alt' => 'Join OSHMail subscribers',
		));
	}?>
	<div id="block_newsletter_image_text">
		<?php print $start_text . ' ' . $subscribers_no . ' ' . $end_text?>
	</div>
</div>