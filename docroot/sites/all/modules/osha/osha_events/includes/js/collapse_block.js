jQuery(document).ready(function()
{
    // init: collapse all groups
    osha_events_hide_date_filters(1);

    // click event: toggle visibility of group clicked (and update icon)
    jQuery(".events-filter-by-date h3").click(function()
    {
        osha_events_hide_date_filters(0);

        jQuery(this).siblings("ul").slideToggle();
		jQuery(this).toggleClass("expand");
    });
});

function osha_events_hide_date_filters(initial_load){
    jQuery(".events-filter-by-date ul").each(function(i)
    {
        if(!initial_load){ // onclick phase
            jQuery(this).hide();
        }else if(!jQuery(this).find('a.current_month').length && !jQuery(this).parent().find('a.current_year').length){ // init phase
            jQuery(this).hide();
        }
    });
}