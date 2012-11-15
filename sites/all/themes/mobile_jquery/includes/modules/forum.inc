<?php
/**
 * @file
 * Contains theme override functions and preprocess functions for the mobile_jquery theme.
 */

/**
 * Returns HTML for a forum form.
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
function mobile_jquery_forum_form($vars) {
  return drupal_render_children($vars['form']);
}

