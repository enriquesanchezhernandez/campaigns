jQuery(document).ready(function() {

	var windowWidth= jQuery(window).width();//capturamos el tamaño de la ventana

	jQuery(window).resize(function() {
	    windowWidth= jQuery(window).width();//capturamos el tamaño de la ventana al redimensionarla
	});

	/*funcion contenedora de funciones exclusivas para tablet y/o movil*/
	funcionesTabletMovil();

	funcionesMovil();
	

	/************************** Comienzo funciones especificas *******************************/

	function funcionesTabletMovil () {
		if(windowWidth <= 992){//<-----funciones exclusivas para tablet y/o movil
			
			jQuery(".form-item-relevant-for > label").click(function() {
				jQuery(this).toggleClass("closeLabel");
				jQuery("#edit-relevant-for").toggle();
			});
			jQuery(".form-item-languages > label").click(function() {
				jQuery(this).toggleClass("closeLabel");
				jQuery("#edit-languages").toggle();
			});

		}//<-----Fin funciones tablet y/o movil
	}

	function funcionesMovil () {
		jQuery("#block-menu-menu-header-login, #block-lang-dropdown-language").addClass("visibility");
		if(windowWidth <= 767){//<-----funciones exclusivas para movil

			//funcion para el menu, convertir las rayas en x

			jQuery(".navbar-toggle").on("click", function () {
		    	jQuery(this).toggleClass("active");
				jQuery("#block-menu-menu-header-login, #block-lang-dropdown-language").toggleClass("visibility");
			});
	
		}
	}	

});