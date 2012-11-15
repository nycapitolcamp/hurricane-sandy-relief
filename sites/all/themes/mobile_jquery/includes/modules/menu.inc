<?php
/**
 * @file
 * Contains theme override functions and preprocess functions for the mobile_jquery theme.
 */

/**
 * Returns HTML for a wrapper for a menu sub-tree.
 *
 * @param $vars
 *   An associative array containing:
 *   - tree: An HTML string containing the tree's items.
 *
 * @see template_preprocess_menu_tree()
 * @ingroup themeable
 */
function mobile_jquery_menu_tree($vars) {
  $use_global = mobile_jquery_theme_get_setting('use_global');
  $attributes = $vars['attributes'];

  $attributes['data-role'] = 'listview'; 
  $attributes['data-inset'] = $use_global ? mobile_jquery_theme_get_setting('global_inset') : mobile_jquery_theme_get_setting('menu_item_inset'); 
  $attributes['data-theme'] = $use_global ? mobile_jquery_theme_get_setting('global_theme') : mobile_jquery_theme_get_setting('menu_item_theme');
  $attributes['data-divider-theme'] = $use_global ? mobile_jquery_theme_get_setting('global_theme') : mobile_jquery_theme_get_setting('menu_item_dividertheme');
  $attributes['data-count-theme'] = $use_global ? mobile_jquery_theme_get_setting('global_theme') : mobile_jquery_theme_get_setting('menu_item_counttheme');
  $attributes['data-split-theme'] = $use_global ? mobile_jquery_theme_get_setting('global_theme') : mobile_jquery_theme_get_setting('menu_item_splittheme');
  $attributes['data-split-icon'] = $use_global ? mobile_jquery_theme_get_setting('global_icon') : mobile_jquery_theme_get_setting('menu_item_spliticon');

  return '<ul class="menu" ' . drupal_attributes($attributes) . '>' . $vars['tree'] . '</ul>';
}

/**
 * Returns HTML for a menu link and submenu.
 *
 * @param $vars
 *   An associative array containing:
 *   - element: Structured array data for a menu link.
 *
 * @ingroup themeable
 */

function mobile_jquery_menu_link(array $vars) {
  
  $element = $vars['element'];
  $sub_menu = '';
  if (module_exists('jquerymobile')) {
    $element['#attributes'] = array_merge($element['#attributes'], jquerymobile_get_link_attributes($element['#original_link']));
  }

  if (variable_get('admin_theme', 0) != 0 || variable_get('theme_default', '') != variable_get('admin_theme', 0)) {
      if ( strpos($element['#href'], 'admin') !== FALSE) {
        $element['#localized_options']['attributes']['rel'] = 'external';
      }
  }

  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);

  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}
/**
 * Returns HTML for a single local task link.
 *
 * @param $vars
 *   An associative array containing:
 *   - element: A render element containing:
 *     - #link: A menu link array with 'title', 'href', and 'localized_options'
 *       keys.
 *     - #active: A boolean indicating whether the local task is active.
 *
 * @ingroup themeable
 */
function mobile_jquery_menu_local_task($vars) {
  $link = $vars['element']['#link'];
  $link_text = $link['title'];

  if (!empty($vars['element']['#active'])) {
    // Add text to indicate active tab for non-visual users.
    $active = '<span class="element-invisible">' . t('(active tab)') . '</span>';

    // If the link does not contain HTML already, check_plain() it now.
    // After we set 'html'=TRUE the link will not be sanitized by l().
    if (empty($link['localized_options']['html'])) {
      $link['title'] = check_plain($link['title']);
    }
    $link['localized_options']['html'] = TRUE;
    $link['localized_options']['attributes']['class'][] = 'ui-btn-active';
    $link_text = t('!local-task-title!active', array('!local-task-title' => $link['title'], '!active' => $active));
  }

  return '<li' . (!empty($vars['element']['#active']) ? ' class="active"' : '') . '>' . l($link_text, $link['href'], $link['localized_options']) . "</li>\n";
}

/**
 * Returns HTML for a single local action link.
 *
 * @param $vars
 *   An associative array containing:
 *   - element: A render element containing:
 *     - #link: A menu link array with 'title', 'href', and 'localized_options'
 *       keys.
 *
 * @ingroup themeable
 */
