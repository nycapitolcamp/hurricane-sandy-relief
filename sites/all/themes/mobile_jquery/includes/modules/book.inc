<?php
/**
 * @file
 * Contains theme override functions and preprocess functions for the mobile_jquery theme.
 */

/**
 * Returns HTML for a book administration form.
 *
 * @param $vars
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @see book_admin_table()
 * @ingroup themeable
 */
function mobile_jquery_book_admin_table($vars) {
  $form = $vars['form'];

  $header = array(t('Title'), t('Weight'), t('Parent'), array('data' => t('Operations'), 'colspan' => '3'));

  $rows = array();
  $destination = drupal_get_destination();
  $access = user_access('administer nodes');
  foreach (element_children($form) as $key) {
    $nid = $form[$key]['nid']['#value'];
    $href = $form[$key]['href']['#value'];

    // Add special classes to be used with tabledrag.js.
    $form[$key]['plid']['#attributes']['class'] = array('book-plid');
    $form[$key]['mlid']['#attributes']['class'] = array('book-mlid');
    $form[$key]['weight']['#attributes']['class'] = array('book-weight');

    $data = array(
      theme('indentation', array('size' => $form[$key]['depth']['#value'] - 2)) . drupal_render($form[$key]['title']),
      drupal_render($form[$key]['weight']),
      drupal_render($form[$key]['plid']) . drupal_render($form[$key]['mlid']),
      l(t('view'), $href, array('attributes' => array('data-role' => 'button', 'data-icon' => 'view', 'data-iconpos' => 'notext'))),
      $access ? l(t('edit'), 'node/' . $nid . '/edit', array('query' => $destination, 'attributes' => array('data-role' => 'button', 'data-icon' => 'edit', 'data-iconpos' => 'notext'))) : '&nbsp;',
      $access ? l(t('delete'), 'node/' . $nid . '/delete', array('query' => $destination, 'attributes' => array('data-role' => 'button', 'data-icon' => 'delete', 'data-iconpos' => 'notext')) )  : '&nbsp;',
    );
    $row = array('data' => $data);
    if (isset($form[$key]['#attributes'])) {
      $row = array_merge($row, $form[$key]['#attributes']);
    }
    
    $rows[] = $row;
  }

  return theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'book-outline')));
}

/**
 * Returns HTML for a link to a book title when used as a block title.
 *
 * @param $vars
 *   An associative array containing:
 *   - link: An array containing title, href and options for the link.
 *
 * @ingroup themeable
 */
function mobile_jquery_book_title_link($vars) {
  $link = $vars['link'];

  $link['options']['attributes']['class'] = array('book-title');

  return l($link['title'], $link['href'], $link['options']);
}
