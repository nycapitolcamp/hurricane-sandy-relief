<?php
/**
 * @file
 * Contains theme override functions and preprocess functions for the mobile_jquery theme.
 */

/**
 * Returns HTML for the date settings form.
 *
 * @param $vars
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @ingroup themeable
 */
function mobile_jquery_system_date_time_settings($vars) {
  $form = $vars['form'];
  $header = array(
    t('Date type'),
    t('Format'),
    t('Operations'),
  );

  foreach (element_children($form['format']) as $key) {
    $delete_key = $key . '_delete';
    $row = array();
    $row[] = $form['format'][$key]['#title'];
    $form['format'][$key]['#title_display'] = 'invisible';
    $form['delete'][$delete_key]['#attributes'] = array('data-role' => 'button', 'data-icon' => 'delete');
    $row[] = array('data' => drupal_render($form['format'][$key]));
    $row[] = array('data' => drupal_render($form['delete'][$delete_key]));
    $rows[] = $row;
  }

  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'system-date-types')));
  $output .= drupal_render_children($form);

  return $output;
}

/**
 * Returns HTML for an administrative block for display.
 *
 * @param $vars
 *   An associative array containing:
 *   - block: An array containing information about the block:
 *     - show: A Boolean whether to output the block. Defaults to FALSE.
 *     - title: The block's title.
 *     - content: (optional) Formatted content for the block.
 *     - description: (optional) Description of the block. Only output if
 *       'content' is not set.
 *
 * @ingroup themeable
 */
function mobile_jquery_admin_block($vars) {
  $block = $vars['block'];
  $output = '';

  // Don't display the block if it has no content to display.
  if (empty($block['show'])) {
    return $output;
  }

  $output .= '<div class="admin-panel">';
  if (!empty($block['title'])) {
    $output .= '<h3>' . $block['title'] . '</h3>';
  }
  if (!empty($block['content'])) {
    $output .= '<div class="body">' . $block['content'] . '</div>';
  }
  else {
    $output .= '<div class="description">' . $block['description'] . '</div>';
  }
  $output .= '</div>';

  return $output;
}

/**
 * Returns HTML for the content of an administrative block.
 *
 * @param $vars
 *   An associative array containing:
 *   - content: An array containing information about the block. Each element
 *     of the array represents an administrative menu item, and must at least
 *     contain the keys 'title', 'href', and 'localized_options', which are
 *     passed to l(). A 'description' key may also be provided.
 *
 * @ingroup themeable
 */
function mobile_jquery_admin_block_content($vars) {
  $use_global = mobile_jquery_theme_get_setting('use_global');
  $content = $vars['content'];
  $output = '';
  
  $attributes = array();

  $attributes['data-role'] = 'listview'; 
  $attributes['data-inset'] = $use_global ? mobile_jquery_theme_get_setting('global_inset') : mobile_jquery_theme_get_setting('menu_item_inset'); 
  $attributes['data-theme'] = $use_global ? mobile_jquery_theme_get_setting('global_theme') : mobile_jquery_theme_get_setting('menu_item_theme');
  $attributes['data-divider-theme'] = $use_global ? mobile_jquery_theme_get_setting('global_theme') : mobile_jquery_theme_get_setting('menu_item_dividertheme');
  $attributes['data-count-theme'] = $use_global ? mobile_jquery_theme_get_setting('global_theme') : mobile_jquery_theme_get_setting('menu_item_counttheme');
  $attributes['data-split-theme'] = $use_global ? mobile_jquery_theme_get_setting('global_theme') : mobile_jquery_theme_get_setting('menu_item_splittheme');
  $attributes['data-split-icon'] = $use_global ? mobile_jquery_theme_get_setting('global_icon') : mobile_jquery_theme_get_setting('menu_item_spliticon');

  if (!empty($content)) {

    $class = 'admin-list';
    if ($compact = system_admin_compact_mode()) {
      $class .= ' compact';
    }

    $output = '<ul ' . drupal_attributes($attributes) . '>';

    foreach ($content as $item) {
      $item['localized_options']['html'] = TRUE;
      $link = '<h3>' . $item['title'] . '</h3>';
      if (!$compact && isset($item['description'])) {
        $link .= '<p>' . filter_xss_admin(strip_tags($item['description'])) . '</p>';
      }
      $output .= '<li>' . l($link, $item['href'], $item['localized_options']) . '</li>';
    }
    
    $output .= '</ul>';
  }
  
  return $output;
}

