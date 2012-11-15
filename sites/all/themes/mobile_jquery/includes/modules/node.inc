<?php
/**
 * @file
 * Contains theme override functions and preprocess functions for the mobile_jquery theme.
 */

/**
 * Returns HTML for a list of recent content.
 *
 * @param $vars
 *   An associative array containing:
 *   - nodes: An array of recent node objects.
 *
 * @ingroup themeable
 */
function mobile_jquery_node_recent_block($vars) {
  $rows = array();
  $output = '';

  $l_options = array('query' => drupal_get_destination(), 'attributes' => array('data-role' => 'button', 'data-icon' => '', 'data-iconpos' => 'notext'));
  foreach ($vars['nodes'] as $node) {
    $row = array();
    $row[] = array(
      'data' => theme('node_recent_content', array('node' => $node)),
      'class' => 'title-author',
    );
    $l_options['attributes']['data-icon'] = 'edit';
    $row[] = array(
      'data' => node_access('update', $node) ? l(t('edit'), 'node/' . $node->nid . '/edit', $l_options) : '',
      'class' => 'edit',
    );
    $l_options['attributes']['data-icon'] = 'delete';
    $row[] = array(
      'data' => node_access('delete', $node) ? l(t('delete'), 'node/' . $node->nid . '/delete', $l_options) : '',
      'class' => 'delete',
    );
    $rows[] = $row;
  }

  if ($rows) {
    $output = theme('table', array('rows' => $rows));
    if (user_access('access content overview')) {
      $output .= theme('more_link', array('url' => 'admin/content', 'title' => t('Show more content')));
    }
  }

  return $output;
}

/* Returns HTML for a node preview for display during node creation and editing.
 *
 * @param $vars
 *   An associative array containing:
 *   - node: The node object which is being previewed.
 *
 * @ingroup themeable
 */
function mobile_jquery_node_preview($vars) {
  $node = $vars['node'];

  $output = '<div class="preview">';

  $preview_trimmed_version = FALSE;

  $elements = node_view(clone $node, 'teaser');
  $trimmed = drupal_render($elements);
  $elements = node_view($node, 'full');
  $full = drupal_render($elements);

  // Do we need to preview trimmed version of post as well as full version?
  if ($trimmed != $full) {
    drupal_set_message(t('The trimmed version of your post shows what your post looks like when promoted to the main page or when exported for syndication.<span class="no-js"> You can insert the delimiter "&lt;!--break--&gt;" (without the quotes) to fine-tune where your post gets split.</span>'));
    $output .= '<h3>' . t('Preview trimmed version') . '</h3>';
    $output .= $trimmed;
    $output .= '<h3>' . t('Preview full version') . '</h3>';
    $output .= $full;
  }
  else {
    $output .= $full;
  }
  $output .= "</div>\n";

  return $output;
}

/**
 * Returns HTML for a node type description for the content type admin overview page.
 *
 * @param $vars
 *   An associative array containing:
 *   - name: The human-readable name of the content type.
 *   - type: An object containing the 'type' (machine name) and 'description' of
 *     the content type.
 *
 * @ingroup themeable
 */
function mobile_jquery_node_admin_overview($vars) {
  $name = $vars['name'];
  $type = $vars['type'];

  $output = check_plain($name);
  $output .= ' <small>' . t('(Machine name: @type)', array('@type' => $type->type)) . '</small>';
  $output .= '<div class="description">' . filter_xss_admin($type->description) . '</div>';
  return $output;
}
