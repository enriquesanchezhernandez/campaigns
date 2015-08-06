$(document).ready(function() {
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
        url += (url.indexOf("?") == -1) ? "?" + urlParams : "&" + urlParams;
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
        var ret = true;
        $("#sidebar .section").each(function (id, item) {
            var elemId = $(item).attr("id");
            if (!checkSingleSection(elemId)) {
                $("#" + elemId).addClass("sidebar-error");
                ret = false;
            } else {
                $("#" + elemId).removeClass("sidebar-error");
            }
        });
        if (ret) {
            $(".main-form").removeClass("error-form");
            $(".main-form #save").removeAttr("disabled");
            $(".main-form #next").removeAttr("disabled");
            $(".main-form #finish").removeAttr("disabled");
        } else {
            $(".main-form").addClass("error-form");
            $(".main-form #save").attr("disabled", "disabled");
            $(".main-form #next").attr("disabled", "disabled");
            $(".main-form #finish").attr("disabled", "disabled");
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

    /**
     * If there are errors, the form cannot be submitted
     */
    $(".main-form").on({
        submit: function (e) {
            if ($(".main-form input[data-error='true']").length) {
                e.preventDefault();
                return false;
            }
        }
    });

    /**
     * Add repeated blocks of information
     */
    $(".repeatable-section").on("click", ".add_user", function(e) {
        var clonedFieldset = $(this).parent().clone(true, true);
        var clonedFieldsetId = $(clonedFieldset).attr("id");
        var clonedFieldsetClass = $(clonedFieldset).attr("class");
        var items = $("." + clonedFieldsetClass).length;
        if (items < 5) {
            $(clonedFieldset).insertAfter($(this).parent());
        }
        if (items >= 4) {
            $(".repeatable-section .add_user").hide();
        }
        e.preventDefault();
    });

    /**
     * Trigger the section validation
     */
    setInterval(checkSections, 2000);
});