jQuery(document).ready(function(){
    var id = '';
    var name = '';
    var tab_container = jQuery('#quicktabs-container-view__partners_list__block');

    jQuery('ul.quicktabs-tabs').addClass('hidden-xs');
    jQuery('.hwc-alphabet-container').addClass('hidden-xs');

    jQuery('ul.quicktabs-tabs').parent().prepend('<select id="select_from_tabs" class="visible-xs"></select>');

    jQuery('ul.quicktabs-tabs li').each(function() {
        id = jQuery(this).find('a').attr('id');
        name = jQuery(this).find('a').text();
        jQuery('#select_from_tabs').prepend('<option value="'+id+'">'+name+'</option>');
    });

    jQuery('#select_from_tabs').change(function(){
        var tab = jQuery(this).val().replace('quicktabs-tab','#quicktabs-tabpage');
        tab_container.find('div.quicktabs-tabpage').addClass('quicktabs-hide');
        tab_container.find(tab).removeClass('quicktabs-hide');
    });
})