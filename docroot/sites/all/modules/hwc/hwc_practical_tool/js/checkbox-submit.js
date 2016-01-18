(function($){
    Drupal.behaviors.hwc_practical_tool = {
        attach: function(context, settings) {
            $('#hwc-practical-tool-menu-tools-form input[type=checkbox]', context).click(function(){
                $('#hwc-practical-tool-menu-tools-form').submit();
            });
        }
    }
})(jQuery);
