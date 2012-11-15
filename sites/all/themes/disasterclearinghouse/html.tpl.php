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
	<link rel="stylesheet" href="disasterclearinghouse.css" />
	<link rel="stylesheet" href="http://code.jquery.com/mobile/1.2.0/jquery.mobile.structure-1.2.0.min.css" />
	<script src="http://code.jquery.com/jquery-1.7.2.min.js"></script>
	<script src="http://code.jquery.com/mobile/1.2.0/jquery.mobile-1.2.0.min.js"></script>
	<script>
	// Load the data for a specific category, based on
	// the URL passed in. Generate markup for the items in the
	// category, inject it into an embedded page, and then make
	// that page the current active page.
	function showCategory( urlObj, options )
	{
		var categoryName = urlObj.hash.replace( /.*category=/, "" ),

			// Get the object that represents the category we
			// are interested in. Note, that at this point we could
			// instead fire off an ajax request to fetch the data, but
			// for the purposes of this sample, it's already in memory.
			category = categoryData[ categoryName ],

			// The pages we use to display our content are already in
			// the DOM. The id of the page we are going to write our
			// content into is specified in the hash before the '?'.
			pageSelector = urlObj.hash.replace( /\?.*$/, "" );

		if ( category ) {
			// Get the page we are going to dump our content into.
			var $page = $( pageSelector ),

				// Get the header for the page.
				$header = $page.children( ":jqmData(role=header)" ),

				// Get the content area element for the page.
				$content = $page.children( ":jqmData(role=content)" ),

				// The markup we are going to inject into the content
				// area of the page.
				markup = "<p>" + category.description + "</p><ul data-role='listview' data-inset='true'>",

				// The array of items for this category.
				cItems = category.items,

				// The number of items in the category.
				numItems = cItems.length;

			// Generate a list item for each item in the category
			// and add it to our markup.
			for ( var i = 0; i < numItems; i++ ) {
				markup += "<li>" + cItems[i].name + "</li>";
			}
			markup += "</ul>";

			// Find the h1 element in our header and inject the name of
			// the category into it.
			$header.find( "h1" ).html( category.name );

			// Inject the category items markup into the content element.
			$content.html( markup );

			// Pages are lazily enhanced. We call page() on the page
			// element to make sure it is always enhanced before we
			// attempt to enhance the listview markup we just injected.
			// Subsequent calls to page() are ignored since a page/widget
			// can only be enhanced once.
			$page.page();

			// Enhance the listview we just injected.
			$content.find( ":jqmData(role=listview)" ).listview();

			// We don't want the data-url of the page we just modified
			// to be the url that shows up in the browser's location field,
			// so set the dataUrl option to the URL for the category
			// we just loaded.
			options.dataUrl = urlObj.href;

			// Now call changePage() and tell it to switch to
			// the page we just modified.
			$.mobile.changePage( $page, options );
		}
	}


	// Listen for any attempts to call changePage().
	$(document).bind( "pagebeforechange", function( e, data ) {
		// We only want to handle changePage() calls where the caller is
		// asking us to load a page by URL.
		if ( typeof data.toPage === "string" ) {
			// We are being asked to load a page by URL, but we only
			// want to handle URLs that request the data for a specific
			// category.
			var u = $.mobile.path.parseUrl( data.toPage ),
				re = /^#category-item/;
			if ( u.hash.search(re) !== -1 ) {
				// We're being asked to display the items for a specific category.
				// Call our internal method that builds the content for the category
				// on the fly based on our in-memory category data structure.
				showCategory( u, data.options );

				// Make sure to tell changePage() we've handled this call so it doesn't
				// have to do anything.
				e.preventDefault();
			}
		}
	});
</script>
</head>
<body class="<?php print $classes; ?>" <?php print $attributes;?>>
  <div id="skip-link">
    <a href="#main-content" class="element-invisible element-focusable"><?php print t('Skip to main content'); ?></a>
  </div>

  <?// php print $page_top; ?>
  <!-- Page.tpl.php -->
  
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