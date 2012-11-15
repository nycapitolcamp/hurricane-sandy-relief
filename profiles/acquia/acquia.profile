<?php

// == Acuquia branding =========================================================

/**
 * Implements hook_init().
 */
function acquia_init() {
  global $conf;

  // Use this early opportunity to brand the install/runtime experience.
  // Once the generic theme settings are saved, or a custom theme's settings
  // are saved to override it, this will not be effective anymore, which is
  // intended.
  if (empty($conf['theme_settings'])) {
    $conf['theme_settings'] = array(
      'default_logo' => 0,
      // Default to different logos depending on whether Drupal is installed or not.
      'logo_path' => empty($conf['site_name']) ? 'profiles/acquia/AcquiaDrupalLogoInstaller.png' : 'profiles/acquia/AcquiaDrupalLogo.png',
    );
  }
}

/**
 * Implements hook_install_tasks_alter().
 */
function acquia_install_tasks_alter(&$tasks, $install_state) {
  // Preselect the English language, so users can skip the language selection
  // form. We do not ship other languages with Acquia Drupal at this point.
  if (!isset($_GET['locale'])) {
    $_POST['locale'] = 'en';
  }
}

// == Configuration UI =========================================================

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
function acquia_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = $_SERVER['SERVER_NAME'];

  $form['site_information']['acquia_identifier'] = array(
    '#title' => st('Acquia subscription identifier'),
    '#description' => st('If you have an <a href="@url">Acquia Network subscription</a>, please enter the subscription identifier. You can also provide it later at Administer > Configuration > Acquia Network settings.', array('@url' => 'http://network.acquia.com/network/dashboard/subscription')),
    '#type' => 'textfield',
    '#required' => FALSE,
  );
  $form['site_information']['acquia_key'] = array(
    '#title' => st('Acquia subscription key'),
    '#description' => st('If you have an <a href="@url">Acquia Network subscription</a>, please enter the subscription key. You can also provide it later at Administer > Configuration > Acquia Network settings.', array('@url' => 'http://network.acquia.com/network/dashboard/subscription')),
    '#type' => 'textfield',
    '#required' => FALSE,
  );

  // Add both existing submit function and our submit function,
  // since adding just ours cancels the automated discovery of the original.
  $form['#validate'] = array('acquia_configure_form_validate', 'install_configure_form_validate');
  $form['#submit'] = array('acquia_configure_form_submit', 'install_configure_form_submit');
}

/**
 * Custom validation handler for Acquia Drupal install.
 */
function acquia_configure_form_validate($form, &$form_state) {
  // Check credentials only if they provided.
  $form_state['values']['acquia_identifier'] = trim($form_state['values']['acquia_identifier']);
  $form_state['values']['acquia_key'] = trim($form_state['values']['acquia_key']);
  if (!empty($form_state['values']['acquia_identifier']) && !empty($form_state['values']['acquia_key'])) {
    if (!acquia_agent_valid_credentials($form_state['values']['acquia_identifier'], $form_state['values']['acquia_key'], acquia_agent_settings('acquia_network_address'))) {
      form_error($form, acquia_agent_connection_error_message());
    }
  }
}

/**
 * Custom submission handler for Acquia Drupal install.
 */
function acquia_configure_form_submit($form, &$form_state) {
  variable_set('acquia_identifier', $form_state['values']['acquia_identifier']);
  variable_set('acquia_key', $form_state['values']['acquia_key']);
}

// == Automated install tasks ==================================================

/**
 * Implements hook_install_tasks().
 */
function acquia_install_tasks($install_state) {
  return array(
    // Just a hidden task callback.
    'acquia_profile_setup' => array(),
  );
}

/**
 * Installer task callback.
 */
function acquia_profile_setup() {
  global $language;

  // Add a node describing how to get started with Acquia Drupal
  $welcome_file = 'profiles/acquia/' . $language->language . '/welcome.txt';
  if (!file_exists($welcome_file)) {
    drupal_set_message(t('Could not find file @filepath.', array('@filepath' => $welcome_file)), 'error');
    $welcome_file = 'profiles/acquia/en/welcome.txt';
  }
  if ($welcome_node = _acquia_profile_create_node($welcome_file, 'page')) {
    node_save($welcome_node);
    variable_set('acquia_welcome', $welcome_node->nid);
  }
  else {
    drupal_set_message(t('The file @filepath could not be read. The welcome message will not be generated.', array('@filepath' => $welcome_file)), 'error');
  }
}

/**
 * Creates a node from the specified filename.
 *
 * The node body will contain the contents of the file. All relative links must
 * be identified within the file so they can be mapped to paths appropriate for
 * the installation.
 *
 * The relative links are identified in the file by surrounding the actual
 * link with double square brackets. For example:
 *
 * <a href="[[admin]]">Admin page</a>
 *
 * @param $filename
 *   The name of the file to retrieve the text from.
 * @param $page_type
 *   The type of node to create.
 */
function _acquia_profile_create_node($filename, $page_type) {
  $contents = trim(file_get_contents($filename));
  if (!$contents) {
    return null;
  }

  // Grab the title from the document and then remove the title so it
  // isn't shown in the title and the body. The title will be encoded
  // in the document in the following form:
  // <h1 [class="..."]>{TITLE}</h1>
  $title_regexp = "/[\<]h1(\s*[^=\>]*=\"[^\"]*\")*\s*[\>](.*)\<\/h1\>/i";
  if (preg_match($title_regexp, $contents, $match)) {
    $title = $match[count($match) - 1];
    // Remove the title from the body of the document.
    $contents = preg_replace($title_regexp, '', $contents);
  }

  // Replace all local links with the full path.
  $options = array();
  $options['alias'] = TRUE;
  $link_regexp = "/(\[\[)([\/?\w+\-*]+)(\]\])/e";
  $contents = preg_replace($link_regexp, 'check_url(url("\2", $options))', $contents);
  $node = new stdClass();
  $node->title = $title;
  $node->body['und'][0]['value'] = $contents;
  $node->body['und'][0]['summary'] = $contents;
  $node->body['und'][0]['format'] = 'full_html';
  $node->uid = 1;
  $node->type = $page_type;
  $node->status = 1;
  $node->promote = 1;
  return $node;
}
