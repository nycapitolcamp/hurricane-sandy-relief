<?php
/**
 * @file
 * Contains theme override functions and preprocess functions for the mobile_jquery theme.
 */

/**
  * Implementation of hook form alter
  */


function mobile_jquery_form_search_block_form_alter(&$form, &$form_state) {
    $form['search_block_form']['#attributes']['data-type'] = 'search';
}
