<?php
/**
 * @file
 * Contains theme override functions and preprocess functions for the mobile_jquery theme.
 */

/**
 * Returns HTML for a list or nested list of items.
 *
 * @param $vars
 *   An associative array containing:
 *   - items: An array of items to be displayed in the list. If an item is a
 *     string, then it is used as is. If an item is an array, then the "data"
 *     element of the array is used as the contents of the list item. If an item
 *     is an array with a "children" element, those children are displayed in a
 *     nested list. All other elements are treated as attributes of the list
 *     item element.
 *   - title: The title of the list.
 *   - type: The type of list to return (e.g. "ul", "ol").
 *   - attributes: The attributes applied to the list element.
 */
function mobile_jquery_item_list($vars) {
  $use_global = mobile_jquery_theme_get_setting('use_global');
  $items = $vars['items'];
  $title = $vars['title'];
  $type = $vars['type'];
  
  $attributes = $vars['attributes'];
  $attributes['data-role'] = 'listview'; 
  $attributes['data-inset'] = $use_global ? mobile_jquery_theme_get_setting('global_inset') : mobile_jquery_theme_get_setting('list_item_inset'); 
  $attributes['data-theme'] = $use_global ? mobile_jquery_theme_get_setting('global_theme') : mobile_jquery_theme_get_setting('list_item_theme');
  $attributes['data-divider-theme'] = $use_global ? mobile_jquery_theme_get_setting('global_theme') : mobile_jquery_theme_get_setting('list_item_dividertheme');
  $attributes['data-count-theme'] = $use_global ? mobile_jquery_theme_get_setting('global_theme') : mobile_jquery_theme_get_setting('list_item_counttheme');
  $attributes['data-split-theme'] = $use_global ? mobile_jquery_theme_get_setting('global_theme') : mobile_jquery_theme_get_setting('list_item_splittheme');
  $attributes['data-split-icon'] = $use_global ? mobile_jquery_theme_get_setting('global_icon') : mobile_jquery_theme_get_setting('list_item_spliticon');

  $output = '';

  if (isset($title)) {
    $output .= '<h3>' . $title . '</h3>';
  }

  if (!empty($items)) {
    $output .= "<$type" . drupal_attributes($attributes) . '>';
    $num_items = count($items);
    foreach ($items as $i => $item) {
      $list_attributes = array();
      $children = array();
      $data = '';
      if (is_array($item)) {
        foreach ($item as $key => $value) {
          if ($key == 'data') {
            $data = $value;
          }
          elseif ($key == 'children') {
            $children = $value;
          }
          else {
            $list_attributes[$key] = $value;
          }
        }
      }
      else {
        $data = $item;
      }
      
      $list_attributes['data-icon'] = $use_global ? mobile_jquery_theme_get_setting('global_icon') : mobile_jquery_theme_get_setting('list_item_icon');
      
      if (count($children) > 0) {
        // Render nested list.
        $data .= theme_item_list(array('items' => $children, 'title' => NULL, 'type' => $type, 'attributes' => $list_attributes));
      }
      if ($i == 0) {
        $list_attributes['class'][] = 'first';
      }
      if ($i == $num_items - 1) {
        $list_attributes['class'][] = 'last';
      }
      
      $output .= '<li' . drupal_attributes($list_attributes) . '>' . $data . "</li>\n";
    }
    $output .= "</$type>";
  }
  return $output;
}

/**
 * Returns HTML for a breadcrumb trail.
 *
 * @param $vars
 *   An associative array containing:
 *   - breadcrumb: An array containing the breadcrumb links.
 */
function mobile_jquery_breadcrumb($vars) {
  $breadcrumb = $vars['breadcrumb'];

  if (!empty($breadcrumb)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $output = '<h2 class="element-invisible">' . t('You are here') . '</h2>';

    $output .= '<div class="breadcrumb" data-role="controlgroup" data-type="horizontal">' . implode('', $breadcrumb) . '</div>';
    return $output;
  }
}

/**
 * Returns HTML for a "more help" link.
 *
 * @param $vars
 *   An associative array containing:
 *   - url: The url for the link.
 */
function mobile_jquery_more_help_link($vars) {
  return '<div class="more-help-link">' . l(t('More help'), $vars['url'], array('attributes' => array('data-rel' => 'dialog', 'data-transition' => 'pop'))) . '</div>';
}

/**
 * Returns HTML for a "more" link, like those used in blocks.
 *
 * @param $variables
 *   An associative array containing:
 *   - url: The url of the main page.
 *   - title: A descriptive verb for the link, like 'Read more'.
 */
