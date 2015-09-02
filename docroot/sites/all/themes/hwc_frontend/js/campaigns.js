//Fixing responsive menu to iPhone
jQuery(document).ready(function() {
	jQuery(".form-item-relevant-for > label").click(function() {
		jQuery(this).toggleClass("closeLabel")
		jQuery("#edit-relevant-for").toggle();
	});
	jQuery(".form-item-languages > label").click(function() {
		jQuery(this).toggleClass("closeLabel")
		jQuery("#edit-languages").toggle();
	});
});