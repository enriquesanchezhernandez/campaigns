$(document).ready(function () {
    var buttonPressed;

    /**
     * Retrieve an URL parameter
     * @param key
     * @returns {Array|{index: number, input: string}|string|string}
     */
    function getUrlVar(key) {
        var result = new RegExp(key + "=([^&]*)", "i").exec(window.location.search);
        return result && decodeURI(result[1]) || "";
    }

    /**
     * Validate a field via AJAX
     * @param field
     */
    function validateField(field) {
        var urlParamsArray = {
            route: getUrlVar("route"),
            ajax: true,
            async: false,
            action: "validateAttribute",
            attribute: $(field).attr("id"),
            value: $(field).val()
        };
        var urlParams = $.param(urlParamsArray);
        var url = window.location.href;
        if (url.indexOf("?") != -1) {
            var pos = url.indexOf("?");
            url = url.substr(0, pos);
        }
        url += "?" + urlParams;
        $.get(url, function (data, status) {
            var response = jQuery.parseJSON(data);
            if (response.status) {
                $(field).removeClass("error");
                $(field).attr("data-error", "");
                if ($("#" + response.id + "_errormsg").length) {
                    $("#" + response.id + "_errormsg").remove();
                }
            } else {
                $(field).addClass("error");
                $(field).attr("data-error", "true");
                if (!$("#" + response.id + "_errormsg").length) {
                    $(field).parent().append('<div id="' + response.id + '_errormsg" class="error-msg">' + response.message + '</div>');
                }
            }
        });
    }

    /**
     * Check all sections to find validation errors
     */
    function checkSections() {
        var ret = false;
        $("#sidebar-top .section").each(function (id, item) {
            var elemId = $(item).attr("data-section");
            if ($("#" + elemId).length) {
                if (!checkSingleSection(elemId)) {
                    $("." + elemId).addClass("sidebar-error");
                    ret = false;
                } else {
                    $("." + elemId).removeClass("sidebar-error");
                }
            }
        });
    }

    /**
     * Check a single section to find validation errors
     * @param section
     */
    function checkSingleSection(section) {
        return !($(".main-form *[data-error='true'][data-section='" + section + "']").length);
    }

    /**
     * Trigger the field validation
     */
    $(".main-form input").on({
        change: function () {
            validateField(this);
        }, blur: function () {
            validateField(this);
        }
    });
    $(".main-form textarea").on({
        change: function () {
            validateField(this);
        }, blur: function () {
            validateField(this);
        }
    });

    $("#contact_osh_mainemail").on({
        blur: function () {
            validateConfirmEmail(this);
        }
    });

    $("#contact_osh_confirm_mainemail").on({
        blur: function () {
            validateConfirmEmail(this);
        }
    });

    /**
     * Validate confirmation email
     */
    function validateConfirmEmail() {
        if ($("#contact_osh_mainemail").val() != $("#contact_osh_confirm_mainemail").val()) {
            $("#contact_osh_mainemail").addClass("error");
            $("#contact_osh_mainemail").attr("data-error", "true");
            $("#contact_osh_confirm_mainemail").addClass("error");
            $("#contact_osh_confirm_mainemail").attr("data-error", "true");
            if (!$("#confirmemail_errormsg").length) {
                $("#contact_osh_confirm_mainemail").parent().append('<div id="confirmemail_errormsg" class="error-msg">The email addresses must match</div>');
            }
        } else {
            $("#contact_osh_mainemail").removeClass("error");
            $("#contact_osh_mainemail").attr("data-error", "");
            $("#contact_osh_confirm_mainemail").removeClass("error");
            $("#contact_osh_confirm_mainemail").attr("data-error", "");
            $("#confirmemail_errormsg").remove();
        }
    }

    /**
     * If there are errors, the form cannot be submitted
     */
    $(".main-form").on({
        submit: function (e) {
            if (buttonPressed == "next") {
                validateConfirmEmail();
                if ($(".main-form input[data-error='true']").length ||
                    $(".main-form textarea[data-error='true']").length ||
                    $(".main-form select[data-error='true']").length) {
                    alert("Error: Some fields contain errors");
                    e.preventDefault();
                    return false;
                } else if (!checkRequiredFields()) {
                    alert("Error: You must fill all the required fields");
                    e.preventDefault();
                    return false;
                } else if ($('#form form').hasClass("current")
                    && ($('#form form input[type=text]:enabled').length
                    || $('#form form input[type=checkbox]:enabled').length
                    || $('#form form input[type=radio]:enabled').length
                    || $('#form form textarea:enabled').length
                    || $('#form form select:enabled').length)) {
                    if (!confirm("There are fields unconfirmed. Do you want to continue?")) {
                        e.preventDefault();
                    } else {
                        $("#form form :input").prop("disabled", false);
                    }
                }
            }
        }
    });

    /**
     * Check that all the required fields are filled
     * @returns {boolean}
     */
    function checkRequiredFields() {
        var ret = true;
        var field;
        $("#form form .required .controls").each(function (id, item) {
            if (field = $(item).find("input[type=text]")) {
                if ($(field).attr("data-section") && !$(field).val()) {
                    ret = false;
                    return false;
                }
            } else if (field = $(item).find("textarea")) {
                if ($(field).attr("data-section") && !$(field).val()) {
                    ret = false;
                    return false;
                }
            } else if (field = $(item).find("select")) {
                if ($(field).attr("data-section") && !$(field).val()) {
                    ret = false;
                    return false;
                }
            }
        });
        return ret;
    }

    /**
     * Add repeated blocks of information
     */
    $("#form").on("click", ".repeatable-button-add", function (e) {
        var clonedElementId = $(this).attr("data-element");
        var clonedElement = $("#" + clonedElementId).clone(true, true);
        var targetId = $(this).attr("data-target");
        var targetElement = $("#" + targetId);
        var clonedFieldsetClass = $(clonedElement).attr("class");
        var items = $("#" + targetId + " ." + clonedFieldsetClass).length;
        if (items < 5) {
            $(clonedElement).children().find("input").each(function (id, item) {
                $(item).attr("id", $(item).attr("id") + "_" + items);
                $(item).attr("name", $(item).attr("name") + "_" + items);
            });
            var buttonRemove = $(clonedElement).children().find(".repeatable-button-remove");
            $(buttonRemove).attr("data-element", $(buttonRemove).attr("data-element") + "_" + items);
            $(clonedElement).attr("id", clonedElementId + "_" + items);
            $(targetElement).append(clonedElement);
        }
        if (items >= 4) {
            $(this).hide();
        }
        e.preventDefault();
    });

    /**
     * Remove a repeated block of information
     */
    $("#form").on("click", ".repeatable-button-remove", function (e) {
        var clonedElementId = $(this).attr("data-element");
        var clonedElement = $("#" + clonedElementId).clone(true, true);
        var targetId = $(this).attr("data-target");
        var clonedFieldsetClass = $(clonedElement).attr("class");
        var items = $("#" + targetId + " ." + clonedFieldsetClass).length;
        if (items > 1) {
            var containerId = "#" + $(this).attr("data-element");
            $(containerId).remove();
            items--;
        }
        if (items < 5 && $(".repeatable-button-add").is(":hidden")) {
            $(".repeatable-button-add").show();
        }
        e.preventDefault();
    });

    /**
     * Validation widget
     */
    $(".validation").click(function (e) {
        var dataSection = $(this).attr("data-section");
        if ($(this).hasClass("validation-pressed")) {
            $('#form form :input[data-section="' + dataSection + '"]').prop("disabled", false);
            $(this).removeClass("validation-pressed");
        } else {
            $('#form form :input[data-section="' + dataSection + '"]').prop("disabled", "disabled");
            $(this).addClass("validation-pressed");
        }
    });

    /**
     * Save action
     */
    $("#save").click(function (e) {
        buttonPressed = "save";
        var url = $("#form form").attr("action");
        var tmpRegex = new RegExp("(action=)[a-z]+", 'ig');
        var newVal = "save";
        var newAction = url.replace(tmpRegex, '$1' + newVal);
        $("#form form").attr("action", newAction);
        $("#form form").submit();
    });

    /**
     * Save action
     */
    $(".save_image").click(function (e) {
        var targetElement = "." + $(this).attr("data-target");
        var imageData = $(this).parent().find(".thumbBox").html();
        $(targetElement).html(imageData);
        e.preventDefault();
        $.magnificPopup.close();
        delete $.magnificPopup.instance.popupsCache[$(this).attr("data-cropperkey")];
        $.magnificPopup.instance.popupsCache = {};
    });

    /**
     * Next action
     */
    $("#next").click(function (e) {
        buttonPressed = "next";
    });

    /**
     * Trigger the section validation
     */
    setInterval(checkSections, 2000);

    /**
     * Dropdown multiple
     */
    $(".dropdown-multiple").select2();

    $("#refresh").click(function (e) {
        $("#captcha").attr("src", 'lib/securimage/securimage_show.php?' + Math.random());
        return false;
    });

    if (!$('#contact_osh_otherusername2').val() && !$('#contact_osh_otherusermail2').val()) {
        $('#contact_osh_otherusername2').closest('#other-users-repeteable').css({
            'display': 'none'
        });
    }
    if (!$('#contact_osh_otherusername3').val() && !$('#contact_osh_otherusermail3').val()) {
        $('#contact_osh_otherusername3').closest('#other-users-repeteable').css({
            'display': 'none'
        });
    }

    /**
     * Show / Hide Disclaimer
     */
    $('#a_disclaimer').click(function () {
        var div_class = $('#div_disclaimer_text');
        if (div_class.hasClass('hidden')) {
            div_class.removeClass('hidden');
        } else {
            div_class.addClass('hidden');
        }
    });

    /**
     * Save Data and Print
     */
    $('.action-print').click(function () {
        if ($(".main-form form").length) {
            var action = $(".main-form form").attr("action") + "&print=true";
            $(".main-form form").attr("action", action);
            if ($("#save").length) {
                $("#save").trigger("click");
            } else {
                window.open($(this).attr("data-href"), 'popup');
            }
        } else {
            window.open($(this).attr("data-href"), 'popup');
        }
    });
    $('.action-pdf').click(function () {
        if ($(".main-form form").length) {
            var action = $(".main-form form").attr("action") + "&pdf=true";
            $(".main-form form").attr("action", action);
            if ($("#save").length) {
                $("#save").trigger("click");
            } else {
                window.open($(this).attr("data-href"), 'popup');
            }
        } else {
            window.open($(this).attr("data-href"), 'popup');
        }
    });

    /**
     * Main contact change functionality
     */
    $(".main-contact-change-checkbox").click(function () {
        if ($(this).prop('checked')) {
            var contactBackup = $(".main-contact-change").clone();
            $(contactBackup).addClass("main-contact-change-backup");
            $(".main-contact-change input").each(function (id, item) {
                $(contactBackup).find("#" + $(item).attr("id")).val($(item).val());
                $(item).val("");
            });
            $(contactBackup).appendTo(".main-contact-change");
        } else {
            $(".main-contact-change-backup input").each(function (id, item) {
                $(".main-contact-change").find("#" + $(item).attr("id")).val($(item).val());
            });
            $(".main-contact-change").remove(".main-contact-change-backup");
        }
    });

    /**
     * Combined checkbox event
     */
    $(".combined-checkbox").click(function () {
        var target = "#" + $(this).attr("data-target");
        $(target).toggle();
        if ($(target).is(":hidden")) {
            $(target).val("");
        }
    });

    /**
     * Triggers the validations
     */
    $(".main-form .field").each(function (id, item) {
        $(item).focus();
        $(item).blur();
    });
    $(".main-form .field").first().focus();
});
