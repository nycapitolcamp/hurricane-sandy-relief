<?php
/**
 * @file
 * Contains theme override functions and preprocess functions for the mobile_jquery theme.
 */

/**
 * Returns HTML for an individual feed item for display in the block.
 *
 * @param $vars
 *   An associative array containing:
 *   - item: The item to be displayed.
 *   - feed: Not used.
 *
 * @ingroup themeable
 */
function mobile_jquery_aggregator_block_item($vars) {
  // Display the external link to the item.
  
  $attributes = array(
    'rel' => 'external',
  );
  
  return l(check_plain($vars['item']->title), check_url($vars['item']->link), array('attributes' => $attributes));
}

/**
 * Returns HTML for the aggregator page list form for assigning categories.
 *
 * @param $vars
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @ingroup themeable
 */
function mobile_jquery_aggregator_categorize_items($vars) {

}