function mobile_jquery_more_link($variables) {
  return '<div class="more-link">' . l(t('More'), $variables['url'], array('attributes' => array('title' => $variables['title'], 'data-role' => 'button', 'data-icon' => 'arrow-r', 'data-iconpos' => 'right'))) . '</div>';
}

/**
 * Returns HTML for a username, potentially linked to the user's page.
 *
 * @param $vars
 *   An associative array containing:
 *   - account: The user object to format.
 *   - name: The user's name, sanitized.
 *   - extra: Additional text to append to the user's name, sanitized.
 *   - link_path: The path or URL of the user's profile page, home page, or
 *     other desired page to link to for more information about the user.
 *   - link_options: An array of options to pass to the l() function's $options
 *     parameter if linking the user's name to the user's page.
 *   - attributes_array: An array of attributes to pass to the
 *     drupal_attributes() function if not linking to the user's page.
 *
 * @see template_preprocess_username()
 * @see template_process_username()
 */
function mobile_jquery_username($vars) {
  if (isset($vars['link_path'])) {
    // We have a link path, so we should generate a link using l().
    // Additional classes may be added as array elements like
    // $vars['link_options']['attributes']['class'][] = 'myclass';
    $output = l($vars['name'] . $vars['extra'], $vars['link_path'], $vars['link_options']);
  }
  else {
    // Modules may have added important attributes so they must be included
    // in the output. Additional classes may be added as array elements like
    // $vars['attributes_array']['class'][] = 'myclass';
    $output = '<span' . drupal_attributes($vars['attributes_array']) . '>' . $vars['name'] . $vars['extra'] . '</span>';
  }
  return $output;
}

/**
 * Returns HTML for status and/or error messages, grouped by type.
 *
 * An invisible heading identifies the messages for assistive technology.
 * Sighted users see a colored box. See http://www.w3.org/TR/WCAG-TECHS/H69.html
 * for info.
 *
 * @param $vars
 *   An associative array containing:
 *   - display: (optional) Set to 'status' or 'error' to display only messages
 *     of that type.
 */
function mobile_jquery_status_messages($vars) {
  $display = $vars['display'];
  $output = '';

  $status_heading = array(
    'status' => t('Status message'),
    'error' => t('Error message'),
    'warning' => t('Warning message'),
  );
    foreach (drupal_get_messages($display) as $type => $messages) {
      $output .= "<div class=\"ui-body ui-body-$type messages $type\">\n";
      if (!empty($status_heading[$type])) {
        $output .= '<h2 class="element-invisible">' . $status_heading[$type] . "</h2>\n";
      }
      if (count($messages) > 1) {
        $output .= " <ul>\n";
        foreach ($messages as $message) {
          $output .= '  <li>' . $message . "</li>\n";
        }
        $output .= " </ul>\n";
      }
      else {
        $output .= $messages[0];
      }
      $output .= "</div>\n";
    }
  return $output;
}

/**
 * Returns HTML for a link.
 *
 * All Drupal code that outputs a link should call the l() function. That
 * function performs some initial preprocessing, and then, if necessary, calls
 * theme('link') for rendering the anchor tag.
 *
 * To optimize performance for sites that don't need custom theming of links,
 * the l() function includes an inline copy of this function, and uses that copy
 * if none of the enabled modules or the active theme implement any preprocess
 * or process functions or override this theme implementation.
 *
 * @param $vars
 *   An associative array containing the keys 'text', 'path', and 'options' . See
 *   the l() function for information about these variables.
 *
 * @see l()
 */
function mobile_jquery_link($vars) {
  if (variable_get('admin_theme', 0) != 0 || variable_get('theme_default', '') != variable_get('admin_theme', 0)) {
      if (path_is_admin($vars['path'])) {
        $vars['options']['attributes']['data-ajax'] = 'false';
      }
  }
  return '<a href="' . check_plain(url($vars['path'], $vars['options'])) . '"' . drupal_attributes($vars['options']['attributes']) . '>' . ($vars['options']['html'] ? $vars['text'] : check_plain($vars['text'])) . '</a>';
}

