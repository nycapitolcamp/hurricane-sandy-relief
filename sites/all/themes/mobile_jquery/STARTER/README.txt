BUILD A THEME WITH MOBILE_JQUERY
----------------------

The base mobile_jquery theme is designed to be easily extended by its sub-themes. You
shouldn't modify any of the CSS or PHP files in the mobile_jquery folder; but instead you
should create a sub-theme of mobile_jquery which is located in a folder outside of the
root mobile_jquery folder.

 1. Setup your new sub-theme.

    Copy the STARTER folder out of the mobile_jquery folder and rename it to be your
    new sub-theme. Do not move the STARTER folder as it will complicate upgrades

    EXAMPLE: copy the sites/all/themes/mobile_jquery/STARTER folder and rename it
    as sites/all/themes/foo.

 2. Prepare your sub-theme.

    In your new sub-theme folder, rename the STARTER.txt file to include
    the name of your new sub-theme and change the ".txt" extension to ".info".
    Then edit the .info file by editing the name and description field.

    For example, rename the foo/STARTER.txt file to foo/foo.info. Edit the
    foo.info file and change "name = STARTER" to "name = Foo"

 3. Edit your sub-theme to use the proper function names.

    Edit the template.php and theme-settings.php files in your sub-theme's
    folder; replace ALL occurrences of "STARTER" with the name of your
    sub-theme.

    For example, edit foo/template.php and foo/theme-settings.php and replace
    every occurrence of "STARTER" with "foo".

 4. Set your website's default theme.

    Log in as an administrator on your Drupal site, go to the Appearance page at
    admin/appearance and click the "Enable and set default" link next to your
    new sub-theme.
