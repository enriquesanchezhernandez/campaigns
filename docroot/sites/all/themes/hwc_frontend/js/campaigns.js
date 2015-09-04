//Fixing responsive menu to iPhone
jQuery(document).ready(function() {

	var windowWidth= jQuery(window).width();

	jQuery(window).resize(function() {
	    windowWidth= jQuery(window).width();
	});

	if(windowWidth <= 767){
		jQuery(".form-item-relevant-for > label").click(function() {
			jQuery(this).toggleClass("closeLabel");
			jQuery("#edit-relevant-for").toggle();
		});
		jQuery(".form-item-languages > label").click(function() {
			jQuery(this).toggleClass("closeLabel");
			jQuery("#edit-languages").toggle();
		});

		/*by endika*/
		//funcion para el menu, convertir las rayas en x
		jQuery(".navbar-toggle").on("click", function () {
	    	jQuery(this).toggleClass("active");
		});

		//funciones para desplegables detalle press room
		jQuery(".pane-osha-press-release-osha-press-rel-become-partner h2").on("click", function(){
			jQuery(".pane-osha-press-release-osha-press-rel-become-partner .pane-content").slideToggle("fast");
		});
		jQuery(".pane-press-contacts h2").on("click", function(){
			jQuery(".pane-press-contacts .pane-content").slideToggle("fast");
		});
		jQuery(".pane-osha-press-release-osha-press-kit h2").on("click", function(){
			jQuery(".pane-osha-press-release-osha-press-kit .pane-content").slideToggle("fast");
		});
	}
	
	
});