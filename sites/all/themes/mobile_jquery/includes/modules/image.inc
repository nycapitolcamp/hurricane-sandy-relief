<?php
/**
 * @file
 * Contains theme override functions and preprocess functions for the mobile_jquery theme.
 */

/**
 * Returns HTML for the page containing the list of image styles.
 *
 * @param $vars
 *   An associative array containing:
 *   - styles: An array of all the image styles returned by image_get_styles().
 *
 * @see image_get_styles()
 * @ingroup themeable
 */
function mobile_jquery_image_style_list($vars) {
  $styles = $vars['styles'];

  $header = array(t('Style name'), t('Settings'), array('data' => t('Operations'), 'colspan' => 3));
  $rows = array();
  foreach ($styles as $style) {
    $row = array();
    $row[] = l($style['name'], 'admin/config/media/image-styles/edit/' . $style['name']);
    $link_attributes = array(
      'attributes' => array(
        'class' => array('image-style-link'),
      ),
    );
    if ($style['storage'] == IMAGE_STORAGE_NORMAL) {
      $row[] = t('Custom');
      $row[] = l(t('edit'), 'admin/config/media/image-styles/edit/' . $style['name'], $link_attributes);
      $row[] = l(t('delete'), 'admin/config/media/image-styles/delete/' . $style['name'], $link_attributes);
    }
    elseif ($style['storage'] == IMAGE_STORAGE_OVERRIDE) {
      $row[] = t('Overridden');
      $row[] = l(t('edit'), 'admin/config/media/image-styles/edit/' . $style['name'], $link_attributes);
      $row[] = l(t('revert'), 'admin/config/media/image-styles/revert/' . $style['name'], $link_attributes);
    }
    else {
      $row[] = t('Default');
      $row[] = l(t('edit'), 'admin/config/media/image-styles/edit/' . $style['name'], $link_attributes);
      $row[] = '';
    }
    $rows[] = $row;
  }

  if (empty($rows)) {
    $rows[] = array(array(
      'colspan' => 4,
      'data' => t('There are currently no styles. <a href="!url">Add a new one</a>. ', array('!url' => url('admin/config/media/image-styles/add'))),
    ));
  }

  return theme('table', array('header' => $header, 'rows' => $rows));
}

/**
 * Returns HTML for a listing of the effects within a specific image style.
 *
 * @param $vars
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @ingroup themeable
 */
function mobile_jquery_image_style_effects($vars) {
  $form = $vars['form'];

  $rows = array();

  foreach (element_children($form) as $key) {
    $row = array();
    $form[$key]['weight']['#attributes']['class'] = array('image-effect-order-weight');
    if (is_numeric($key)) {
      $summary = drupal_render($form[$key]['summary']);
      $row[] = drupal_render($form[$key]['label']) . (empty($summary) ? '' : ' ' . $summary);
      $row[] = drupal_render($form[$key]['weight']);
      $row[] = drupal_render($form[$key]['configure']);
      $row[] = drupal_render($form[$key]['remove']);
    }
    else {
      // Add the row for adding a new image effect.
      $row[] = '<div class="image-style-new">' . drupal_render($form['new']['new']) . drupal_render($form['new']['add']) . '</div>';
      $row[] = drupal_render($form['new']['weight']);
      $row[] = array('data' => '', 'colspan' => 2);
    }

    if (!isset($form[$key]['#access']) || $form[$key]['#access']) {
      $rows[] = array(
        'data' => $row,
        'class' => /* !empty($form[$key]['weight']['#access']) || $key == 'new' ? array('draggable') : */ array(),
      );
    }
  }

  $header = array(
    t('Effect'),
    t('Weight'),
    array('data' => t('Operations'), 'colspan' => 2),
  );

  if (count($rows) == 1 && $form['new']['#access']) {
    array_unshift($rows, array(array(
      'data' => t('There are currently no effects in this style. Add one by selecting an option below.'),
      'colspan' => 4,
    )));
  }

  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'image-style-effects')));
/*   drupal_add_tabledrag('image-style-effects', 'order', 'sibling', 'image-effect-order-weight'); */
  return $output;
}

/**
 * Returns HTML for a preview of an image style.
 *
 * @param $vars
 *   An associative array containing:
 *   - style: The image style array being previewed.
 *
 * @ingroup themeable
 */
