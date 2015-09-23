jQuery(document).ready(function() {

	var windowWidth= jQuery(window).width();//capturamos el tamaño de la ventana

	jQuery(window).resize(function() {
	    windowWidth= jQuery(window).width();//capturamos el tamaño de la ventana al redimensionarla
	});

	/*funcion contenedora de funciones exclusivas para tablet y/o movil*/
	funcionesTabletMovil();

	/*funcion contenedora de funciones exclusivas para movil*/
	funcionesMovil();

	/**Funciones independientes de la resolucion**/
	




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

			//funciones para desplegables detalle press room
			jQuery(".pane-osha-press-release-osha-press-rel-become-partner h2").on("click", function(){
				jQuery(".pane-osha-press-release-osha-press-rel-become-partner h2").toggleClass("closeLabel");
				jQuery(".pane-osha-press-release-osha-press-rel-become-partner .pane-content").slideToggle("fast");
			});
			jQuery(".pane-press-contacts h2").on("click", function(){
				jQuery(".pane-press-contacts h2").toggleClass("closeLabel");
				jQuery(".pane-press-contacts .pane-content").slideToggle("fast");
			});
			jQuery(".pane-osha-press-release-osha-press-kit h2").on("click", function(){
				jQuery(".pane-osha-press-release-osha-press-kit h2").toggleClass("closeLabel");
				jQuery(".pane-osha-press-release-osha-press-kit .pane-content").slideToggle("fast");
			});

			dropdownMenu();//<-----menu nav desplegable para movil/tablet
			
		}//<-----Fin funciones movil
	}
	
	//<------Funciones independientes de la resolucion
	function dropdownMenu () {//<----menu desplegable movil/tablet
		jQuery(".dropdown-menu").hide();
		jQuery(".expanded.dropdown").removeClass('active-trail');
		jQuery(".expanded.dropdown").on("click", function(){
			
			if (!jQuery(this).hasClass("active-trail")) {
				
				jQuery(this).addClass('active-trail');
				jQuery(this).siblings().removeClass("active-trail");
				jQuery(this).children('ul').children('li').removeClass("active-trail");
				jQuery(".dropdown-menu").slideUp();
				jQuery(this).children('ul').slideDown();
			}else{

				jQuery(this).removeClass('active-trail');
				jQuery(this).children('ul').slideUp();
			};
		});

		jQuery(".dropdown-menu > li").on("click", function(){

			if (!jQuery(this).hasClass("active-trail")) {
				jQuery(this).addClass('active-trail');

			}else{
				jQuery(this).removeClass('active-trail');
			};
		});
	}
	//<------Fin funciones independientes de la resolucion

});