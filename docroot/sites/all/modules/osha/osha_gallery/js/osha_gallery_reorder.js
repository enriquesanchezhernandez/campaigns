(function($){
    Drupal.behaviors.osha_gallery_reorder = {
        attach: function (context, settings) {
            $( "#osha_gallery_files_sort_container" ).once('osha_gallery_reorder', function(){
                $(this).sortable();
                $(this).disableSelection();
            });
        }
    };
})(jQuery);
