<?php
/**
 * @file
 * Contains theme override functions and preprocess functions for the mobile_jquery theme.
 */

/**
 * Returns HTML for a list of recent comments to be displayed in the comment block.
 *
 * @ingroup themeable
 */
function mobile_jquery_comment_block() {
  $items = array();
  $number = variable_get('comment_block_count', 10);
  foreach (comment_get_recent($number) as $comment) {
    $items[] = l($comment->subject . '&nbsp;<span>- ' . t('@time ago', array('@time' => format_interval(REQUEST_TIME - $comment->changed))) . '</span>', 'comment/' . $comment->cid, array('html' => TRUE));
  }

  if ($items) {
    return theme('item_list', array('items' => $items, 'title' => 'Recent Comments'));
  }
  else {
    return t('No comments available.');
  }
}

/**
 * Returns HTML for a "you can't post comments" notice.
 *
 * @param $vars
 *   An associative array containing:
 *   - node: The comment node.
 *
 * @ingroup themeable
 */
function mobile_jquery_comment_post_forbidden($vars) {
  $node = $vars['node'];
  global $user;

  // Since this is expensive to compute, we cache it so that a page with many
  // comments only has to query the database once for all the links.
  $authenticated_post_comments = &drupal_static(__FUNCTION__, NULL);

  if (!$user->uid) {
    if (!isset($authenticated_post_comments)) {
      // We only output a link if we are certain that users will get permission
      // to post comments by logging in.
      $comment_roles = user_roles(TRUE, 'post comments');
      $authenticated_post_comments = isset($comment_roles[DRUPAL_AUTHENTICATED_RID]);
    }

    if ($authenticated_post_comments) {
      // We cannot use drupal_get_destination() because these links
      // sometimes appear on /node and taxonomy listing pages.
      if (variable_get('comment_form_location_' . $node->type, COMMENT_FORM_BELOW) == COMMENT_FORM_SEPARATE_PAGE) {
        $destination = array('destination' => "comment/reply/$node->nid");//#comment-form");
      }
      else {
        $destination = array('destination' => "node/$node->nid");//#comment-form");
      }

      if (variable_get('user_register', USER_REGISTER_VISITORS_ADMINISTRATIVE_APPROVAL)) {
        // Users can register themselves.
        return t('<a href="@login">Log in</a> or <a href="@register">register</a> to post comments', array('@login' => url('user/login', array('query' => $destination)), '@register' => url('user/register', array('query' => $destination))));
      }
      else {
        // Only admins can add new users, no public registration.
        return t('<a href="@login">Log in</a> to post comments', array('@login' => url('user/login', array('query' => $destination))));
      }
    }
  }
}
