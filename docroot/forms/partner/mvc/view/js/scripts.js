$(document).ready(function() {
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
     * Confirms validations of Email
     * @param field
     */
    function validateEmail(field) {
        if ($("#contact_osh_mainemail").val() != $(field).val()) {
            $("#contact_osh_mainemail").addClass("error");
        } else {
            $("#contact_osh_mainemail").removeClass("error");
        }
    }

    /**
     * Check all sections to find validation errors
     */
    function checkSections() {
        var ret = true;
        $("#sidebar-top .section").each(function (id, item) {
            var elemId = $(item).attr("data-section");
            if (!checkSingleSection(elemId)) {
                $("." + elemId).addClass("sidebar-error");
                ret = false;
            } else {
                $("." + elemId).removeClass("sidebar-error");
            }
        });
        if (ret) {
            $(".main-form").removeClass("error-form");
        } else {
            $(".main-form").addClass("error-form");
        }
    }

    /**
     * Check a single section to find validation errors
     * @param section
     */
    function checkSingleSection(section) {
        return !($(".main-form input[data-error='true'][data-section='" + section + "']").length);
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

    $("#contact_osh_confirm_mainemail").on({
        change: function () {
            validateEmail(this);
        }, blur: function () {
            validateEmail(this);
        }
    });

    /**
     * If there are errors, the form cannot be submitted
     */
    $(".main-form").on({
        submit: function (e) {
            if (buttonPressed == "next") {
                if ($(".main-form input[data-error='true']").length ||
                    $(".main-form").hasClass("error-form")) {
                    alert("Error: Some fields contain errors");
                    e.preventDefault();
                    return false;
                } else if (!checkRequiredFields()) {
                    alert("Error: You must fill all the required fields");
                    e.preventDefault();
                    return false;
                } else if ($('#form form').hasClass("current") && $('#form form input:enabled').length) {
                    if (!confirm("There are fields unconfirmed. Do you want to continue?")) {
                        e.preventDefault();
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
    $("#form").on("click", ".repeatable-button", function(e) {
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
            $(clonedElement).attr("id", clonedElementId + "_" + items);
            $(targetElement).append(clonedElement);
        }
        if (items >= 4) {
            $(this).hide();
        }
        e.preventDefault();
    });

    /**
     * Validation widget
     */
    $(".validation").click(function(e) {
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
    $("#save").click(function(e) {
        buttonPressed = "save";
        var url = $("#form form").attr("action");
        var tmpRegex = new RegExp("(action=)[a-z]+", 'ig');
        var newVal = "save";
        var newAction = url.replace(tmpRegex, '$1' + newVal);
        $("#form form").attr("action", newAction);
        $("#form form").submit();
    });

    /**
     * Next action
     */
    $("#next").click(function(e) {
        buttonPressed = "next";
    });

    /**
     * Enable all fields before submitting the form
     */
    $("#form form").submit(function(e) {
        $("#form form :input").prop("disabled", false);
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

});
