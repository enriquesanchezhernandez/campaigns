jQuery(document).ready(function() {
    ZeroClipboard.config({
        moviePath: '/sites/all/libraries/zeroclipboard/ZeroClipboard.swf',
        forceEnhancedClipboard: true
    });

    var client = new ZeroClipboard( jQuery("#edit-short-messages-clipboard") );

    client.on( 'load', function(client) {

        client.on( 'datarequested', function(client) {
            var iframeContent = jQuery('#edit-short-messages-content-value_ifr').contents();
            //add css styles
            iframeContent.find('.views-field-field-press-contact-job-title').find('div').css({'font-size': '0.9em', 'font-weight': 'bold', 'margin-bottom':'5px'});
            iframeContent.find('.views-field-title').find('a').css({'color': '#003399', 'font-size': '0.9em', 'text-decoration': 'none'});
            iframeContent.find('.views-field-field-press-contact-phone').find('div').css({'font-size': '0.9em'});
            iframeContent.find('.views-field-field-press-contact-email').find('a').css({'color': '#003399', 'font-size': '0.9em', 'text-decoration': 'none', 'font-weight': 'bold'});
            iframeContent.find('.view-footer').css({'margin-top':'4px'});
            iframeContent.find('.view-footer').find('a').css({'color': '#003399', 'text-decoration': 'none', 'font-weight': 'bold', 'margin-left':'4px'});
            //get iframe body
            var editorContent = iframeContent.find("body").html();
            client.setText(editorContent);
        });

        // callback triggered on successful copying
        client.on( 'complete', function(client, args) {
            jQuery("<div>Copied HTML to clipboard</div>").dialog();
        });
    });

    // In case of error - such as Flash not being available
    client.on( 'wrongflash noflash', function() {
        ZeroClipboard.destroy();
    } );
});