function mobile_jquery_menu_local_action($vars) {
  $link = $vars['element']['#link'];

  $output = '<li>';
  if (isset($link['href'])) {
    $output .= l($link['title'], $link['href'], isset($link['localized_options']) ? $link['localized_options'] : array());
  }
  elseif (!empty($link['localized_options']['html'])) {
    $output .= $link['title'];
  }
  else {
    $output .= check_plain($link['title']);
  }
  $output .= "</li>\n";

  return $output;
}

/**
 * Returns HTML for primary and secondary local tasks.
 *
 * @ingroup themeable
 */
function mobile_jquery_menu_local_tasks(&$vars) {
  $output = '';
  if (!empty($vars['primary'])) {
    $vars['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>';
    $vars['primary']['#prefix'] .= '<div data-role="navbar"><ul class="tabs primary">';
    $vars['primary']['#suffix'] = '</ul></div>';
    $output .= drupal_render($vars['primary']);
  }
  if (!empty($vars['secondary'])) {
    $vars['secondary']['#prefix'] = '<h2 class="element-invisible">' . t('Secondary tabs') . '</h2>';
    $vars['secondary']['#prefix'] .= '<div data-role="navbar"><ul class="tabs secondary">';
    $vars['secondary']['#suffix'] = '</ul></div>';
    $output .= drupal_render($vars['secondary']);
  }

  return $output;
}

function mobile_jquery_menu_breadcrumb_alter(&$active_trail, $item) {
  foreach ($active_trail as $trail => $crumb) {
    $active_trail[$trail]['localized_options']['attributes']['data-role'] = 'button';
  }
}

/**
 * Returns HTML for the menu overview form into a table.
 *
 * @param $vars
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @ingroup themeable
 */
function mobile_jquery_menu_overview_form($vars) {
  $form = $vars['form'];

  //drupal_add_tabledrag('menu-overview', 'match', 'parent', 'menu-plid', 'menu-plid', 'menu-mlid', TRUE, MENU_MAX_DEPTH - 1);
  //drupal_add_tabledrag('menu-overview', 'order', 'sibling', 'menu-weight');

  $header = array(
    t('Menu link'),
    array('data' => t('Enabled'), 'class' => array('checkbox')),
    t('Weight'),
    array('data' => t('Operations'), 'colspan' => '3'),
  );

  $rows = array();
  foreach (element_children($form) as $mlid) {
    if (isset($form[$mlid]['hidden'])) {
      $element = &$form[$mlid];
      // Build a list of operations.
      $operations = array();
      foreach (element_children($element['operations']) as $op) {
        $element['operations'][$op]['#attributes']['data-role'] = 'button';
        $element['operations'][$op]['#attributes']['data-icon'] = $op;
        $element['operations'][$op]['#attributes']['data-iconpos'] = 'notext';
        $operations[] = array('data' => drupal_render($element['operations'][$op]), 'class' => array('menu-operations'));
      }
      while (count($operations) < 2) {
        $operations[] = '';
      }

      // Add special classes to be used for tabledrag.js.
      $element['plid']['#attributes']['class'] = array('menu-plid');
      $element['mlid']['#attributes']['class'] = array('menu-mlid');
      $element['weight']['#attributes']['class'] = array('menu-weight');

      // Change the parent field to a hidden. This allows any value but hides the field.
      $element['plid']['#type'] = 'hidden';

      $row = array();
      $row[] = theme('indentation', array('size' => $element['#item']['depth'] - 1)) . drupal_render($element['title']);
      $row[] = array('data' => drupal_render($element['hidden']), 'class' => array('checkbox', 'menu-enabled'));
      $row[] = drupal_render($element['weight']) . drupal_render($element['plid']) . drupal_render($element['mlid']);
      $row = array_merge($row, $operations);

      $row = array_merge(array('data' => $row), $element['#attributes']);
/*       $row['class'][] = 'draggable'; */
      $rows[] = $row;
    }
  }
  $output = '';
  if (empty($rows)) {
    $rows[] = array(array('data' => $form['#empty_text'], 'colspan' => '7'));
  }
  $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'menu-overview')));
  $output .= drupal_render_children($form);
  return $output;
}

