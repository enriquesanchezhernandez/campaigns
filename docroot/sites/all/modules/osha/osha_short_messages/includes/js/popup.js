jQuery(document).ready(function() {
    //create dialog window to access the iframe
    displayDialog();
    jQuery( "#preview_message" ).dialog('close');
});

/**
 * Populate dialog window with the editor content
 * The HTML is inserted in an iframe to not use the site css styles
 */
function displayDialog(){

    var editorContent = jQuery('#edit-short-messages-content-value_ifr').contents().find("body").html();

    var $frm = jQuery("#preview_content");
    var $doc = $frm[0].contentWindow ? $frm[0].contentWindow.document : $frm[0].contentDocument;
    var $body = jQuery($doc.body);
    $body.html(''); // clear iFrame contents
    $body.append(editorContent); // use this to write something into the iFrame

    //add css to html head
    jQuery($doc.head).append('<style>' +
        '.field-name-field-image{float: left;min-height: 95px;min-width: 100px;padding-bottom: 1em;padding-right: 1em;}' +
        '.views-field-field-press-contact-job-title {font-size: 0.9em;font-weight: bold; margin-bottom: 5px}' +
        '.views-field-title a {color: #003399;font-size: 0.9em;text-decoration: none;}' +
        '.views-field-field-press-contact-phone {font-size: 0.9em;}' +
        '.views-field-field-press-contact-email a {color: #003399;font-size: 0.9em;font-weight: bold;text-decoration: none;}' +
        '.view-footer {margin-top:10px}' +
        '.view-footer a {color: #003399; text-decoration: none; font-weight: bold; margin-left:4px}' +
        '</style>');

    //display dialog
    jQuery( "#preview_message" ).dialog({
        width: '850px'
    });

    //set iframe height
    setIframeHeight(jQuery("#preview_content").get(0));
}

/**
 * Adjust height to match content
 * @param iframe
 */
function setIframeHeight(iframe) {
    if (iframe) {
        var iframeWin = iframe.contentWindow || iframe.contentDocument.parentWindow;
        if (iframeWin.document.body) {
            iframe.height = iframeWin.document.documentElement.scrollHeight || iframeWin.document.body.scrollHeight;
        }
    }
};