<?php
/**
 * @file
 * Contains theme override functions and preprocess functions for the mobile_jquery STARTER theme.
 *
 */
 
/*
 * Preprocess Functions
 *
 */
/**
 * Preprocess variables for html.tpl.php
 *
 * @see system_elements()
 * @see html.tpl.php
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_html(&$vars) {
}
// */

/**
 * Preprocess variables for page.tpl.php
 *
 * Most themes utilize their own copy of page.tpl.php. The default is located
 * inside "modules/system/page.tpl.php". Look in there for the full list of
 * variables.
 *
 * Uses the arg() function to generate a series of page template suggestions
 * based on the current path.
 *
 * Any changes to variables in this preprocessor should also be changed inside
 * template_preprocess_maintenance_page() to keep all of them consistent.
 *
 * @see drupal_render_page()
 * @see template_process_page()
 * @see page.tpl.php
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_page(&$vars) {
}
// */


/**
 * Process variables for node.tpl.php
 *
 * Most themes utilize their own copy of node.tpl.php. The default is located
 * inside "modules/node/node.tpl.php". Look in there for the full list of
 * variables.
 *
 * The $vars array contains the following arguments:
 * - $node
 * - $view_mode
 * - $page
 *
 * @see node.tpl.php
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_node(&$vars) {
}
// */

/**
 * The variables array generated here is a mirror of template_preprocess_page().
 * This preprocessor will run its course when theme_maintenance_page() is
 * invoked.
 *
 * An alternate template file of "maintenance-page--offline.tpl.php" can be
 * used when the database is offline to hide errors and completely replace the
 * content.
 *
 * The $vars array contains the following arguments:
 * - $content
 *
 * @see maintenance-page.tpl.php
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_maintenance_page(&$vars) {
}
// */

/**
 * Process variables for block.tpl.php
 *
 * Prepare the values passed to the theme_block function to be passed
 * into a pluggable template engine. Uses block properties to generate a
 * series of template file suggestions. If none are found, the default
 * block.tpl.php is used.
 *
 * Most themes utilize their own copy of block.tpl.php. The default is located
 * inside "modules/block/block.tpl.php". Look in there for the full list of
 * variables.
 *
 * The $variables array contains the following arguments:
 * - $block
 *
 * @see block.tpl.php
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_block(&$vars) {
}
// */


/**
 * Processes variables for block-admin-display-form.tpl.php.
 *
 * The $vars array contains the following arguments:
 * - $form
 *
 * @see block-admin-display.tpl.php
 * @see theme_block_admin_display()
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_block_admin_display_form(&$vars) {
}
// */

/**
 * Preprocess variables for region.tpl.php
 *
 * Prepare the values passed to the theme_region function to be passed into a
 * pluggable template engine. Uses the region name to generate a template file
 * suggestions. If none are found, the default region.tpl.php is used.
 *
 * @see drupal_region_class()
 * @see region.tpl.php
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_region(&$vars) {

}

/**
 * Preprocesses variables for theme_username().
 *
 * Modules that make any changes to variables like 'name' or 'extra' must insure
 * that the final string is safe to include directly in the output by using
 * check_plain() or filter_xss().
 *
 * @see template_process_username()
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_username(&$vars) {

}


/**
 * Process variables for aggregator-wrapper.tpl.php.
 *
 * @see aggregator-wrapper.tpl.php
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_aggregator_wrapper(&$vars) {

}

/**
 * Process variables for aggregator-item.tpl.php.
 *
 * @see aggregator-item.tpl.php
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_aggregator_item(&$vars) {

}

/**
 * Process variables for aggregator-summary-item.tpl.php.
 *
 * @see aggregator-summary-item.tpl.php
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_aggregator_summary_item(&$vars) {
 
}

/**
 * Process variables for aggregator-feed-source.tpl.php.
 *
 * @see aggregator-feed-source.tpl.php
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_aggregator_feed_source(&$vars) {

}


/**
 * Process variables for book-all-books-block.tpl.php.
 *
 * The $vars array contains the following arguments:
 * - $book_menus
 *
 * All non-renderable elements are removed so that the template has full
 * access to the structured data but can also simply iterate over all
 * elements and render them (as in the default template).
 *
 * @see book-navigation.tpl.php
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_book_all_books_block(&$vars) {

}

/**
 * Process variables for book-navigation.tpl.php.
 *
 * The $vars array contains the following arguments:
 * - $book_link
 *
 * @see book-navigation.tpl.php
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_book_navigation(&$vars) {

}


/**
 * Process variables for comment.tpl.php.
 *
 * @see comment.tpl.php
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_comment(&$vars) {
}
// */