function mobile_jquery_links($vars) {
  global $language_url;
  $use_global = mobile_jquery_theme_get_setting('use_global');

  $links = $vars['links'];
  $heading = $vars['heading'];
  $attributes = $vars['attributes'];

  $attributes['data-role'] = 'listview'; 
  $attributes['data-inset'] = $use_global ? mobile_jquery_theme_get_setting('global_inset') : mobile_jquery_theme_get_setting('menu_item_inset'); 
  $attributes['data-theme'] = $use_global ? mobile_jquery_theme_get_setting('global_theme') : mobile_jquery_theme_get_setting('menu_item_theme');
  $attributes['data-divider-theme'] = $use_global ? mobile_jquery_theme_get_setting('global_theme') : mobile_jquery_theme_get_setting('menu_item_dividertheme');
  $attributes['data-count-theme'] = $use_global ? mobile_jquery_theme_get_setting('global_theme') : mobile_jquery_theme_get_setting('menu_item_counttheme');
  $attributes['data-split-theme'] = $use_global ? mobile_jquery_theme_get_setting('global_theme') : mobile_jquery_theme_get_setting('menu_item_splittheme');
  $attributes['data-split-icon'] = $use_global ? mobile_jquery_theme_get_setting('global_icon') : mobile_jquery_theme_get_setting('menu_item_spliticon');

  $output = '';
  
  // Treat the heading first if it is present to prepend it to the
  // list of links.
  if (!empty($heading)) {
    if (is_string($heading)) {
      // Prepare the array that will be used when the passed heading
      // is a string.
      $heading = array(
        'text' => $heading,
        // Set the default level of the heading.
        'level' => 'h2',
      );
    }
    $output .= '<' . $heading['level'];
    if (!empty($heading['class'])) {
      $output .= drupal_attributes(array('class' => $heading['class']));
    }
    $output .= '>' . check_plain($heading['text']) . '</' . $heading['level'] . '>';
  }
  if (count($links) > 0) {

    $output .= '<ul' . drupal_attributes($attributes) . '>';
    
    $num_links = count($links);
    $i = 1;

    foreach ($links as $key => $link) {
      $class = array($key);
      $list_attributes = array();
      $list_attributes['data-icon'] = $use_global ? mobile_jquery_theme_get_setting('global_icon') : mobile_jquery_theme_get_setting('list_item_icon');

      // Add first, last and active classes to the list of links to help out themers.
      if ($i == 1) {
        $class[] = 'first';
      }
      if ($i == $num_links) {
        $class[] = 'last';
      }
      if (isset($link['href']) && ($link['href'] == $_GET['q'] || ($link['href'] == '<front>' && drupal_is_front_page()))
          && (empty($link['language']) || $link['language']->language == $language_url->language)) {
        $class[] = 'active';
      }
      $list_attributes['class'] = $class;
      $output .= '<li' . drupal_attributes($list_attributes) . '>';

      if (isset($link['href'])) {
        // Pass in $link as $options, they share the same keys.
        $output .= l($link['title'], $link['href'], $link);
      }
      elseif (!empty($link['title'])) {
        // Some links are actually not links, but we wrap these in <span> for adding title and class attributes.
        if (empty($link['html'])) {
          $link['title'] = check_plain($link['title']);
        }
        $span_attributes = '';
        if (isset($link['attributes'])) {
          $span_attributes = drupal_attributes($link['attributes']);
        }
        $output .= '<span' . $span_attributes . '>' . $link['title'] . '</span>';
      }

      $i++;
      $output .= "</li>\n";
    }

    $output .= '</ul>';
  }

  return $output;
}


function mobile_jquery_links__node($vars) {
  $links = $vars['links'];
  $output = '<div data-role="controlgroup" data-type="horizontal">';

  foreach ($links as $link => $value) {
    if (!isset($links[$link]['attributes'])) {
      $links[$link]['attributes'] = array();
    }
    if ($link != 'comment_forbidden') {
      $links[$link]['attributes']['data-role'] = 'button';
      $links[$link]['attributes']['data-icon'] = $link;
    }
    
    $output .= l($links[$link]['title'], $links[$link]['href'], array('attributes' => $links[$link]['attributes'], 'html' => TRUE));
  }
  
  $output .= '</div>';
  
  return $output;
}

function mobile_jquery_links__contextual($vars) {
  $output = '';
  $links = $vars['links'];
  
  foreach ($links as $link => $value) {
    $path = explode('/', $links[$link]['href']);
    $icon = $path[count($path)-1];
    
    $attributes = array(
      'data-role' => 'button', 
      'data-iconpos' => 'notext', 
      'data-icon' => $icon,
    );
    if ($icon == 'delete') {
      $attributes['data-rel'] = 'dialog';
    }
    $output .= l($links[$link]['title'], $links[$link]['href'], array('title' => $links[$link]['title'], 'attributes' => $attributes));
  }
  
  return $output;
}

