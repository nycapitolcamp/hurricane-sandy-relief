<?php
/**
 * @file
 * Contains theme override functions and preprocess functions for the mobile_jquery theme.
 */

/**
 * Returns HTML for the entire dashboard.
 *
 * @param $vars
 *   An associative array containing:
 *   - element: A render element containing the properties of the dashboard
 *     region element, #dashboard_region and #children.
 *
 * @ingroup themeable
 */
function mobile_jquery_dashboard($vars) {
  extract($vars);
  drupal_add_css(drupal_get_path('module', 'dashboard') . '/dashboard.css');
  return '<div id="dashboard" class="clearfix">' . $element['#children'] . '</div>';
}

/**
 * Returns HTML for the non-customizable part of the dashboard page.
 *
 * @param $vars
 *   An associative array containing:
 *   - element: A render element containing a #message.
 *
 * @ingroup themeable
 */
function mobile_jquery_dashboard_admin($vars) {
  // We only return a simple help message, since the actual content of the page
  // will be populated via the dashboard regions in dashboard_page_build().
  return '<div class="customize-dashboard js-hide">' . $vars['element']['#message'] . '</div>';
}

/**
 * Returns HTML for a generic dashboard region.
 *
 * @param $vars
 *   An associative array containing:
 *   - element: A render element containing the properties of the dashboard
 *     region element, #dashboard_region and #children.
 *
 * @ingroup themeable
 */
function mobile_jquery_dashboard_region($vars) {
  extract($vars);
  $output = '<div id="' . $element['#dashboard_region'] . '" class="dashboard-region">';
  $output .= '<div class="region clearfix">';
  $output .= $element['#children'];
  // Closing div.region
  $output .= '</div>';
  // Closing div.dashboard-region
  $output .= '</div>';
  return $output;
}

/**
 * Returns HTML for a set of disabled blocks, for display in dashboard customization mode.
 *
 * @param $vars
 *   An associative array containing:
 *   - blocks: An array of block objects from _block_rehash().
 *
 * @ingroup themeable
 */
function mobile_jquery_dashboard_disabled_blocks($vars) {
  extract($vars);
  $output = '<div class="canvas-content"><p>' . t('Drag and drop these blocks to the columns below. Changes are automatically saved. More options are available on the <a href="@dashboard-url">configuration page</a>. ', array('@dashboard-url' => url('admin/dashboard/configure'))) . '</p>';
  $output .= '<div id="disabled-blocks"><div class="region disabled-blocks clearfix">';
  foreach ($blocks as $block) {
    $output .= theme('dashboard_disabled_block', array('block' => $block));
  }
  $output .= '<div class="clearfix"></div>';
  $output .= '<p class="dashboard-add-other-blocks">' . l(t('Add other blocks'), 'admin/dashboard/configure') . '</p>';
  $output .= '</div></div></div>';
  return $output;
}

/**
 * Returns HTML for a disabled block, for display in dashboard customization mode.
 *
 * @param $vars
 *   An associative array containing:
 *   - block: A block object from _block_rehash().
 *
 * @ingroup themeable
 */
function mobile_jquery_dashboard_disabled_block($vars) {
  extract($vars);
  $output = "";
  if (isset($block)) {
    $output .= '<div id="block-' . $block['module'] . '-' . $block['delta']
   . '" class="disabled-block block block-' . $block['module'] . '-' . $block['delta']
   . ' module-' . $block['module'] . ' delta-' . $block['delta'] . '">'
   . '<h2>' . (!empty($block['title']) && $block['title'] != '<none>' ? check_plain($block['title']) : check_plain($block['info'])) . '</h2>'
   . '<div class="content"></div>'
   . '</div>';
  }
  return $output;
}
