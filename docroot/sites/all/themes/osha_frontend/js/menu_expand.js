/* Expand vertical (left, right) menu on click */
jQuery(document).ready(function() {
    jQuery(function(){
        jQuery('div#block-menu-block-2>ul#menu>li').hoverIntent(function(){
            jQuery(this).find('>ul').fadeIn('fast');
        },function(){
            jQuery(this).find('>ul').fadeOut('fast');
        });
    });
});