/**
 * Returns HTML for an administrative page.
 *
 * @param $vars
 *   An associative array containing:
 *   - blocks: An array of blocks to display. Each array should include a
 *     'title', a 'description', a formatted 'content' and a 'position' which
 *     will control which container it will be in. This is usually 'left' or
 *     'right'.
 *
 * @ingroup themeable
 */
function mobile_jquery_admin_page($vars) {
  $blocks = $vars['blocks'];

  $stripe = 0;
  $container = array();

  foreach ($blocks as $block) {
    if ($block_output = theme('admin_block', array('block' => $block))) {
      if (empty($block['position'])) {
        // perform automatic striping.
        $block['position'] = ++$stripe % 2 ? 'left' : 'right';
      }
      if (!isset($container[$block['position']])) {
        $container[$block['position']] = '';
      }
      $container[$block['position']] .= $block_output;
    }
  }

  $output = '<div class="admin clearfix">';
  $output .= theme('system_compact_link');

  foreach ($container as $id => $data) {
    $output .= '<div class="' . $id . ' clearfix">';
    $output .= $data;
    $output .= '</div>';
  }
  $output .= '</div>';
  return $output;
}

/**
 * Returns HTML for the output of the dashboard page.
 *
 * @param $vars
 *   An associative array containing:
 *   - menu_items: An array of modules to be displayed.
 *
 * @ingroup themeable
 */
function mobile_jquery_system_admin_index($vars) {
  $menu_items = $vars['menu_items'];

  $stripe = 0;
  $container = array('left' => '', 'right' => '');
  $flip = array('left' => 'right', 'right' => 'left');
  $position = 'left';

  // Iterate over all modules.
  foreach ($menu_items as $module => $block) {
    list($description, $items) = $block;

    // Output links.
    if (count($items)) {
      $block = array();
      $block['title'] = $module;
      $block['content'] = theme('admin_block_content', array('content' => $items));
      $block['description'] = t($description);
      $block['show'] = TRUE;

      if ($block_output = theme('admin_block', array('block' => $block))) {
        if (!isset($block['position'])) {
          // Perform automatic striping.
          $block['position'] = $position;
          $position = $flip[$position];
        }
        $container[$block['position']] .= $block_output;
      }
    }
  }

  $output = '<div class="admin clearfix">';
  $output .= theme('system_compact_link');
  foreach ($container as $id => $data) {
    $output .= '<div class="' . $id . ' clearfix">';
    $output .= $data;
    $output .= '</div>';
  }
  $output .= '</div>';

  return $output;
}

/**
 * Returns HTML for the status report.
 *
 * @param $vars
 *   An associative array containing:
 *   - requirements: An array of requirements.
 *
 * @ingroup themeable
 */
function mobile_jquery_status_report($vars) {
  $requirements = $vars['requirements'];
  $severities = array(
    REQUIREMENT_INFO => array(
      'title' => t('Info'),
      'class' => 'info',
    ),
    REQUIREMENT_OK => array(
      'title' => t('OK'),
      'class' => 'ok',
    ),
    REQUIREMENT_WARNING => array(
      'title' => t('Warning'),
      'class' => 'warning',
    ),
    REQUIREMENT_ERROR => array(
      'title' => t('Error'),
      'class' => 'error',
    ),
  );
  $output = '<table class="system-status-report">';

  foreach ($requirements as $requirement) {
    if (empty($requirement['#type'])) {
      $severity = $severities[isset($requirement['severity']) ? (int) $requirement['severity'] : 0];
      $severity['icon'] = '<div title="' . $severity['title'] . '"><span class="element-invisible">' . $severity['title'] . '</span></div>';

      // Output table row(s)
      if (!empty($requirement['description'])) {
        $output .= '<tr class="' . $severity['class'] . ' merge-down"><td class="status-icon">' . $severity['icon'] . '</td><td class="status-title">' . $requirement['title'] . '</td><td class="status-value">' . $requirement['value'] . '</td></tr>';
        $output .= '<tr class="' . $severity['class'] . ' merge-up"><td colspan="3" class="status-description">' . $requirement['description'] . '</td></tr>';
      }
      else {
        $output .= '<tr class="' . $severity['class'] . '"><td class="status-icon">' . $severity['icon'] . '</td><td class="status-title">' . $requirement['title'] . '</td><td class="status-value">' . $requirement['value'] . '</td></tr>';
      }
    }
  }

  $output .= '</table>';
  return $output;
}

/**
 * Returns HTML for the modules form.
 *
 * @param $vars
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @ingroup themeable
 */