function mobile_jquery_links__comment($vars) {
  $links = $vars['links'];
  $output = '<div data-role="controlgroup" data-type="horizontal">';
  foreach ($links as $link => $value) {
    if (!isset($links[$link]['attributes'])) {
      $links[$link]['attributes'] = array();
    }

    if ($link != 'comment_forbidden') {
      $icon = explode('-', $link);
      $links[$link]['attributes']['data-role'] = 'button';
      $links[$link]['attributes']['data-icon'] = $icon[1];
    }
    $output .= l($links[$link]['title'], $links[$link]['href'], array('attributes' => $links[$link]['attributes'], 'html' => TRUE));
  }
  
  $output .= '</div>';
  
  return $output;
}

function mobile_jquery_links__poll_results($vars) {

}

/**
 * Returns HTML for a table.
 *
 * @param $vars
 *   An associative array containing:
 *   - header: An array containing the table headers. Each element of the array
 *     can be either a localized string or an associative array with the
 *     following keys:
 *     - "data": The localized title of the table column.
 *     - "field": The database field represented in the table column (required
 *       if user is to be able to sort on this column).
 *     - "sort": A default sort order for this column ("asc" or "desc").
 *     - Any HTML attributes, such as "colspan", to apply to the column header
 *       cell.
 *   - rows: An array of table rows. Every row is an array of cells, or an
 *     associative array with the following keys:
 *     - "data": an array of cells
 *     - Any HTML attributes, such as "class", to apply to the table row.
 *     - "no_striping": a boolean indicating that the row should receive no
 *       'even / odd' styling. Defaults to FALSE.
 *     Each cell can be either a string or an associative array with the
 *     following keys:
 *     - "data": The string to display in the table cell.
 *     - "header": Indicates this cell is a header.
 *     - Any HTML attributes, such as "colspan", to apply to the table cell.
 *     Here's an example for $rows:
 *     @code
 *     $rows = array(
 *       // Simple row
 *       array(
 *         'Cell 1', 'Cell 2', 'Cell 3'
 *       ),
 *       // Row with attributes on the row and some of its cells.
 *       array(
 *         'data' => array('Cell 1', array('data' => 'Cell 2', 'colspan' => 2)), 'class' => array('funky')
 *       )
 *     );
 *     @endcode
 *   - attributes: An array of HTML attributes to apply to the table tag.
 *   - caption: A localized string to use for the <caption> tag.
 *   - colgroups: An array of column groups. Each element of the array can be
 *     either:
 *     - An array of columns, each of which is an associative array of HTML
 *       attributes applied to the COL element.
 *     - An array of attributes applied to the COLGROUP element, which must
 *       include a "data" attribute. To add attributes to COL elements, set the
 *       "data" attribute with an array of columns, each of which is an
 *       associative array of HTML attributes.
 *     Here's an example for $colgroup:
 *     @code
 *     $colgroup = array(
 *       // COLGROUP with one COL element.
 *       array(
 *         array(
 *           'class' => array('funky'), // Attribute for the COL element.
 *         ),
 *       ),
 *       // Colgroup with attributes and inner COL elements.
 *       array(
 *         'data' => array(
 *           array(
 *             'class' => array('funky'), // Attribute for the COL element.
 *           ),
 *         ),
 *         'class' => array('jazzy'), // Attribute for the COLGROUP element.
 *       ),
 *     );
 *     @endcode
 *     These optional tags are used to group and set properties on columns
 *     within a table. For example, one may easily group three columns and
 *     apply same background style to all.
 *   - sticky: Use a "sticky" table header.
 *   - empty: The message to display in an extra row if table does not have any
 *     rows.
 */