function mobile_jquery_image_style_preview($vars) {
  $style = $vars['style'];

  $sample_image = variable_get('image_style_preview_image', drupal_get_path('module', 'image') . '/sample.png');
  $sample_width = 160;
  $sample_height = 160;

  // Set up original file information.
  $original_path = $sample_image;
  $original_image = image_get_info($original_path);
  if ($original_image['width'] > $original_image['height']) {
    $original_width = min($original_image['width'], $sample_width);
    $original_height = round($original_width / $original_image['width'] * $original_image['height']);
  }
  else {
    $original_height = min($original_image['height'], $sample_height);
    $original_width = round($original_height / $original_image['height'] * $original_image['width']);
  }
  $original_attributes = array_intersect_key($original_image, array('width' => '', 'height' => ''));
  $original_attributes['style'] = 'width: ' . $original_width . 'px; height: ' . $original_height . 'px;';

  // Set up preview file information.
  $preview_file = image_style_path($style['name'], $original_path);
  if (!file_exists($preview_file)) {
    image_style_create_derivative($style, $original_path, $preview_file);
  }
  $preview_image = image_get_info($preview_file);
  if ($preview_image['width'] > $preview_image['height']) {
    $preview_width = min($preview_image['width'], $sample_width);
    $preview_height = round($preview_width / $preview_image['width'] * $preview_image['height']);
  }
  else {
    $preview_height = min($preview_image['height'], $sample_height);
    $preview_width = round($preview_height / $preview_image['height'] * $preview_image['width']);
  }
  $preview_attributes = array_intersect_key($preview_image, array('width' => '', 'height' => ''));
  $preview_attributes['style'] = 'width: ' . $preview_width . 'px; height: ' . $preview_height . 'px;';

  // In the previews, timestamps are added to prevent caching of images.
  $output = '<div class="image-style-preview preview clearfix">';

  // Build the preview of the original image.
  $original_url = file_create_url($original_path);
  $output .= '<div class="preview-image-wrapper">';
  $output .= t('original') . ' (' . l(t('view actual size'), $original_url) .')';
  $output .= '<div class="preview-image original-image" style="' . $original_attributes['style'] . '">';
  $output .= '<a href="' . $original_url . '">' . theme('image', array('path' => $original_path, 'alt' => t('Sample original image'), 'title' => '', 'attributes' => $original_attributes)) . '</a>';
  $output .= '<div class="height" style="height: ' . $original_height . 'px"><span>' . $original_image['height'] . 'px</span></div>';
  $output .= '<div class="width" style="width: ' . $original_width . 'px"><span>' . $original_image['width'] . 'px</span></div>';
  $output .= '</div>'; // End preview-image.
  $output .= '</div>'; // End preview-image-wrapper.

  // Build the preview of the image style.
  $preview_url = file_create_url($preview_file) . '?cache_bypass=' . REQUEST_TIME;
  $output .= '<div class="preview-image-wrapper">';
  $output .= check_plain($style['name']) . ' (' . l(t('view actual size'), file_create_url($preview_file) . '?' . time()) .')';
  $output .= '<div class="preview-image modified-image" style="' . $preview_attributes['style'] . '">';
  $output .= '<a href="' . file_create_url($preview_file) . '?' . time() . '">' . theme('image', array('path' => $preview_url, 'alt' => t('Sample modified image'), 'title' => '', 'attributes' => $preview_attributes)) . '</a>';
  $output .= '<div class="height" style="height: ' . $preview_height . 'px"><span>' . $preview_image['height'] . 'px</span></div>';
  $output .= '<div class="width" style="width: ' . $preview_width . 'px"><span>' . $preview_image['width'] . 'px</span></div>';
  $output .= '</div>'; // End preview-image.
  $output .= '</div>'; // End preview-image-wrapper.

  $output .= '</div>'; // End image-style-preview.

  return $output;
}

/**
 * Returns HTML for a 3x3 grid of checkboxes for image anchors.
 *
 * @param $vars
 *   An associative array containing:
 *   - element: A render element containing radio buttons.
 *
 * @ingroup themeable
 */
function mobile_jquery_image_anchor($vars) {
  $element = $vars['element'];

  $rows = array();
  $row = array();
  foreach (element_children($element) as $n => $key) {
    $element[$key]['#attributes']['title'] = $element[$key]['#title'];
    unset($element[$key]['#title']);
    $row[] = drupal_render($element[$key]);
    if ($n % 3 == 3 - 1) {
      $rows[] = $row;
      $row = array();
    }
  }

  return theme('table', array('header' => array(), 'rows' => $rows, 'attributes' => array('class' => array('image-anchor'))));
}

