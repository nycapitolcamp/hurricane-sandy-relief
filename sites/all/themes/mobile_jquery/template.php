<?php
/**
 * @file
 * Contains theme override functions and preprocess functions for the mobile_jquery theme.
 *
 * IMPORTANT WARNING: DO NOT MODIFY THIS FILE.
 *
 * The base mobile_jquery theme is designed to be easily extended by its sub-themes.
 * You shouldn't modify this or any of the CSS or PHP files in the root mobile_jquery folder.
 */
 
include_once(drupal_get_path('theme', 'mobile_jquery') . '/includes/mobile_jquery.inc');
include_once(drupal_get_path('theme', 'mobile_jquery') . '/includes/modules/theme.inc');
include_once(drupal_get_path('theme', 'mobile_jquery') . '/includes/modules/pager.inc');
include_once(drupal_get_path('theme', 'mobile_jquery') . '/includes/modules/form.inc');

$modules = module_list();

foreach ($modules as $module) {
  if (is_file(drupal_get_path('theme', 'mobile_jquery') . '/includes/modules/' . str_replace('_', '-', $module) . '.inc')) {
    include_once(drupal_get_path('theme', 'mobile_jquery') . '/includes/modules/' . str_replace('_', '-', $module) . '.inc');
  }    
} 

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
function mobile_jquery_preprocess_html(&$vars) {

  $vars['viewport'] = implode(',', mobile_jquery_get_viewport());

  if (module_exists('jquerymobile')) {
    jquerymobile_load_files();
  }
  else {
   $css_options = array(
      'type' => 'file', 
      'group' => CSS_THEME, 
      'every_page' => TRUE, 
      'media' => 'all', 
      'preprocess' => FALSE, 
    );
    $js_options = array(
      'type' => 'file', 
      'scope' => 'header', 
      'group' => JS_THEME, 
      'every_page' => TRUE, 
      'preprocess' => TRUE, 
      'cache' => TRUE, 
      'defer' => FALSE,
    );
   drupal_add_css('http://code.jquery.com/mobile/1.0.1/jquery.mobile.structure-1.0.1.min.css', array_merge($css_options, array('weight' => 100)));
   drupal_add_css('http://code.jquery.com/mobile/1.0.1/jquery.mobile-1.0.1.min.css', array_merge($css_options, array('weight' => 100)));
   drupal_add_js('http://code.jquery.com/jquery-1.6.4.min.js', array_merge($js_options, array('weight' => 100)));
   drupal_add_js(drupal_get_path('theme', 'mobile_jquery') . '/scripts/mobile_jquery.js', array_merge($js_options, array('weight' => 101)));
   drupal_add_js('http://code.jquery.com/mobile/1.0.1/jquery.mobile-1.0.1.min.js', array_merge($js_options, array('weight' => 101)));
   } 
  $vars['styles'] = drupal_get_css();

   if (isset($vars['page']['page_top']['toolbar'])) {
     $vars['page']['page_bottom']['toolbar'] = $vars['page']['page_top']['toolbar'];
     unset($vars['page']['page_top']['toolbar']);
   }   
}

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
function mobile_jquery_preprocess_page(&$vars) {
  $vars['page']['attributes_array'] = array();
  $use_global = mobile_jquery_theme_get_setting('use_global');

  $classes = array('page');
  
  if ($vars['is_front']) {
    $classes[] = 'type-home';
  } 
  else {
    $classes[] = 'type-interior';
  }

  $vars['page']['attributes_array']['page'] = array(
    'data-theme' => $use_global ? mobile_jquery_theme_get_setting('global_theme') : '',
    'data-role' => 'page',
    'class' => implode(' ', $classes),
  );
  $vars['page']['attributes_array']['header'] = array(
    'data-theme' => $use_global ? mobile_jquery_theme_get_setting('global_theme') : mobile_jquery_theme_get_setting('header_data_theme'),
    'data-position' => mobile_jquery_theme_get_setting('global_header_data_position') ? mobile_jquery_theme_get_setting('global_header_data_position') : mobile_jquery_theme_get_setting('header_data_position'),
    'data-role' => 'header',
  );
  $vars['page']['attributes_array']['content'] = array(
    'data-theme' => $use_global ? mobile_jquery_theme_get_setting('global_theme') : mobile_jquery_theme_get_setting('content_data_theme'),
    'data-role' => 'content',
  );
  $vars['page']['attributes_array']['footer'] = array(
    'data-theme' => $use_global ? mobile_jquery_theme_get_setting('global_theme') : mobile_jquery_theme_get_setting('footer_data_theme'),
    'data-position' => mobile_jquery_theme_get_setting('global_footer_data_position') ? mobile_jquery_theme_get_setting('global_footer_data_position') : mobile_jquery_theme_get_setting('footer_data_position'),
    'data-role' => 'footer',
  );
  if (!isset($vars['messages'])) {
    $vars['messages'] = $vars['show_messages'] ? theme('status_messages') : '';
  }
}


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
function mobile_jquery_preprocess_node(&$vars) {
  $vars['is_list'] = FALSE;
  if (module_exists('jquerymobile')) {
    if (_jquerymobile_is_mobile_theme('mobile_jquery') && _jquerymobile_get_setting('mobile_jquery', 'front')) {
      $vars['is_list'] = TRUE;
    }
  }
}

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
function mobile_jquery_preprocess_maintenance_page(&$vars) {

}

