(function($){
    Drupal.behaviors.osha_publication = {
        attach: function(context, settings) {
            var $form = $('#osha-publication-menu-case-studies-form, #osha-publication-menu-publications-form');
            $form.find('input[type=checkbox]').click(function(){
                var $container = $(this).closest('.form-checkboxes');
                if ($(this).val() != 0) {
                    $container.find('[value=0]').prop('checked', false);
                }
                else {
                    $container.find('[type=checkbox]').not(this).prop('checked', false);
                }
                if ($container.find(':checked').length == 0) {
                    $container.find('[value=0]').prop('checked', true);
                }
                $form.submit();
            });
        }
    }
})(jQuery);
