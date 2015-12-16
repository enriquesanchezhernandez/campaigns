jQuery(document).ready(function() {

	var windowWidth= jQuery(window).width();//window size

	jQuery(window).resize(function() {
	    windowWidth= jQuery(window).width();//window size, when resizing
	});

	/*specific functions for tablet and/or mobile */
	funcionesTabletMovil();

	funcionesMovil();
	
	
	//Fixing responsive menu to iPhone
	jQuery(document).ready(function() {
		jQuery(".dropdown-toggle").dropdown();
		//Hover for download episodes on iPad
		document.addEventListener("touchstart", function() {},false);
	});

	/************************** FUNCTIONS *******************************/

	function funcionesTabletMovil () {
		if(windowWidth <= 992){//<-----functions for tablet and/or mobile
			
			jQuery(".form-item-relevant-for > label").click(function() {
				jQuery(this).toggleClass("closeLabel");
				jQuery("#edit-relevant-for").toggle();
			});
			jQuery(".form-item-languages > label").click(function() {
				jQuery(this).toggleClass("closeLabel");
				jQuery("#edit-languages").toggle();
			});
			jQuery(".form-item-publication-type > label").click(function() {
				jQuery(this).toggleClass("closeLabel");
				jQuery("#edit-publication-type").toggle();
			});

		}//<-----End: functions for tablet and/or mobile
	}

	function funcionesMovil () {
		jQuery("#block-menu-menu-header-login, #block-lang-dropdown-language").addClass("visibility");
		if(windowWidth <= 767){//<-----functions for mobile

			//Menu function, transform the menu icon in a x

			jQuery(".navbar-toggle").on("click", function () {
		    	jQuery(this).toggleClass("active");
				jQuery("#block-menu-menu-header-login, #block-lang-dropdown-language").toggleClass("visibility");
			});
			
			//Additional Resources Block
			
			jQuery(".field-name-field-aditional-resources h4.pane-title").click(function() {
				jQuery(this).toggleClass("closeLabel");
				jQuery(this).next("div").toggle();
			});
			
			//Press Room
			
			jQuery(".pane-osha-press-release-osha-press-rel-become-partner h2.pane-title").click(function() {
				jQuery(this).toggleClass("closeLabel");
				jQuery(this).next("div").toggle();
			});
			
			jQuery(".pane-press-contacts h2.pane-title").click(function() {
				jQuery(this).toggleClass("closeLabel");
				jQuery(this).next("div").toggle();
			});
			
			jQuery(".pane-osha-press-release-osha-press-kit h2.pane-title").click(function() {
				jQuery(this).toggleClass("closeLabel");
				jQuery(this).next("div").toggle();
			});
			
		}
	}	

});