/**
 * Process variables for comment-wrapper.tpl.php.
 *
 * @see comment-wrapper.tpl.php
 * @see theme_comment_wrapper()
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_comment_wrapper(&$vars) {
   
}


/**
 * Preprocesses variables for block-admin-display-form.tpl.php.
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_dashboard_admin_display_form(&$vars) {
}
// */


/**
 * Theme preprocess function for theme_field() and field.tpl.php.
 *
 * @see theme_field()
 * @see field.tpl.php
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_field(&$vars, $hook) {
}
// */

/**
 * Process variables for forums.tpl.php
 *
 * The $vars array contains the following arguments:
 * - $forums
 * - $topics
 * - $parents
 * - $tid
 * - $sortby
 * - $forum_per_page
 *
 * @see forums.tpl.php
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_forums(&$vars) {
}
// */

/**
 * Process variables to format a forum listing.
 *
 * $vars contains the following information:
 * - $forums
 * - $parents
 * - $tid
 *
 * @see forum-list.tpl.php
 * @see theme_forum_list()
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_forum_list(&$vars) {
}
// */

/**
 * Preprocess variables to format the topic listing.
 *
 * $vars contains the following data:
 * - $tid
 * - $topics
 * - $sortby
 * - $forum_per_page
 *
 * @see forum-topic-list.tpl.php
 * @see theme_forum_topic_list()
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_forum_topic_list(&$vars) {
}
// */

/**
 * Process variables to format the icon for each individual topic.
 *
 * $vars contains the following data:
 * - $new_posts
 * - $num_posts = 0
 * - $comment_mode = 0
 * - $sticky = 0
 * - $first_new
 *
 * @see forum-icon.tpl.php
 * @see theme_forum_icon()
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_forum_icon(&$vars) {
}
// */

/**
 * Process variables to format submission info for display in the forum list and topic list.
 *
 * $vars will contain: $topic
 *
 * @see forum-submitted.tpl.php
 * @see theme_forum_submitted()
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_forum_submitted(&$vars) {
}
// */

/**
 * Preprocesses the rendered tree for theme_menu_tree().
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_menu_tree(&$vars) {
}
// */


/**
 * Preprocesses template variables for overlay.tpl.php
 *
 * @see overlay.tpl.php
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_overlay(&$vars) {
}
// */

/**
 * Themes the voting form for a poll.
 *
 * Inputs: $form
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_poll_vote(&$vars) {
}
// */

/**
 * Preprocess the poll_results theme hook.
 *
 * Inputs: $raw_title, $results, $votes, $raw_links, $block, $nid, $vote. The
 * $raw_* inputs to this are naturally unsafe; often safe versions are
 * made to simply overwrite the raw version, but in this case it seems likely
 * that the title and the links may be overridden by the theme layer, so they
 * are left in with a different name for that purpose.
 *
 * @see poll-results.tpl.php
 * @see poll-results--block.tpl.php
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_poll_results(&$vars) {
}
// */

/**
 * Preprocess the poll_bar theme hook.
 *
 * Inputs: $title, $votes, $total_votes, $voted, $block
 *
 * @see poll-bar.tpl.php
 * @see poll-bar--block.tpl.php
 * @see theme_poll_bar()
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_poll_bar(&$vars) {
}
// */

/**
 * Process variables for search-results.tpl.php.
 *
 * The $vars array contains the following arguments:
 * - $results: Search results array.
 * - $module: Module the search results came from (module implementing
 *   hook_search_info()).
 *
 * @see search-results.tpl.php
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_search_results(&$vars) {
}
// */

/**
 * Process variables for search-result.tpl.php.
 *
 * The $vars array contains the following arguments:
 * - $result
 * - $module
 *
 * @see search-result.tpl.php
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_search_result(&$vars) {
}
// */

/**
 * Process variables for taxonomy-term.tpl.php.
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_taxonomy_term(&$vars) {
}
// */


/**
 * Process variables for user-picture.tpl.php.
 *
 * The $vars array contains the following arguments:
 * - $account: A user, node or comment object with 'name', 'uid' and 'picture'
 *   fields.
 *
 * @see user-picture.tpl.php
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_user_picture(&$vars) {
}
// */

/**
 * Process variables for user-profile.tpl.php.
 *
 * The $vars array contains the following arguments:
 * - $account
 *
 * @see user-profile.tpl.php
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_user_profile(&$vars) {
}
// */

/**
 * Process variables for user-profile-item.tpl.php.
 *
 * The $vars array contains the following arguments:
 * - $element
 *
 * @see user-profile-item.tpl.php
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_user_profile_item(&$vars) {
}
// */

/**
 * Process variables for user-profile-category.tpl.php.
 *
 * The $vars array contains the following arguments:
 * - $element
 *
 * @see user-profile-category.tpl.php
 */
/* -- Delete this line if you want to use this function
function STARTER_preprocess_user_profile_category(&$vars) {
}
// */


