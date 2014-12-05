jQuery(document).ready(function () {
    hoverThemes();
	zoomMedium();
	hoverSlideHome();
	displayCaptcha();
});


function hoverThemes() {
	jQuery("#block-menu-block-3 ul li").each(function() {
		var obj=jQuery(this);
		jQuery(".introduction-image img",this).mouseover(function() {
		obj.find(".introduction-title").css("border-bottom", "10px solid #DC2E81");
		obj.find(".introduction-title a").css("background","url('/sites/all/themes/osha_frontend/images/flecha.png') 100% 25% no-repeat").css("padding-right", "1.5em");
		});
	});
	
	jQuery("#block-menu-block-3 ul li").each(function() {
		var obj=jQuery(this);
		jQuery(".introduction-image img",this).mouseout(function() {
		obj.find(".introduction-title").css("border-bottom", "10px solid #D2DCED");
		obj.find(".introduction-title a").css("background","none");
		});
	});
	
	jQuery("#block-menu-block-3 ul li").each(function() {
		var obj=jQuery(this);
		jQuery(".introduction-title",this).mouseover(function() {
		obj.find(".introduction-title").css("border-bottom", "10px solid #DC2E81");
		obj.find(".introduction-title a").css("background","url('/sites/all/themes/osha_frontend/images/flecha.png') 100% 25% no-repeat").css("padding-right", "1.5em");
		});
	});
	
	jQuery("#block-menu-block-3 ul li").each(function() {
		var obj=jQuery(this);
		jQuery(".introduction-title",this).mouseout(function() {
		obj.find(".introduction-title").css("border-bottom", "10px solid #D2DCED");
		obj.find(".introduction-title a").css("background","none");
		});
	});
}


function hoverSlideHome() {

	jQuery("#num_slides div").each(function() {
		jQuery(this).mouseover(function() {
		jQuery("span",this).addClass('text_white');
		jQuery("span",this).removeClass('text_blue');
		});
	});
	
	jQuery("#num_slides div").each(function() {
		jQuery(this).mouseout(function() {
		jQuery("span",this).addClass('text_blue');
		jQuery("span",this).removeClass('text_white');
		});
	});	
	
	jQuery("#num_slides div").each(function() {
		jQuery(this).mouseover(function() {
		jQuery("img",this).addClass('img_opac');
		jQuery("img",this).removeClass('img_no_opac');
		});
	});	
	
	jQuery("#num_slides div").each(function() {
		jQuery(this).mouseout(function() {
		jQuery("img",this).addClass('img_no_opac');
		jQuery("img",this).removeClass('img_opac');
		});
	});	
	
}

function displayCaptcha() {
	
	jQuery( "#edit-email" ).click(function() {
		jQuery(".captcha").show(300);
	});
	
}

        
	function zoomSmall() {
		jQuery("body").addClass("bodysmall");
		jQuery("body").removeClass("bodymedium");
		jQuery("body").removeClass("bodybig");
	}
	
	function zoomMedium() {
		jQuery("body").addClass("bodymedium");
		jQuery("body").removeClass("bodysmall");
		jQuery("body").removeClass("bodybig");
	}
	function zoomBig() {
		jQuery("body").addClass("bodybig");
		jQuery("body").removeClass("bodysmall");
		jQuery("body").removeClass("bodymedium");
	}
		
		



