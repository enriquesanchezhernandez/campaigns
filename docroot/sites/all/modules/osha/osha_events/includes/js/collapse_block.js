jQuery(document).ready(function()
{
    // init: collapse all groups
    osha_events_hide_date_filters();

    // click event: toggle visibility of group clicked (and update icon)
    jQuery(".events-filter-by-date h3").click(function()
    {
        osha_events_hide_date_filters();

        jQuery(this).siblings("ul").slideToggle();
		jQuery(this).toggleClass("expand");
    });
});

function osha_events_hide_date_filters(){
    jQuery(".events-filter-by-date ul").each(function(i)
    {
        jQuery(this).hide();
    });
}