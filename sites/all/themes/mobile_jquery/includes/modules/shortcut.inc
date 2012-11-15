<?php
/**
 * @file
 * Contains theme override functions and preprocess functions for the mobile_jquery theme.
 */

/**
 * Returns HTML for a shortcut set customization form.
 *
 * @param $vars
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @see shortcut_set_customize()
 * @ingroup themeable
 */
function mobile_jquery_shortcut_set_customize($vars) {
  $form = $vars['form'];
  $map = array('disabled' => t('Disabled'), 'enabled' => t('Enabled'));

  $rows = array();
  foreach (array('enabled', 'disabled') as $status) {
/*
    drupal_add_tabledrag('shortcuts', 'match', 'sibling', 'shortcut-status-select');
    drupal_add_tabledrag('shortcuts', 'order', 'sibling', 'shortcut-weight');
*/
    $rows[] = array(
      'data' => array(array(
        'colspan' => 5,
        'data' => '<strong>' . $map[$status] . '</strong>',
      )),
      'class' => array('shortcut-status', 'shortcut-status-' . $status),
    );

    foreach (element_children($form['shortcuts'][$status]) as $key) {
      $shortcut = &$form['shortcuts'][$status][$key];
      $row = array();
      $row[] = drupal_render($shortcut['name']);
      $row[] = drupal_render($shortcut['weight']);
      $row[] = drupal_render($shortcut['status']);
      $row[] = drupal_render($shortcut['edit']);
      $row[] = drupal_render($shortcut['delete']);
      $rows[] = array(
        'data' => $row,
        'class' => array(/* 'draggable' */),
      );
    }

    if ($status == 'enabled') {
      for ($i = 0; $i < shortcut_max_slots(); $i++) {
        $rows['empty-' . $i] = array(
          'data' => array(array(
            'colspan' => 5,
            'data' => '<em>' . t('Empty') . '</em>',
          )),
          'class' => array('shortcut-slot-empty'),
        );
      }
      $count_shortcuts = count(element_children($form['shortcuts'][$status]));
      if (!empty($count_shortcuts)) {
        for ($i = 0; $i < min($count_shortcuts, shortcut_max_slots()); $i++) {
          $rows['empty-' . $i]['class'][] = 'shortcut-slot-hidden';
        }
      }
    }
  }

  $header = array(t('Name'), t('Weight'), t('Status'), array('data' => t('Operations'), 'colspan' => 2));
  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'shortcuts')));
  $output .= drupal_render($form['actions']);
  $output = drupal_render_children($form) . $output;
  return $output;
}