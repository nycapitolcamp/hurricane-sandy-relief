<?php

/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 */
?>
<div <?php print drupal_attributes($page['attributes_array']['page']); ?>>
    <div class="header" <?php print drupal_attributes($page['attributes_array']['header']); ?>>
      <?php if ($site_name): ?>
        <h1 class="site-name"><?php print $site_name; ?></h1>
      <?php elseif ($logo): ?>
        <h1>
          <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
        </h1>
      <?php endif; ?>      
      
      <?php if (module_exists('toolbar') && $is_admin): ?>
      <a href="#toolbar" data-role="button" data-rel="dialog" data-transition="pop" data-icon="grid" >Menu</a>
      <?php endif; ?>

      <?php if (!$is_front && !$is_admin): ?>
      <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" data-rel="home" data-icon="home" data-ajax="false"><span><?php print t('Home'); ?></span></a>
      <?php endif; ?>
      
      <?php if ($tabs): ?><?php print render($tabs); ?><?php endif; ?>  
      <?php if ($action_links): ?><div data-role="navbar"><ul class="action-links"><?php print render($action_links); ?></ul></div><?php endif; ?>
    </div> <!-- /#header -->


    <div class="main-content" <?php print drupal_attributes($page['attributes_array']['content']); ?>>

        <div class="content-primary">

          <?php print render($page['header']); ?>
          <?php if ($breadcrumb): ?>
            <div id="breadcrumb"><?php print $breadcrumb; ?></div>
          <?php endif; ?>
          <?php print $messages; ?>  
          <?php if ($page['highlighted']): ?><div class="highlighted"><?php print render($page['highlighted']); ?></div><?php endif; ?>
          <?php print render($title_prefix); ?>
          <?php if ($title): ?><h2 class="title" class="page-title"><?php print $title; ?></h2><?php endif; ?>
          <?php print render($title_suffix); ?>
          <?php print render($page['help']); ?>
          <?php print render($page['content']); ?>
        </div> <!-- /.content-primary -->
        
        <div class="content-secondary">
        
        <?php if ($main_menu || $secondary_menu): ?>
          <div class="navigation">
            <?php print theme('links__system_main_menu', array('links' => $main_menu, 'attributes' => array('id' => 'main-menu', 'class' => array('links', 'inline', 'clearfix')), 'heading' => t('Main Menu'))); ?>
            <?php print theme('links__system_secondary_menu', array('links' => $secondary_menu, 'attributes' => array('id' => 'secondary-menu', 'class' => array('links', 'inline', 'clearfix')), 'heading' => t('Secondary Menu'))); ?>
          </div> <!-- /#navigation -->
        <?php endif; ?>
        
        <?php if ($page['sidebar_first']): ?>
          <div class="sidebar-first" class="column sidebar">
            <?php print render($page['sidebar_first']); ?>
          </div> <!-- /#sidebar-first -->
        <?php endif; ?>

        <?php if ($page['sidebar_second']): ?>
          <div class="sidebar-second" class="column sidebar">
            <?php print render($page['sidebar_second']); ?>
          </div> <!-- /#sidebar-second -->
        <?php endif; ?>
        </div><!-- /.content-secondary -->
              
    </div>

    <div class="footer" <?php print drupal_attributes($page['attributes_array']['footer']); ?>>        
      <?php print render($page['footer']); ?>
    </div> <!-- /#footer -->

</div> <!-- /#page -->