function mobile_jquery_preprocess_block(&$vars) {

}


/**
 * Processes variables for block-admin-display-form.tpl.php.
 *
 * The $vars array contains the following arguments:
 * - $form
 *
 * @see block-admin-display.tpl.php
 * @see theme_block_admin_display()
 */
function mobile_jquery_preprocess_block_admin_display_form(&$vars) {
  if (isset($vars['block_listing'])) {
    foreach (element_children($vars['form']['blocks']) as $i) {
      $block = &$vars['form']['blocks'][$i];
      $region = (isset($block['region']['#default_value']) ? $block['region']['#default_value'] : BLOCK_REGION_NONE);
      if (isset($block['configure'])) {
        $block['configure']['#options']['attributes']['data-role'] = 'button';
        $block['configure']['#options']['attributes']['data-icon'] = 'configure';
        $vars['block_listing'][$region][$i]->configure_link = l($block['configure']['#title'], $block['configure']['#href'], $block['configure']['#options']);
      }
      if (isset($block['delete']) && !empty($block['delete'])) {
        $block['delete']['#options']['attributes']['data-role'] = 'button';
        $block['delete']['#options']['attributes']['data-icon'] = 'delete';
        $vars['block_listing'][$region][$i]->delete_link = l($block['delete']['#title'], $block['delete']['#href'], $block['delete']['#options']);
      }
    }
  }
}

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
function mobile_jquery_preprocess_region(&$vars) {

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
function mobile_jquery_preprocess_username(&$vars) {

}


/**
 * Process variables for aggregator-wrapper.tpl.php.
 *
 * @see aggregator-wrapper.tpl.php
 */
function mobile_jquery_preprocess_aggregator_wrapper(&$vars) {

}

/**
 * Process variables for aggregator-item.tpl.php.
 *
 * @see aggregator-item.tpl.php
 */
function mobile_jquery_preprocess_aggregator_item(&$vars) {

}

/**
 * Process variables for aggregator-summary-item.tpl.php.
 *
 * @see aggregator-summary-item.tpl.php
 */
function mobile_jquery_preprocess_aggregator_summary_item(&$vars) {
 
}

/**
 * Process variables for aggregator-feed-source.tpl.php.
 *
 * @see aggregator-feed-source.tpl.php
 */
function mobile_jquery_preprocess_aggregator_feed_source(&$vars) {

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
function mobile_jquery_preprocess_book_all_books_block(&$vars) {

}

/**
 * Process variables for book-navigation.tpl.php.
 *
 * The $vars array contains the following arguments:
 * - $book_link
 *
 * @see book-navigation.tpl.php
 */
function mobile_jquery_preprocess_book_navigation(&$vars) {

}


/**
 * Process variables for comment.tpl.php.
 *
 * @see comment.tpl.php
 */
function mobile_jquery_preprocess_comment(&$vars) {
  $comment = $vars['elements']['#comment'];
  $vars['title'] = $comment->subject;
}

/**
 * Process variables for comment-wrapper.tpl.php.
 *
 * @see comment-wrapper.tpl.php
 * @see theme_comment_wrapper()
 */
function mobile_jquery_preprocess_comment_wrapper(&$vars) {
   
}


/**
 * Preprocesses variables for block-admin-display-form.tpl.php.
 */
function mobile_jquery_preprocess_dashboard_admin_display_form(&$vars) {
  mobile_jquery_preprocess_block_admin_display_form($vars);
  if (isset($vars['block_listing'])) {
    foreach (element_children($vars['form']['blocks']) as $i) {
      $block = &$vars['form']['blocks'][$i];
      $region = (isset($block['region']['#default_value']) ? $block['region']['#default_value'] : BLOCK_REGION_NONE);
      if (isset($block['configure'])) {
        $block['configure']['#options']['attributes']['data-role'] = 'button';
        $block['configure']['#options']['attributes']['data-icon'] = 'configure';
        $vars['block_listing'][$region][$i]->configure_link = l($block['configure']['#title'], $block['configure']['#href'], $block['configure']['#options']);
      }
      if (isset($block['delete']) && !empty($block['delete'])) {
        $block['delete']['#options']['attributes']['data-role'] = 'button';
        $block['delete']['#options']['attributes']['data-icon'] = 'delete';
        $vars['block_listing'][$region][$i]->delete_link = l($block['delete']['#title'], $block['delete']['#href'], $block['delete']['#options']);
      }
    }
  }
}


/**
 * Theme preprocess function for theme_field() and field.tpl.php.
 *
 * @see theme_field()
 * @see field.tpl.php
 */
function mobile_jquery_preprocess_field(&$vars, $hook) {

}

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
function mobile_jquery_preprocess_forums(&$vars) {
 global $user;

  $vid = variable_get('forum_nav_vocabulary', 0);
  $vocabulary = taxonomy_vocabulary_load($vid);
  $title = !empty($vocabulary->name) ? $vocabulary->name : '';
  $options = array(
    'attributes' => array(
      'data-role' => 'button',
    ),
  );
  // Breadcrumb navigation:
  $breadcrumb[] = l(t('Home'), NULL, $options);
  if ($vars['tid']) {
    $breadcrumb[] = l($vocabulary->name, 'forum', $options);
  }
  if ($vars['parents']) {
    $vars['parents'] = array_reverse($vars['parents']);
    foreach ($vars['parents'] as $p) {
      if ($p->tid == $vars['tid']) {
        $title = $p->name;
      }
      else {
        $breadcrumb[] = l($p->name, 'forum/' . $p->tid, $options);
      }
    }
  }
  drupal_set_breadcrumb($breadcrumb);

}

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
function mobile_jquery_preprocess_forum_list(&$vars) {

}

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
function mobile_jquery_preprocess_forum_topic_list(&$vars) {

}

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
function mobile_jquery_preprocess_forum_icon(&$vars) {

}

/**
 * Process variables to format submission info for display in the forum list and topic list.
 *
 * $vars will contain: $topic
 *
 * @see forum-submitted.tpl.php
 * @see theme_forum_submitted()
 */
function mobile_jquery_preprocess_forum_submitted(&$vars) {
}

/**
 * Preprocesses the rendered tree for theme_menu_tree().
 */
function mobile_jquery_preprocess_menu_tree(&$vars) {
  $use_global = mobile_jquery_theme_get_setting('use_global');
  $vars['attributes'] = array(
    'data-theme' => $use_global ? mobile_jquery_theme_get_setting('global_theme') : mobile_jquery_theme_get_setting('menu_item_theme'),
    'data-role' => 'listview'
  );
}


/**
 * Preprocesses template variables for overlay.tpl.php
 *
 * @see overlay.tpl.php
 */
function mobile_jquery_preprocess_overlay(&$vars) {
  $vars['tabs'] = menu_primary_local_tasks();
  $vars['title'] = drupal_get_title();
  $vars['disable_overlay'] = overlay_disable_message();
  $vars['content_attributes_array']['class'][] = 'clearfix';
}

/**
 * Themes the voting form for a poll.
 *
 * Inputs: $form
 */
function mobile_jquery_preprocess_poll_vote(&$vars) {
  $form = $vars['form'];
  $vars['choice'] = drupal_render($form['choice']);
  $vars['title'] = check_plain($form['#node']->title);
  $vars['vote'] = drupal_render($form['vote']);
  $vars['rest'] = drupal_render_children($form);
  $vars['block'] = $form['#block'];
  if ($vars['block']) {
    $vars['theme_hook_suggestions'][] = 'poll_vote__block';
  }
}

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
function mobile_jquery_preprocess_poll_results(&$vars) {

}

/**
 * Preprocess the poll_bar theme hook.
 *
 * Inputs: $title, $votes, $total_votes, $voted, $block
 *
 * @see poll-bar.tpl.php
 * @see poll-bar--block.tpl.php
 * @see theme_poll_bar()
 */
function mobile_jquery_preprocess_poll_bar(&$vars) {

}

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
function mobile_jquery_preprocess_search_results(&$vars) {

}

/**
 * Process variables for search-result.tpl.php.
 *
 * The $vars array contains the following arguments:
 * - $result
 * - $module
 *
 * @see search-result.tpl.php
 */
function mobile_jquery_preprocess_search_result(&$vars) {
  global $language;

  $result = $vars['result'];
  $vars['url'] = check_url($result['link']);
  $vars['title'] = check_plain($result['title']);
  if (isset($result['language']) && $result['language'] != $language->language && $result['language'] != LANGUAGE_NONE) {
    $vars['title_attributes_array']['xml:lang'] = $result['language'];
    $vars['content_attributes_array']['xml:lang'] = $result['language'];
  }

  $info = array();
  if (!empty($result['module'])) {
    $info['module'] = check_plain($result['module']);
  }
  if (!empty($result['user'])) {
    $info['user'] = $result['user'];
  }
  if (!empty($result['date'])) {
    $info['date'] = format_date($result['date'], 'short');
  }
  if (isset($result['extra']) && is_array($result['extra'])) {
    $info = array_merge($info, $result['extra']);
  }
  // Check for existence. User search does not include snippets.
  $vars['snippet'] = isset($result['snippet']) ? strip_tags($result['snippet']) : '';
  // Provide separated and grouped meta information..
  $vars['info_split'] = $info;
  $vars['info'] = strip_tags(implode(' - ', $info));
  $vars['theme_hook_suggestions'][] = 'search_result__' . $vars['module'];

}

/**
 * Process variables for taxonomy-term.tpl.php.
 */
function mobile_jquery_preprocess_taxonomy_term(&$vars) {

}


/**
 * Process variables for user-picture.tpl.php.
 *
 * The $vars array contains the following arguments:
 * - $account: A user, node or comment object with 'name', 'uid' and 'picture'
 *   fields.
 *
 * @see user-picture.tpl.php
 */
function mobile_jquery_preprocess_user_picture(&$vars) {
  $vars['user_picture'] = '';
  if (variable_get('user_pictures', 0)) {
    $account = $vars['account'];
    if (!empty($account->picture)) {
      // @TODO: Ideally this function would only be passed file objects, but
      // since there's a lot of legacy code that JOINs the {users} table to
      // {node} or {comments} and passes the results into this function if we
      // a numeric value in the picture field we'll assume it's a file id
      // and load it for them. Once we've got user_load_multiple() and
      // comment_load_multiple() functions the user module will be able to load
      // the picture files in mass during the object's load process.
      if (is_numeric($account->picture)) {
        $account->picture = file_load($account->picture);
      }
      if (!empty($account->picture->uri)) {
        $filepath = $account->picture->uri;
      }
    }
    elseif (variable_get('user_picture_default', '')) {
      $filepath = variable_get('user_picture_default', '');
    }
    if (isset($filepath)) {
      $alt = t("@user's picture", array('@user' => format_username($account)));
      // If the image does not have a valid Drupal scheme (for eg. HTTP),
      // don't load image styles.
      if (module_exists('image') && file_valid_uri($filepath) && $style = variable_get('user_picture_style', '')) {
        $vars['user_picture'] = theme('image_style', array('style_name' => $style, 'path' => $filepath, 'alt' => $alt, 'title' => $alt));
      }
      else {
        $vars['user_picture'] = theme('image', array('path' => $filepath, 'alt' => $alt, 'title' => $alt));
      }
      if (!empty($account->uid) && user_access('access user profiles')) {
        $attributes = array('attributes' => array('title' => t('View user profile.')), 'html' => TRUE);
        $vars['user_picture'] = l($vars['user_picture'], "user/$account->uid", $attributes);
      }
    }
  }
}

/**
 * Process variables for user-profile.tpl.php.
 *
 * The $vars array contains the following arguments:
 * - $account
 *
 * @see user-profile.tpl.php
 */
function mobile_jquery_preprocess_user_profile(&$vars) {

}

/**
 * Process variables for user-profile-item.tpl.php.
 *
 * The $vars array contains the following arguments:
 * - $element
 *
 * @see user-profile-item.tpl.php
 */
function mobile_jquery_preprocess_user_profile_item(&$vars) {

}

/**
 * Process variables for user-profile-category.tpl.php.
 *
 * The $vars array contains the following arguments:
 * - $element
 *
 * @see user-profile-category.tpl.php
 */
function mobile_jquery_preprocess_user_profile_category(&$vars) {

}