function mobile_jquery_system_modules_fieldset($vars) {
  $form = $vars['form'];

  $output = '<div class="ui-grid-b">';
  
  // Iterate through all the modules, which are
  // children of this fieldset.
  foreach (element_children($form) as $key) {
    // Stick it into $module for easier accessing.
    $module = $form[$key];

    //unset($module['enable']['#title']);
    //$module['enable']['#title'] = $module['name'];
    $mod = array();
    
    foreach ($module['enable'] as $key => $value) {
      if ($key === '#title') {
        $mod[$key] = $module['name']['#markup'];
      }
      else {
        $mod[$key] = $value;
      }
    }

    $output .= '<div class="ui-block-a checkbox">' . drupal_render($mod) . '</div>';
    
    
    // Add the description, along with any modules it requires.
    $description = drupal_render($module['description']);
    if ($module['#requires']) {
      $description .= '<div class="admin-requirements">' . t('Requires: !module-list', array('!module-list' => implode(', ', $module['#requires']))) . '</div>';
    }
    if ($module['#required_by']) {
      $description .= '<div class="admin-requirements">' . t('Required by: !module-list', array('!module-list' => implode(', ', $module['#required_by']))) . '</div>';
    }
    $description .= '<div class="admin-version">' . t('Version') . ': ' . drupal_render($module['version']) . '</div>';
    $output .= '<div class="ui-block-b"><div class="description">' . $description . '</div></div>';
    
    // Display links (such as help or permissions) in their own columns.
    $links = '';
    foreach (array('help', 'permissions', 'configure') as $key) {
      $module['links'][$key]['#attributes'] = array('data-role' => 'button', 'data-icon' => $key, 'data-iconpos' => 'notext');
      $links .= drupal_render($module['links'][$key]);
    }
    $output .= '<div class="ui-block-c">' . $links . '</div>';
  }

  $output .=  '</div>';
  return $output;
}

/**
 * Returns HTML for a table of currently disabled modules.
 *
 * @param $vars
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @ingroup themeable
 */
function mobile_jquery_system_modules_uninstall($vars) {
  $form = $vars['form'];

  // No theming for the confirm form.
  if (isset($form['confirm'])) {
    return drupal_render($form);
  }

  // Table headers.
  $header = array(
    t('Uninstall'),
    t('Name'),
    t('Description'),
  );

  // Display table.
  $rows = array();
  foreach (element_children($form['modules']) as $module) {
    if (!empty($form['modules'][$module]['#required_by'])) {
      $disabled_message = format_plural(count($form['modules'][$module]['#required_by']),
        'To uninstall @module, the following module must be uninstalled first: @required_modules',
        'To uninstall @module, the following modules must be uninstalled first: @required_modules',
        array('@module' => $form['modules'][$module]['#module_name'], '@required_modules' => implode(', ', $form['modules'][$module]['#required_by'])));
      $disabled_message = '<div class="admin-requirements">' . $disabled_message . '</div>';
    }
    else {
      $disabled_message = '';
    }
    
    $rows[] = array(
      array('data' => drupal_render($form['uninstall'][$module]), 'align' => 'center'),
      '<strong>' . drupal_render($form['modules'][$module]['name']) . '</strong>',
      array('data' => drupal_render($form['modules'][$module]['description']) . $disabled_message, 'class' => array('description')),
    );
  }

  $output = theme('table', array('header' => $header, 'rows' => $rows, 'empty' => t('No modules are available to uninstall.')));
  $output .= drupal_render_children($form);

  return $output;
}

/**
 * Returns HTML for the Appearance page.
 *
 * @param $vars
 *   An associative array containing:
 *   - theme_groups: An associative array containing groups of themes.
 *
 * @ingroup themeable
 */
