<?php

/**
 * @file
 * Default theme implementation to display the basic html structure of a single
 * Drupal page.
 *
 * Variables:
 * - $css: An array of CSS files for the current page.
 * - $language: (object) The language the site is being displayed in.
 *   $language->language contains its textual representation.
 *   $language->dir contains the language direction. It will either be 'ltr' or 'rtl'.
 * - $rdf_namespaces: All the RDF namespace prefixes used in the HTML document.
 * - $grddl_profile: A GRDDL profile allowing agents to extract the RDF data.
 * - $head_title: A modified version of the page title, for use in the TITLE
 *   tag.
 * - $head_title_array: (array) An associative array containing the string parts
 *   that were used to generate the $head_title variable, already prepared to be
 *   output as TITLE tag. The key/value pairs may contain one or more of the
 *   following, depending on conditions:
 *   - title: The title of the current page, if any.
 *   - name: The name of the site.
 *   - slogan: The slogan of the site, if any, and if there is no title.
 * - $head: Markup for the HEAD section (including meta tags, keyword tags, and
 *   so on).
 * - $styles: Style tags necessary to import all CSS files for the page.
 * - $scripts: Script tags necessary to load the JavaScript files and settings
 *   for the page.
 * - $page_top: Initial markup from any modules that have altered the
 *   page. This variable should always be output first, before all other dynamic
 *   content.
 * - $page: The rendered page content.
 * - $page_bottom: Final closing markup from any modules that have altered the
 *   page. This variable should always be output last, after all other dynamic
 *   content.
 * - $classes String of classes that can be used to style contextually through
 *   CSS.
 *
 * @see template_preprocess()
 * @see template_preprocess_html()
 * @see template_process()
 */
?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML+RDFa 1.0//EN"
  "http://www.w3.org/MarkUp/DTD/xhtml-rdfa-1.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language; ?>" version="XHTML+RDFa 1.0" dir="<?php print $language->dir; ?>"<?php print $rdf_namespaces; ?>>
<head profile="<?php print $grddl_profile; ?>">
	<?php print $head; ?>
	<title><?php print $head_title; ?></title>
	<?php print $styles; ?>
	<?php print $scripts; ?>
	<link rel="stylesheet" href="/sites/all/themes/disasterclearinghouse/styles/disasterclearinghouse.css" />
	<!-- <link rel="stylesheet" href="http://code.jquery.com/mobile/1.2.0/jquery.mobile.structure-1.2.0.min.css" /> -->
	<!-- <script src="http://code.jquery.com/jquery-1.7.2.min.js"></script> -->
	<!-- <script src="http://code.jquery.com/mobile/1.2.0/jquery.mobile-1.2.0.min.js"></script> -->
</head>
<!--
	Basic idea is, make menus, display nodes menu's are top level data.
	-->
<body class="<?php print $classes; ?>" <?php print $attributes;?>>
	<div id="skip-link">
		<a href="#main-content" class="element-invisible element-focusable"><?php print t('Skip to main content'); ?></a>
	</div>
	<?// php print $page_top; ?>
	<div data-role="page" id="page1">
		<div data-role="header">
			<h1><?php print variable_get('site_name'); ?></h1>
		</div>
		<div data-role="content">
			<div data-role="navbar" data-iconpos="top">
		        <ul>
		            <li>
		                <a href="#page1" data-theme="" data-icon="">
		                    News
		                </a>
		            </li>
		            <li>
		                <a href="#page1" data-theme="" data-icon="">
		                    Shelters
		                </a>
		            </li>
		            <li>
		                <a href="#page1" data-theme="" data-icon="">
		                    Help
		                </a>
		            </li>
		            <li>
		                <a href="#page1" data-theme="" data-icon="">
		                    MTA
		                </a>
		            </li>
		        </ul>
		    </div>
		    <ul id="HowYouCanHelp" data-role="listview" data-divider-theme="b" data-inset="true">
		        <li data-role="list-divider" role="heading">
		            How you can help
		        </li>
		        <li data-theme="c">
		            <a href="#page1" data-tranntion="slide">
		                Volunteer
		            </a>
		        </li>
		        <li data-theme="c">
		            <a href="#page1" data-transition="slide">
		                Donate to Red Cross
		            </a>
		        </li>
		        <li data-theme="c">
		            <a href="#page1" data-transition="slide">
		                Corporate Donations
		            </a>
		        </li>
		        <li data-theme="c">
		            <a href="#page1" data-transition="slide">
		                Donate Blood
		            </a>
		        </li>
		    </ul>
		</div>
	</div>	
	<? //php print $page; ?>
	<?//php print $page_bottom; ?>
</body>
</html>