/**
 * Returns HTML for a summary of an image resize effect.
 *
 * @param $vars
 *   An associative array containing:
 *   - data: The current configuration for this resize effect.
 *
 * @ingroup themeable
 */
function mobile_jquery_image_resize_summary($vars) {
  $data = $vars['data'];

  if ($data['width'] && $data['height']) {
    return check_plain($data['width']) . 'x' . check_plain($data['height']);
  }
  else {
    return ($data['width']) ? t('width @width', array('@width' => $data['width'])) : t('height @height', array('@height' => $data['height']));
  }
}

/**
 * Returns HTML for a summary of an image scale effect.
 *
 * @param $vars
 *   An associative array containing:
 *   - data: The current configuration for this scale effect.
 *
 * @ingroup themeable
 */
function mobile_jquery_image_scale_summary($vars) {
  $data = $vars['data'];
  return theme('image_resize_summary', array('data' => $data)) . ' ' . ($data['upscale'] ? '(' . t('upscaling allowed') .')' : '');
}

/**
 * Returns HTML for a summary of an image crop effect.
 *
 * @param $vars
 *   An associative array containing:
 *   - data: The current configuration for this crop effect.
 *
 * @ingroup themeable
 */
function mobile_jquery_image_crop_summary($vars) {
  return theme('image_resize_summary', $vars);
}

/**
 * Returns HTML for a summary of an image rotate effect.
 *
 * @param $vars
 *   An associative array containing:
 *   - data: The current configuration for this rotate effect.
 *
 * @ingroup themeable
 */
function mobile_jquery_image_rotate_summary($vars) {
  $data = $vars['data'];
  return ($data['random']) ? t('random between -@degrees&deg and @degrees&deg', array('@degrees' => str_replace('-', '', $data['degrees']))) : t('@degrees&deg', array('@degrees' => $data['degrees']));
}

/**
 * Returns HTML for an image field widget.
 *
 * @param $vars
 *   An associative array containing:
 *   - element: A render element representing the image field widget.
 *
 * @ingroup themeable
 */
function mobile_jquery_image_widget($vars) {
  $element = $vars['element'];
  $output = '';
  $output .= '<div class="image-widget form-managed-file clearfix">';

  if (isset($element['preview'])) {
    $output .= '<div class="image-preview">';
    $output .= drupal_render($element['preview']);
    $output .= '</div>';
  }

  $output .= '<div class="image-widget-data">';
  if ($element['fid']['#value'] != 0) {
    $element['filename']['#markup'] .= ' <span class="file-size">(' . format_size($element['#file']->filesize) .')</span>';
  }
  $output .= drupal_render_children($element);
  $output .= '</div>';
  $output .= '</div>';

  return $output;
}

/**
 * Returns HTML for an image field formatter.
 *
 * @param $vars
 *   An associative array containing:
 *   - item: An array of image data.
 *   - image_style: An optional image style.
 *   - path: An array containing the link 'path' and link 'options'.
 *
 * @ingroup themeable
 */
function mobile_jquery_image_formatter($vars) {
  $item = $vars['item'];
  $image = array(
    'path' => $item['uri'],
    'alt' => $item['alt'],
  );
  // Do not output an empty 'title' attribute.
  if (drupal_strlen($item['title']) > 0) {
    $image['title'] = $item['title'];
  }

  if ($vars['image_style']) {
    $image['style_name'] = $vars['image_style'];
    $output = theme('image_style', $image);
  }
  else {
    $output = theme('image', $image);
  }

  if (!empty($vars['path']['path'])) {
    $path = $vars['path']['path'];
    $options = $vars['path']['options'];
    // When displaying an image inside a link, the html option must be TRUE.
    $options['html'] = TRUE;
    $output = l($output, $path, $options);
  }

  return $output;
}

/**
 * Returns HTML for an image using a specific image style.
 *
 * @param $vars
 *   An associative array containing:
 *   - style_name: The name of the style to be used to alter the original image.
 *   - path: The path of the image file relative to the Drupal files directory.
 *     This function does not work with images outside the files directory nor
 *     with remotely hosted images.
 *   - alt: The alternative text for text-based browsers.
 *   - title: The title text is displayed when the image is hovered in some
 *     popular browsers.
 *   - attributes: Associative array of attributes to be placed in the img tag.
 *
 * @ingroup themeable
 */
function mobile_jquery_image_style($vars) {
  $vars['path'] = image_style_url($vars['style_name'], $vars['path']);
  return theme('image', $vars);
}