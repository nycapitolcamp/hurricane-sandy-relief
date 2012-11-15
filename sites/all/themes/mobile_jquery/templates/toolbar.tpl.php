<?php

/**
 * @file
 * Default template for admin toolbar.
 *
 * Available variables:
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default value has the following:
 *   - toolbar: The current template type, i.e., "theming hook".
 * - $toolbar['toolbar_user']: User account / logout links.
 * - $toolbar['toolbar_menu']: Top level management menu links.
 * - $toolbar['toolbar_drawer']: A place for extended toolbar content.
 *
 * Other variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 *
 * @see template_preprocess()
 * @see template_preprocess_toolbar()
 */
?>
<div data-role="page" data-rel="dialog" data-url="toolbar">
  <div data-role="header">
    <h1 role="heading">Toolbar</h1>
  </div>
  <div data-role="content">
      <div class="clearfix">
        <?php print render($toolbar['toolbar_home']); ?>
      </div>
      <h3>User</h3>
      <?php print render($toolbar['toolbar_user']); ?>
      <h3>Menu</h3>
      <?php print render($toolbar['toolbar_menu']); ?>
      <h3>Shortcuts</h3>
      <?php print render($toolbar['toolbar_drawer']); ?>
  </div>
</div>
