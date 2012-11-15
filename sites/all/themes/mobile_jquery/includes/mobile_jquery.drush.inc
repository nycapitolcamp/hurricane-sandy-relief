<?php
/**
 * @file
 * Contains functions only needed for drush integration.
 */

/**
 * Implementation of hook_drush_command().
 */
function mobile_jquery_drush_command() {
  $items = array();

  $items['mobile_jquery'] = array(
    'description' => 'Create a theme using mobile_jquery.',
    'arguments' => array(
      'name'         => 'A name for your theme.',
      'machine_name' => '[optional] A machine-readable name for your theme.',
    ),
    'examples' => array(
      'drush mobile_jquery "My theme name"' => 'Create a sub-theme, using the default options.',
      'drush mobile_jquery "My theme name" my_theme' => 'Create a sub-theme with a specific machine name.',
    ),
  );

  return $items;
}

/**
 * Create a mobile_jquery sub-theme using the starter kit.
 */
function drush_mobile_jquery($name = NULL, $machine_name = NULL) {
  
  if (is_null($name)) {
    drush_print(dt('No mobile_jquery sub-theme was created.'));
    return;
  }
  else if (drush_confirm(dt('Do you want to continue creating !name?', array('!name' => $name)))) {
    if (!$machine_name) {
      $machine_name = $name;
    }
    $machine_name = str_replace(' ', '_', strtolower($machine_name));
    $search = array(
      '/[^a-z0-9_]/', // Remove characters not valid in function names.
      '/^[^a-z]+/',   // Functions must begin with an alpha character.
    );
    $machine_name = preg_replace($search, '', $machine_name);
  
    // Determine the path to the new subtheme by finding the path to mobile_jquery.
    $mobile_jquery_path = drush_locate_root() . '/' . drupal_get_path('theme', 'mobile_jquery');
    $subtheme_path = explode('/', $mobile_jquery_path);
    array_pop($subtheme_path);
    $subtheme_path = implode('/', $subtheme_path) . '/' . $machine_name;
    if (is_dir($subtheme_path)) {
      drush_print(dt('The theme folder !name already exists', array('!name' => $name)));
      return;
    }
    // Make a fresh copy of the original starter kit.
    drush_op('mobile_jquery_copy', $mobile_jquery_path . '/STARTER', $subtheme_path);
  
    // Rename the .info file.
    $subtheme_info_file = $subtheme_path . '/' . $machine_name . '.info';
    drush_op('rename', $subtheme_path . '/STARTER.txt', $subtheme_info_file);
  
    // Alter the contents of the .info file based on the command options.
    $alterations = array(
      " = 'STARTER'" => ' = ' . $name,
    );
    drush_op('mobile_jquery_file_str_replace', $subtheme_info_file, array_keys($alterations), $alterations);
  
    // Replace all occurrences of 'STARTER' with the machine name of our sub theme.
    drush_op('mobile_jquery_file_str_replace', $subtheme_info_file, 'STARTER', $machine_name);
    drush_op('mobile_jquery_file_str_replace', $subtheme_path . '/theme-settings.php', 'STARTER', $machine_name);
    drush_op('mobile_jquery_file_str_replace', $subtheme_path . '/template.php', 'STARTER', $machine_name);
  
    // Notify user of the newly created theme.
    drush_print(dt('Starter kit for "!name" created in: !path', array(
      '!name' => $name,
      '!path' => $subtheme_path,
    )));
  }
}

/**
 * Copy a directory recursively.
 */
function mobile_jquery_copy($source_dir, $target_dir, $ignore = '/^(\.(\.)?|CVS|\.svn|\.git|\.DS_Store)$/') {
  if (!is_dir($source_dir)) {
    drush_die(dt('The directory "!directory" was not found.', array('!directory' => $source_dir)));
  }
  $dir = opendir($source_dir);
  @mkdir($target_dir);
  while($file = readdir($dir)) {
    if (!preg_match($ignore, $file)) {
      if (is_dir($source_dir . '/' . $file)) {
        mobile_jquery_copy($source_dir . '/' . $file, $target_dir . '/' . $file, $ignore);
      }
      else {
        copy($source_dir . '/' . $file, $target_dir . '/' . $file);
      }
    }
  }
  closedir($dir);
}

/**
 * Replace strings in a file.
 */
function mobile_jquery_file_str_replace($file_path, $find, $replace) {
  $file_contents = file_get_contents($file_path);
  $file_contents = str_replace($find, $replace, $file_contents);
  file_put_contents($file_path, $file_contents);
}
