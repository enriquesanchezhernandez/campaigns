(function($) {
    $(function() {
        var id = '';
        var name = '';
        var tab_container = $('div.quicktabs-wrapper div.quicktabs_main');

        $('ul.quicktabs-tabs').addClass('hidden-xs');
        $('.hwc-alphabet-container').addClass('hidden-xs');

        $('ul.quicktabs-tabs').parent().prepend('<select class="select_from_tabs visible-xs"></select>');

        $('ul.quicktabs-tabs li').each(function() {
            id = $(this).find('a').attr('id');
            name = $(this).find('a').text();
            $('.select_from_tabs').prepend('<option value="'+id+'">'+name+'</option>');
        });

        $('.select_from_tabs').change(function(){
            var tab = $(this).val().replace('quicktabs-tab','#quicktabs-tabpage');
            tab_container.find('div.quicktabs-tabpage').addClass('quicktabs-hide');
            tab_container.find(tab).removeClass('quicktabs-hide');
        });
    });
})(jQuery);