function mobile_jquery_system_themes_page($vars) {
  $theme_groups = $vars['theme_groups'];

  $output = '<div id="system-themes-page">';

  foreach ($vars['theme_group_titles'] as $state => $title) {
    if (!count($theme_groups[$state])) {
      // Skip this group of themes if no theme is there.
      continue;
    }
    // Start new theme group.
    $attributes = array('class' => array('system-themes-list', 'system-themes-list-' . $state, 'clearfix'));
    $attributes['data-role'] = "collapsible";
    if ($state != 'enabled') {
      $attributes['data-collapsed'] = "true";
    }
    $output .= '<div ' . drupal_attributes($attributes) . '><h2>' . $title . '</h2>';

    foreach ($theme_groups[$state] as $theme) {

      // Theme the screenshot.
      $screenshot = $theme->screenshot ? theme('image', $theme->screenshot) : '<div class="no-screenshot">' . t('no screenshot') . '</div>';

      // Localize the theme description.
      $description = t($theme->info['description']);

      // Style theme info
      $notes = count($theme->notes) ? ' (' . join(', ', $theme->notes) . ')' : '';
      $theme->classes[] = 'theme-selector';
      $theme->classes[] = 'clearfix';
      $output .= '<div class="' . join(' ', $theme->classes) . '"><div class="theme-info"><h3>' . $theme->info['name'] . ' ' . (isset($theme->info['version']) ? $theme->info['version'] : '') . $notes . '</h3><div class="theme-description">' . $description . '</div>';
      $output .= '<div>' . $screenshot . '</div>';

      // Make sure to provide feedback on compatibility.
      if (!empty($theme->incompatible_core)) {
        $output .= '<div class="incompatible">' . t('This version is not compatible with Drupal !core_version and should be replaced. ', array('!core_version' => DRUPAL_CORE_COMPATIBILITY)) . '</div>';
      }
      elseif (!empty($theme->incompatible_php)) {
        if (substr_count($theme->info['php'], '.') < 2) {
          $theme->info['php'] .= '.*';
        }
        $output .= '<div class="incompatible">' . t('This theme requires PHP version @php_required and is incompatible with PHP version !php_version. ', array('@php_required' => $theme->info['php'], '!php_version' => phpversion())) . '</div>';
      }
      else {
        $output .= '<div data-role="controlgroup" data-type="horizontal">';
        foreach ($theme->operations as $key => $value) {
          $theme->operations[$key]['attributes']['data-role'] = 'button';
          $output .= l($theme->operations[$key]['title'], $theme->operations[$key]['href'], array('attributes' => $theme->operations[$key]['attributes']));
        }
        //$output .= theme('links', array('links' => $theme->operations, 'attributes' => array('class' => array('operations', 'clearfix'))));

        $output .= '</div>';
      }
      $output .= '</div></div>';
    }
    $output .= '</div>';
  }
  $output .= '</div>';

  return $output;
}

/**
 * Returns HTML for a link to show or hide inline help descriptions.
 *
 * @ingroup themeable
 */
function mobile_jquery_system_compact_link() {
  $output = '<div class="compact-link">';
  if (system_admin_compact_mode()) {
    $output .= l(t('Show descriptions'), 'admin/compact/off', array('attributes' => array('title' => t('Expand layout to include descriptions.')), 'query' => drupal_get_destination()));
  }
  else {
    $output .= l(t('Hide descriptions'), 'admin/compact/on', array('attributes' => array('title' => t('Compress layout by hiding descriptions.')), 'query' => drupal_get_destination()));
  }
  $output .= '</div>';

  return $output;
}

/**
 * Returns HTML for the Powered by Drupal text.
 *
 * @ingroup themeable
 */
function mobile_jquery_system_powered_by() {
  return '<span>' . t('Powered by <a href="@poweredby">Drupal</a>', array('@poweredby' => 'http://drupal.org')) . '</span>';
}

/**
 * Returns HTML for a confirmation form.
 *
 * By default this does not alter the appearance of a form at all,
 * but is provided as a convenience for themers.
 *
 * @param $vars
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @ingroup themeable
 */
function mobile_jquery_confirm_form($vars) {
  $form = $vars['form'];
  
  $form['actions']['cancel']['#attributes'] += array(
    'data-role' => 'button',
  );

  return drupal_render_children($form);
}

/**
 * Returns HTML for a system settings form.
 *
 * By default this does not alter the appearance of a form at all,
 * but is provided as a convenience for themers.
 *
 * @param $vars
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @ingroup themeable
 */
function mobile_jquery_system_settings_form($vars) {
  return drupal_render_children($vars['form']);
}

/**
 * Returns HTML for an exposed filter form.
 *
 * @param $vars
 *   An associative array containing:
 *   - form: An associative array containing the structure of the form.
 *
 * @return
 *   A string containing an HTML-formatted form.
 *
 * @ingroup themeable
 */
function mobile_jquery_exposed_filters($vars) {
  $form = $vars['form'];
  $output = '';

  if (isset($form['current'])) {
    $items = array();
    foreach (element_children($form['current']) as $key) {
      $items[] = drupal_render($form['current'][$key]);
    }
    $output .= theme('item_list', array('items' => $items, 'attributes' => array('class' => array('clearfix', 'current-filters'))));
  }

  $output .= drupal_render_children($form);

  return '<div class="exposed-filters">' . $output . '</div>';
}
