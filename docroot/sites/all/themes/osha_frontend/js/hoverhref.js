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
	
	
	/*INFOGRAPHICS*/
	
	jQuery(".view-infographic div div").each(function() {
		var obj=jQuery(this);
		jQuery(".views-field-field-thumbnail img",this).mouseover(function() {
		obj.find(".views-field-title").css("border-bottom", "10px solid #DC2E81");
		obj.find(".views-field-title a").css("background","url('/sites/all/themes/osha_frontend/images/flecha.png') 100% 25% no-repeat").css("padding-right", "1.5em");
		});
	});
	
	jQuery(".view-infographic div div").each(function() {
		var obj=jQuery(this);
		jQuery(".views-field-field-thumbnail img",this).mouseout(function() {
		obj.find(".views-field-title").css("border-bottom", "10px solid #D2DCED");
		obj.find(".views-field-title a").css("background","none");
		});
	});
	
	jQuery(".view-infographic div div").each(function() {
		var obj=jQuery(this);
		jQuery(".views-field-title",this).mouseover(function() {
		obj.find(".views-field-title").css("border-bottom", "10px solid #DC2E81");
		obj.find(".views-field-title a").css("background","url('/sites/all/themes/osha_frontend/images/flecha.png') 100% 25% no-repeat").css("padding-right", "1.5em");
		});
	});
	
	jQuery(".view-infographic div div").each(function() {
		var obj=jQuery(this);
		jQuery(".views-field-title",this).mouseout(function() {
		obj.find(".views-field-title").css("border-bottom", "10px solid #D2DCED");
		obj.find(".views-field-title a").css("background","none");
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
	
	
// Tools & Publications filters
jQuery(document).ready(function() {
    // Init: collapse all filters
    jQuery(".sidebars_first .block-facetapi .item-list ul").each(function(i) {
		jQuery(this).hide();
	});
    // Click event: toggle visibility of group clicked (and update icon)
	jQuery(".block-facetapi h2").click(function() {		
		jQuery(this).parent().find("div.item-list ul").slideToggle();
		jQuery(this).toggleClass("expand");
    });
});

/* Show searcher in responsive menu */
jQuery(document).ready(function() {
    // Click event: show language and search box
	jQuery("a[href$='#nav']").click(function() {
		showSearcher();
    });	
});
function showSearcher() {
	jQuery(".mean-container #block-lang-dropdown-language-content").toggle();
	jQuery(".mean-container #block-search-form").toggle();
}
