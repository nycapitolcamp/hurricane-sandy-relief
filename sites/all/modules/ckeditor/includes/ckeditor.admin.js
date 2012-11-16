/*
Copyright (c) 2003-2012, CKSource - Frederico Knabben. All rights reserved.
For licensing, see LICENSE.html or http://ckeditor.com/license
*/
(function ($) {
    CKEDITOR.on( 'dialogDefinition', function( ev )
    {
        var dialogName = ev.data.name;
        var dialogDefinition = ev.data.definition;

        if ( dialogName == 'uicolor' )
        {
            // Get a reference to the configBox and hide it (cannot be removed).
            var configBox = dialogDefinition.getContents( 'tab1' ).get( 'configBox' );
            configBox.style = 'display:none';
        }
    });

    $(document).ready(function() {
        if (typeof(CKEDITOR) == "undefined")
            return;

        $('#edit-uicolor-textarea').show();

        Drupal.ckeditorUiColorOnChange = function() {
            var color = CKEDITOR.instances["edit-uicolor-textarea"].getUiColor();
            $("#edit-uicolor").val("custom");
            if (typeof(color) != "undefined") {
                if (color == "default"){
                    $("#edit-uicolor").val("default");
                }
                $('input[name$="uicolor_user"]').val(color);
            }
        };

        if ( $("#edit-skin").val() == "kama" ){
            $("#edit-uicolor").removeAttr('disabled');
            $("#edit-uicolor").parent().removeClass('form-disabled');
            CKEDITOR.replace("edit-uicolor-textarea",
            {
                extraPlugins : 'uicolor',
                height: 60,
                uiColor: $('input[name$="uicolor_user"]').val() || '#D3D3D3',
                width: 400,
                toolbar : [[ 'Bold', 'Italic', '-', 'NumberedList', 'BulletedList'],[ 'UIColor' ]],
                skin: $("#edit-skin").val(),
                on:
                {
                    focus : Drupal.ckeditorUiColorOnChange,
                    blur : Drupal.ckeditorUiColorOnChange
                }
            });
        }
        else {
            $("#edit-uicolor").attr('disabled', 'disabled');
            $("#edit-uicolor").parent().addClass('form-disabled');
            CKEDITOR.replace("edit-uicolor-textarea",
            {
                height: 60,
                uiColor: $('input[name$="uicolor_user"]').val() || '#D3D3D3',
                width: 400,
                toolbar : [[ 'Bold', 'Italic', '-', 'NumberedList', 'BulletedList']],
                skin: $("#edit-skin").val(),
                on:
                {
                    focus : Drupal.ckeditorUiColorOnChange,
                    blur : Drupal.ckeditorUiColorOnChange
                }
            });
        }

        $("#edit-skin").bind("change", function() {
            CKEDITOR.instances["edit-uicolor-textarea"].destroy();
            if ( $("#edit-skin").val() == "kama" ){
                $("#edit-uicolor").removeAttr('disabled');
                $("#edit-uicolor").parent().removeClass('form-disabled');
                CKEDITOR.replace("edit-uicolor-textarea",
                {
                    extraPlugins : 'uicolor',
                    height: 60,
                    uiColor: $('input[name$="uicolor_user"]').val() || '#D3D3D3',
                    width: 400,
                    toolbar: [[ 'Bold', 'Italic', '-', 'NumberedList', 'BulletedList'],[ 'UIColor' ]],
                    skin: $("#edit-skin").val(),
                    on:
                    {
                        focus : Drupal.ckeditorUiColorOnChange,
                        blur : Drupal.ckeditorUiColorOnChange
                    }
                });
            }
            else {
                $("#edit-uicolor").attr('disabled', 'disabled');
                $("#edit-uicolor").parent().addClass('form-disabled');
                CKEDITOR.replace("edit-uicolor-textarea",
                {
                    height: 60,
                    uiColor: $('input[name$="uicolor_user"]').val() || '#D3D3D3',
                    width: 400,
                    toolbar: [[ 'Bold', 'Italic', '-', 'NumberedList', 'BulletedList']],
                    skin: $("#edit-skin").val(),
                    on:
                    {
                        focus : Drupal.ckeditorUiColorOnChange,
                        blur : Drupal.ckeditorUiColorOnChange
                    }
                });
            }
        });

        $("#edit-uicolor").bind("change", function() {
            if (typeof(Drupal.settings.ckeditor_uicolor) != "undefined") {
                CKEDITOR.instances["edit-uicolor-textarea"].setUiColor(Drupal.settings.ckeditor_uicolor[$(this).val()]);
            }
            if ($(this).val() != "custom") {
                $('input[name$="uicolor_user"]').val("");
            }
            else {
                var color = CKEDITOR.instances["edit-uicolor-textarea"].getUiColor();
                if (typeof(color) != "undefined") {
                    $('input[name$="uicolor_user"]').val(color);
                }
            }
        });

        $("#input-formats :checkbox").change(function() {
            $('#security-filters .filter-warning').hide();
            $('#security-filters div.filter-text-formats[filter]').html('');
            $('#security-filters ul.text-formats-config').html('');
            $('#input-formats :checked').each(function() {
                var format_name = $(this).val();
                var format_label = $('label[for="' + $(this).attr('id') + '"]').html();

                if (typeof(Drupal.settings.text_formats_config_links[format_name]) != 'undefined') {
                    var text = "<li>" + format_label + " - <a href=\"" + Drupal.settings.text_formats_config_links[format_name].config_url + "\">configure</a></li>";
                    var dataSel = $('#security-filters ul.text-formats-config');
                    var html = dataSel.html();
                    if (html == null || html.length == 0) {
                        dataSel.html(text);
                    }
                    else {
                        html += text;
                        dataSel.html(html);
                    }
                }

                $('#security-filters div.filter-text-formats[filter]').each(function() {
                    var filter_name = $(this).attr('filter');
                    var dataSel = $(this);
                    var html = dataSel.html();
                    var status = "enabled";
                    if (typeof Drupal.settings.text_format_filters[format_name][filter_name] == 'undefined') {
                        status = "disabled";
                    }
                    var text = "<span class=\"filter-text-format-status " + status + "\">" + format_label + ': </span><br/>';

                    if (html == null || html.length == 0) {
                        dataSel.html(text);
                    }
                    else {
                        html += text;
                        dataSel.html(html);
                    }
                });
            });
        });
        $("#input-formats :checkbox:eq(0)").trigger('change');

        $(".cke_load_toolbar").click(function() {
            var buttons = eval('Drupal.settings.'+$(this).attr("id"));
            var text = "[\n";
            for(i in buttons) {
                if (typeof buttons[i] == 'string'){
                    text = text + "    '/',\n";
                }
                else {
                    text = text + "    [";
                    max = buttons[i].length - 1;
                    rows = buttons.length - 1;
                    for (j in buttons[i]) {
                        if (j < max){
                            text = text + "'" + buttons[i][j] + "',";
                        } else {
                            text = text + "'" + buttons[i][j] + "'";
                        }
                    }
                    if (i < rows){
                        text = text + "],\n";
                    } else {
                        text = text + "]\n";
                    }
                }
            }

            text = text + "]";
            text = text.replace(/\['\/'\]/g,"'/'");
            $("#edit-toolbar").attr('value',text);
            if (Drupal.settings.ckeditor_toolbar_wizard == 't'){
                Drupal.ckeditorToolbarReload();
            }
            return false;
        });

        if (Drupal.settings.ckeditor_toolbar_wizard == 'f'){
            $("form#ckeditor-admin-profile-form textarea#edit-toolbar, form#ckeditor-admin-profile-form #edit-toolbar + .grippie").show();
        }
    });
})(jQuery);