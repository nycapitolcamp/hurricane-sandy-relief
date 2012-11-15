<?php
/**
 * @file
 * Contains theme override functions and preprocess functions for the mobile_jquery theme.
 */

/**
 * Returns HTML for a link to the more extensive filter tips.
 *
 * @ingroup themeable
 */
function mobile_jquery_filter_tips_more_info() {
  $options = array(
    'attributes' => array(
      'data-rel' => 'dialog',
      'data-transition' => 'pop',
      'data-role' => 'button',
      'data-inline' => 'true',
    ), 
  );
  return '<p>' . l(t('More information about text formats'), 'filter/tips', $options) . '</p>';
}

/**
 * Returns HTML for a set of filter tips.
 *
 * @param $vars
 *   An associative array containing:
 *   - tips: An array containing descriptions and a CSS id in the form of
 *     'module-name/filter-id' (only used when $long is TRUE) for each
 *     filter in one or more text formats. Example:
 *     @code
 *       array(
 *         'Full HTML' => array(
 *           0 => array(
 *             'tip' => 'Web page addresses and e-mail addresses turn into links automatically. ',
 *             'id' => 'filter/2',
 *           ),
 *         ),
 *       );
 *     @endcode
 *   - long: (optional) Whether the passed-in filter tips contain extended
 *     explanations, i.e. intended to be output on the path 'filter/tips'
 *     (TRUE), or are in a short format, i.e. suitable to be displayed below a
 *     form element. Defaults to FALSE.
 *
 * @see _filter_tips()
 * @ingroup themeable
 */
function mobile_jquery_filter_tips($vars) {
  $tips = $vars['tips'];
  $long = $vars['long'];
  $output = '';

  $multiple = count($tips) > 1;
  if ($multiple) {
    $output = '<h2>' . t('Text Formats') . '</h2>';
  }

  if (count($tips)) {
    if ($multiple) {
      $output .= '<div class="compose-tips">';
    }
    foreach ($tips as $name => $tiplist) {
      if ($multiple) {
        $output .= '<div class="filter-type filter-' . drupal_html_class($name) . '">';
        $output .= '<h3>' . $name . '</h3>';
      }

      if (count($tiplist) > 0) {
        $output .= '<ul class="tips">';
        foreach ($tiplist as $tip) {
          $output .= '<li' . ($long ? ' id="filter-' . str_replace("/", "-", $tip['id']) . '">' : '>') . $tip['tip'] . '</li>';
        }
        $output .= '</ul>';
      }

      if ($multiple) {
        $output .= '</div>';
      }
    }
    if ($multiple) {
      $output .= '</div>';
    }
  }

  return $output;
}

/**
 * Returns HTML for guidelines for a text format.
 *
 * @param $vars
 *   An associative array containing:
 *   - format: An object representing a text format.
 *
 * @ingroup themeable
 */
function mobile_jquery_filter_guidelines($vars) {
  $format = $vars['format'];
  $attributes['class'][] = 'filter-guidelines-item';
  $attributes['class'][] = 'filter-guidelines-' . $format->format;
  $output = '<div' . drupal_attributes($attributes) . '>';
  $output .= '<h3>' . check_plain($format->name) . '</h3>';
  $output .= theme('filter_tips', array('tips' => _filter_tips($format->format, FALSE)));
  $output .= '</div>';
  return $output;
}

/**
 * Returns HTML for the text format administration overview form.
 *
 * @param $vars
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @ingroup themeable
 */
function mobile_jquery_filter_admin_overview($vars) {
  $form = $vars['form'];

  $rows = array();
  foreach (element_children($form['formats']) as $id) {
    $form['formats'][$id]['weight']['#attributes']['class'] = array('text-format-order-weight');
    $form['formats'][$id]['configure']['#attributes'] += array('data-role' => 'button', 'data-icon' => 'configure', 'data-iconpos' => 'notext');
    $form['formats'][$id]['disable']['#attributes'] += array('data-role' => 'button', 'data-icon' => 'delete', 'data-iconpos' => 'notext');
    $rows[] = array(
      'data' => array(
        drupal_render($form['formats'][$id]['name']),
        drupal_render($form['formats'][$id]['roles']),
        drupal_render($form['formats'][$id]['weight']),
        drupal_render($form['formats'][$id]['configure']),
        drupal_render($form['formats'][$id]['disable']),
      ),
/*       'class' => array('draggable'), */
    );
  }
  $header = array(t('Name'), t('Roles'), t('Weight'), array('data' => t('Operations'), 'colspan' => 2));
  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'text-format-order')));
  $output .= drupal_render_children($form);

/*   drupal_add_tabledrag('text-format-order', 'order', 'sibling', 'text-format-order-weight'); */

  return $output;
}

/**
 * Returns HTML for a text format's filter order form.
 *
 * @param $vars
 *   An associative array containing:
 *   - element: A render element representing the form.
 *
 * @ingroup themeable
 */
function mobile_jquery_filter_admin_format_filter_order($vars) {
  $element = $vars['element'];

  // Filter order (tabledrag).
  $rows = array();
  foreach (element_children($element, TRUE) as $name) {
    $element[$name]['weight']['#attributes']['class'][] = 'filter-order-weight';
    $rows[] = array(
      'data' => array(
        drupal_render($element[$name]['filter']),
        drupal_render($element[$name]['weight']),
      ),
/*       'class' => array('draggable'), */
    );
  }
  $output = drupal_render_children($element);
  $output .= theme('table', array('rows' => $rows, 'attributes' => array('id' => 'filter-order')));
/*   drupal_add_tabledrag('filter-order', 'order', 'sibling', 'filter-order-weight', NULL, NULL, TRUE); */

  return $output;
}

/**
 * Returns HTML for a text format-enabled form element.
 *
 * @param $vars
 *   An associative array containing:
 *   - element: A render element containing #children and #description.
 *
 * @ingroup themeable
 */
function mobile_jquery_text_format_wrapper($vars) {
  $element = $vars['element'];
  $output = '<div class="text-format-wrapper">';
  $output .= $element['#children'];
  if (!empty($element['#description'])) {
    $output .= '<div class="description">' . $element['#description'] . '</div>';
  }
  $output .= "</div>\n";

  return $output;
}