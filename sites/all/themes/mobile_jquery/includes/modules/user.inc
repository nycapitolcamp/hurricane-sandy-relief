<?php
/**
 * @file
 * Contains theme override functions and preprocess functions for the mobile_jquery theme.
 */

/**
 * Returns HTML for a list of users.
 *
 * @param $vars
 *   An associative array containing:
 *   - users: An array with user objects. Should contain at least the name and
 *     uid.
 *   - title: (optional) Title to pass on to theme_item_list().
 *
 * @ingroup themeable
 */
function mobile_jquery_user_list($vars) {
  $users = $vars['users'];
  $title = $vars['title'];
  $items = array();

  if (!empty($users)) {
    foreach ($users as $user) {
      $items[] = theme('username', array('account' => $user));
    }
  }
  return theme('item_list', array('items' => $items, 'title' => $title));
}

/**
 * Returns HTML for the administer permissions page.
 *
 * @param $vars
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @ingroup themeable
 */
function mobile_jquery_user_admin_permissions($vars) {
  $form = $vars['form'];
  
  if (count($vars['form']['role_names']['#value']) == 1) {
    $output = mobile_jquery_user_admin_permissions_role($form);
  }
  else {
    $roles = user_roles();
    $output = '';
    $idx = 0;
    foreach (element_children($form['permission']) as $key) {
      if (is_numeric($key)) {
        if ($idx > 0) {
          $output .= '</div>';
        }
        $output .= '<div data-role="collapsible" data-collapsed="true">';
        $output .= '<h3>' . drupal_render($form['permission'][$key]) . '</h3>';
      }
      else {
        $output .= '<div data-role="collapsible" data-collapsed="true">';
  
        $output .= '<h3>' . strip_tags($form['permission'][$key]['#markup']) . '</h3>';
        foreach (element_children($form['checkboxes']) as $rid) {
          $form['checkboxes'][$rid][$key]['#title'] = $roles[$rid] . ': ' . strip_tags($form['permission'][$key]['#markup']);
          $output .= drupal_render($form['checkboxes'][$rid][$key]);
          
        }
        $output .= '</div>';
      }
    $idx++;
    }
  $output .= '</div>';
  }
  // We've rendered these already, no need to do it again.
  unset($form['permission']);
  unset($form['checkboxes']);
  unset($form['role_names']);
  
  // Render the rest of the form
  $output .= drupal_render_children($form);

  return $output;
  
}

function mobile_jquery_user_admin_permissions_role($form) {
  $roles = user_roles();
  
  $output = '';
$idx = 0;
  foreach (element_children($form['permission']) as $key) {

    if (is_numeric($key)) {
      if ($idx > 0) {
        $output .= '</div>';
      }
      $output .= '<div data-role="collapsible" data-collapsed="true">';

      $output .= '<h3>' . $form['permission'][$key]['#markup'] . '</h3>';
    }
    else {
      foreach (element_children($form['checkboxes']) as $rid) {
        $form['checkboxes'][$rid][$key]['#title'] = strip_tags($form['permission'][$key]['#markup']);
        $output .= '<div>' . drupal_render($form['checkboxes'][$rid][$key]) . '</div>';
        
      }

    }
    $idx++;
  }
  $output .= '</div>';
    
  return $output;
}

/**
 * Returns HTML for an individual permission description.
 *
 * @param $vars
 *   An associative array containing:
 *   - permission_item: An associative array representing the permission whose
 *     description is being themed. Useful keys include:
 *     - description: The text of the permission description.
 *     - warning: A security-related warning message about the permission (if
 *       there is one).
 *   - hide: A boolean indicating whether or not the permission description was
 *     requested to be hidden rather than shown.
 *
 * @ingroup themeable
 */
function mobile_jquery_user_permission_description($vars) {
  if (!$vars['hide']) {
    $description = array();
    $permission_item = $vars['permission_item'];
    if (!empty($permission_item['description'])) {
      $description[] = $permission_item['description'];
    }
    if (!empty($permission_item['warning'])) {
      $description[] = '<em class="permission-warning">' . $permission_item['warning'] . '</em>';
    }
    if (!empty($description)) {
      return implode(' ', $description);
    }
  }
}

/**
 * Returns HTML for the role order and new role form.
 *
 * @param $vars
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @ingroup themeable
 */
function mobile_jquery_user_admin_roles($vars) {
  $form = $vars['form'];

  $header = array(t('Name'), t('Weight'), array('data' => t('Operations'), 'colspan' => 2));
  foreach (element_children($form['roles']) as $rid) {
    $name = $form['roles'][$rid]['#role']->name;
    $row = array();
    if (in_array($rid, array(DRUPAL_ANONYMOUS_RID, DRUPAL_AUTHENTICATED_RID))) {
      $row[] = t('@name <em>(locked)</em>', array('@name' => $name));
      $row[] = drupal_render($form['roles'][$rid]['weight']);
      $row[] = '';
      $row[] = l(t('edit permissions'), 'admin/people/permissions/' . $rid, array('attributes' => array('data-role' => 'button', 'data-icon' => 'permissions', 'data-iconpos' => 'notext')));
    }
    else {
      $row[] = check_plain($name);
      $row[] = drupal_render($form['roles'][$rid]['weight']);
      $row[] = l(t('edit role'), 'admin/people/permissions/roles/edit/' . $rid, array('attributes' => array('data-role' => 'button', 'data-icon' => 'edit', 'data-iconpos' => 'notext')));
      $row[] = l(t('edit permissions'), 'admin/people/permissions/' . $rid, array('attributes' => array('data-role' => 'button', 'data-icon' => 'permissions', 'data-iconpos' => 'notext')));
    }
    $rows[] = array('data' => $row, 'class' => array(/* 'draggable' */));
  }
  $rows[] = array(array('data' => drupal_render($form['name']) . drupal_render($form['add']), 'colspan' => 4, 'class' => 'edit-name'));

/*   drupal_add_tabledrag('user-roles', 'order', 'sibling', 'role-weight'); */

  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'user-roles')));
  $output .= drupal_render_children($form);

  return $output;
}
