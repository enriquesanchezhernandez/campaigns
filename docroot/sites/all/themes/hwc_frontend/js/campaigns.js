jQuery(document).ready(function() {

	var windowWidth= jQuery(window).width();//window size

	jQuery(window).resize(function() {
	    windowWidth= jQuery(window).width();//window size, when resizing
	});

	/*specific functions for tablet and/or mobile */
	funcionesTabletMovil();

	funcionesMovil();
	

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
			
		}
	}	

});