function mobile_jquery_table($vars) {
  $header = $vars['header'];
  $rows = $vars['rows'];
  $attributes = $vars['attributes'];
  $caption = $vars['caption'];
  $colgroups = $vars['colgroups'];
  $sticky = $vars['sticky'];
  $empty = $vars['empty'];

  // Add sticky headers, if applicable.
  if (count($header) && $sticky) {
    drupal_add_js('misc/tableheader.js');
    // Add 'sticky-enabled' class to the table to identify it for JS.
    // This is needed to target tables constructed by this function.
    $attributes['class'][] = 'sticky-enabled';
  }

  $output = '<table' . drupal_attributes($attributes) . ">\n";

  if (isset($caption)) {
    $output .= '<caption>' . $caption . "</caption>\n";
  }

  // Format the table columns:
  if (count($colgroups)) {
    foreach ($colgroups as $number => $colgroup) {
      $attributes = array();

      // Check if we're dealing with a simple or complex column
      if (isset($colgroup['data'])) {
        foreach ($colgroup as $key => $value) {
          if ($key == 'data') {
            $cols = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $cols = $colgroup;
      }

      // Build colgroup
      if (is_array($cols) && count($cols)) {
        $output .= ' <colgroup' . drupal_attributes($attributes) . '>';
        $i = 0;
        foreach ($cols as $col) {
          $output .= ' <col' . drupal_attributes($col) . ' />';
        }
        $output .= " </colgroup>\n";
      }
      else {
        $output .= ' <colgroup' . drupal_attributes($attributes) . " />\n";
      }
    }
  }

  // Add the 'empty' row message if available.
  if (!count($rows) && $empty) {
    $header_count = 0;
    foreach ($header as $header_cell) {
      if (is_array($header_cell)) {
        $header_count += isset($header_cell['colspan']) ? $header_cell['colspan'] : 1;
      }
      else {
        $header_count++;
      }
    }
    $rows[] = array(array('data' => $empty, 'colspan' => $header_count, 'class' => array('empty', 'message')));
  }

  // Format the table header:
  if (count($header)) {
    $ts = tablesort_init($header);
    // HTML requires that the thead tag has tr tags in it followed by tbody
    // tags. Using ternary operator to check and see if we have any rows.
    $output .= (count($rows) ? ' <thead><tr>' : ' <tr>');
    foreach ($header as $cell) {
      $cell = tablesort_header($cell, $header, $ts);
      $output .= _theme_table_cell($cell, TRUE);
    }
    // Using ternary operator to close the tags based on whether or not there are rows
    $output .= (count($rows) ? " </tr></thead>\n" : "</tr>\n");
  }
  else {
    $ts = array();
  }

  // Format the table rows:
  if (count($rows)) {
    $output .= "<tbody>\n";
    $flip = array('even' => 'odd', 'odd' => 'even');
    $class = 'even';
    foreach ($rows as $number => $row) {
      $attributes = array();

      // Check if we're dealing with a simple or complex row
      if (isset($row['data'])) {
        foreach ($row as $key => $value) {
          if ($key == 'data') {
            $cells = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $cells = $row;
      }
      if (count($cells)) {
        // Add odd/even class
        if (empty($row['no_striping'])) {
          $class = $flip[$class];
          $attributes['class'][] = $class;
        }

        // Build row
        $output .= ' <tr' . drupal_attributes($attributes) . '>';
        $i = 0;
        foreach ($cells as $cell) {
          $cell = tablesort_cell($cell, $header, $ts, $i++);
          $output .= _theme_table_cell($cell);
        }
        $output .= " </tr>\n";
      }
    }
    $output .= "</tbody>\n";
  }

  $output .= "</table>\n";
  return $output;
}

/**
 * Returns HTML for a sort icon.
 *
 * @param $vars
 *   An associative array containing:
 *   - style: Set to either 'asc' or 'desc', this determines which icon to show.
 */
function mobile_jquery_tablesort_indicator($vars) {
  if ($vars['style'] == "asc") {
    return theme('image', array('path' => 'misc/arrow-asc.png', 'width' => 13, 'height' => 13, 'alt' => t('sort ascending'), 'title' => t('sort ascending')));
  }
  else {
    return theme('image', array('path' => 'misc/arrow-desc.png', 'width' => 13, 'height' => 13, 'alt' => t('sort descending'), 'title' => t('sort descending')));
  }
}

/**
 * Returns HTML for a feed icon.
 *
 * @param $vars
 *   An associative array containing:
 *   - url: An internal system path or a fully qualified external URL of the
 *     feed.
 *   - title: A descriptive title of the feed.
 */
function mobile_jquery_feed_icon($vars) {
  $text = t('Subscribe to @feed-title', array('@feed-title' => $vars['title']));
  if ($image = theme('image', array('path' => 'misc/feed.png', 'width' => 16, 'height' => 16, 'alt' => $text))) {
    return l($image, $vars['url'], array('html' => TRUE, 'attributes' => array('class' => array('feed-icon'), 'title' => $text)));
  }
}

function mobile_jquery_css_alter(&$css) {
  $excludes = _mobile_jquery_alter(mobile_jquery_theme_get_info('exclude'), 'css');
  $css = array_diff_key($css, $excludes);
}
 

function mobile_jquery_js_alter(&$js) {
  $excludes = _mobile_jquery_alter(mobile_jquery_theme_get_info('exclude'), 'js');
  $js = array_diff_key($js, $excludes);
}


function _mobile_jquery_alter($files, $type) {
  $output = array();
  foreach ($files as $key => $value) {
    foreach ($files[$key][$type] as $file => $name) {
      $output[$name] = FALSE;
    }
  }
  return $output;
}
