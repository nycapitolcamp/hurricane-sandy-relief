<?php
/**
 *@file
 * Implements theme settings for mobile_jquery
 */
 
include_once(drupal_get_path('theme', 'mobile_jquery') . '/includes/mobile_jquery.inc');

/**
 * Implements hook_form_system_theme_settings_alter().
 *
 * @param $form
 *   Nested array of form elements that comprise the form.
 * @param $form_state
 *   A keyed array containing the current state of the form.
 */
function mobile_jquery_form_system_theme_settings_alter(&$form, &$form_state) {
  
    //Theming Styles
  $boolean_options  = array(
    'true' => t('True'),
    'false' => t('False'),
  );

  $theme_settings = array(
    'a' => t('Black'),
    'b' => t('Blue'),
    'c' => t('White'),
    'd' => t('Grey'),
    'e' => t('Yellow')
  );

  if (module_exists('jquerymobile')) {
    $theme_settings = array_merge($theme_settings, _jquerymobile_get_custom_themes());
  }

  
  $icon_options = array(
   'arrow-r' => t('Right arrow'),
   'arrow-l' => t('Left arrow'),
   'arrow-u' => t('Up arrow'),
   'arrow-d' => t('Down arrow'),
   'delete' => t('Delete'),
   'plus' => t('Plus'),
   'minus' => t('Minus'),
   'check' => t('Check'),
   'gear' => t('Gear'),
   'refresh' => t('Refresh'),
   'forward' => t('Forward'),
   'back' => t('Back'),
   'grid' => t('Grid'),
   'star' => t('Star'),
   'alert' => t('Alert'),
   'info' => t('Info'),
   'home' => t('Home'),
   'search' => t('Search'),
  );
  
  $position_options = array(
    'inline' => t('inline'),
    'fixed' => t('fixed'),
  );
  
  $use_global = mobile_jquery_theme_get_setting('use_global');
  
  $form['mobile_jquery_settings'] = array(
    '#type' => 'fieldset',
    '#weight' => -10,
    '#title' => t('jQuery Mobile Configuration'),
  );
  $form['mobile_jquery_settings']['rebuild_registry'] = array(
    '#type' => 'checkbox',
    '#title' => t('Rebuild theme registry for every page.'),
    '#description' => t('<em>Note: Not recommended for production use.</em>'),
    '#default_value' => mobile_jquery_theme_get_setting('rebuild_registry'),
  );
  $form['mobile_jquery_settings']['use_global'] = array(
    '#type'         => 'checkbox',
    '#title'        => t('Use a global color swatch'),
    '#description'  => t('This option allows all items to be set to the same swatch rather than set each item individually.'),
    '#default_value' => $use_global,
  );
  
  $form['mobile_jquery_settings']['viewport'] = array(
    '#type'         => 'checkbox',
    '#title'        => t('Use Viewport'),
    '#description'  => t('Add viewport to header.'),
    '#default_value' => mobile_jquery_theme_get_setting('viewport'),
    '#options' => array(
      TRUE,
      FALSE,
    ),
  );
    
// GLOBAL  
  $form['mobile_jquery_settings']['global_styles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Global Settings'),
    '#states' => array(
      'visible' => array(
        ':input[name="use_global"]' => array('checked' => TRUE),
      ),
    ),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE, 
  );
    $form['mobile_jquery_settings']['global_styles']['global_theme'] = array(
      '#type'         => 'select',
      '#title'        => t('Global Theme (data-theme)'),
      '#default_value' => mobile_jquery_theme_get_setting('global_theme'),
      '#options'      => $theme_settings,
    );
    $form['mobile_jquery_settings']['global_styles']['global_inset'] = array(
      '#type'         => 'radios',
      '#title'        => t('Inset Style Lists/Menus (data-inset)'),
      '#default_value' => mobile_jquery_theme_get_setting('global_inset'),
    '#options'      => $boolean_options,
    );
    $form['mobile_jquery_settings']['global_styles']['global_spliticon'] = array(
      '#type'         => 'select',
      '#title'        => t('Split Button Icon (data-split-icon)'),
      '#default_value' => mobile_jquery_theme_get_setting('global_spliticon'),
      '#options'      => $icon_options,
    );
    $form['mobile_jquery_settings']['global_styles']['global_icon'] = array(
      '#type'         => 'select',
      '#title'        => t('List/Menu Item Icon (data-icon)'),
      '#default_value' => mobile_jquery_theme_get_setting('global_icon'),
      '#options'      => $icon_options,
    );
    $form['mobile_jquery_settings']['global_styles']['global_header_data_position'] = array(
      '#type'         => 'select',
      '#title'        => t('Header Position (data-position)'),
      '#default_value' => mobile_jquery_theme_get_setting('global_header_data_position'),
      '#options'      => $position_options,
    );
    $form['mobile_jquery_settings']['global_styles']['global_footer_data_position'] = array(
      '#type'         => 'select',
      '#title'        => t('Footer Position (data-position)'),
      '#default_value' => mobile_jquery_theme_get_setting('global_footer_data_position'),
      '#options'      => $position_options,
    );
  
//ITEM LISTS  
  $form['mobile_jquery_settings']['item_list_styles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Item List settings'),
    '#states' => array(
      'visible' => array(
        ':input[name="use_global"]' => array('checked' => FALSE),
      ),
    ),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE, 
  );  
    
  $form['mobile_jquery_settings']['item_list_styles']['list_item_theme'] = array(
    '#type'         => 'select',
    '#title'        => t('Theme (data-theme)'),
    '#default_value' => mobile_jquery_theme_get_setting('list_item_theme'),
    '#options'      => $theme_settings,

  );
  $form['mobile_jquery_settings']['item_list_styles']['list_item_inset'] = array(
    '#type'         => 'radios',
    '#title'        => t('Inset Lists (data-inset)'),
    '#default_value' => mobile_jquery_theme_get_setting('list_item_inset'),
    '#options'      => $boolean_options,
  );
  $form['mobile_jquery_settings']['item_list_styles']['list_item_icon'] = array(
    '#type'         => 'select',
    '#title'        => t('List Item Icon (data-icon)'),
    '#default_value' => mobile_jquery_theme_get_setting('list_item_icon'),
    '#options'      => $icon_options,
  );
  $form['mobile_jquery_settings']['item_list_styles']['list_item_dividertheme'] = array(
    '#type'         => 'select',
    '#title'        => t('List Divider Theme (data-divider-theme)'),
    '#default_value' => mobile_jquery_theme_get_setting('list_item_dividertheme'),
    '#options'      => $theme_settings,
  );   
  $form['mobile_jquery_settings']['item_list_styles']['list_item_counttheme'] = array(
    '#type'         => 'select',
    '#title'        => t('Count Bubble Theme (data-count-theme)'),
    '#default_value' => mobile_jquery_theme_get_setting('list_item_counttheme'),
    '#options'      => $theme_settings,
  );  
  $form['mobile_jquery_settings']['item_list_styles']['list_item_splittheme'] = array(
    '#type'         => 'select',
    '#title'        => t('Split Button Theme (data-split-theme)'),
    '#default_value' => mobile_jquery_theme_get_setting('list_item_splittheme'),
    '#options'      => $theme_settings,
  );    
  $form['mobile_jquery_settings']['item_list_styles']['list_item_spliticon'] = array(
    '#type'         => 'select',
    '#title'        => t('Slit Button Icon (data-split-icon)'),
    '#default_value' => mobile_jquery_theme_get_setting('list_item_spliticon'),
    '#options'      => $icon_options,
  );
  
//MENU ITEM LIST
  $form['mobile_jquery_settings']['menu_item_list_styles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Menu Item Settings'),
    '#states' => array(
      'visible' => array(
        ':input[name="use_global"]' => array('checked' => FALSE),
      ),
    ),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE, 
  );  
    $form['mobile_jquery_settings']['menu_item_list_styles']['menu_item_theme'] = array(
      '#type'         => 'select',
      '#title'        => t('Theme (data-theme)'),
      '#default_value' => mobile_jquery_theme_get_setting('menu_item_theme'),
      '#options'      => $theme_settings,
    );  
    $form['mobile_jquery_settings']['menu_item_list_styles']['menu_item_inset'] = array(
      '#type'         => 'radios',
      '#title'        => t('Menu Item Inset (data-inset)'),
      '#default_value' => mobile_jquery_theme_get_setting('menu_item_inset'),
      '#options'      => $boolean_options,
    );
    $form['mobile_jquery_settings']['menu_item_list_styles']['menu_item_icon'] = array(
      '#type'         => 'select',
      '#title'        => t('Menu Item Icon (data-icon)'),
      '#default_value' => mobile_jquery_theme_get_setting('menu_item_icon'),
      '#options'      => $icon_options,
    );  
    $form['mobile_jquery_settings']['menu_item_list_styles']['menu_item_dividertheme'] = array(
      '#type'         => 'select',
      '#title'        => t('Menu Divider Theme (data-divider-theme)'),
      '#default_value' => mobile_jquery_theme_get_setting('menu_item_dividertheme'),
      '#options'      => $theme_settings,
    );   
    $form['mobile_jquery_settings']['menu_item_list_styles']['menu_item_counttheme'] = array(
      '#type'         => 'select',
      '#title'        => t('Count Bubble Theme (data-count-theme)'),
      '#default_value' => mobile_jquery_theme_get_setting('menu_item_counttheme'),
      '#options'      => $theme_settings,
    );  
    $form['mobile_jquery_settings']['menu_item_list_styles']['menu_item_splittheme'] = array(
      '#type'         => 'select',
      '#title'        => t('Split Button Theme (data-split-theme)'),
      '#default_value' => mobile_jquery_theme_get_setting('menu_item_splittheme'),
      '#options'      => $theme_settings,
    );
    $form['mobile_jquery_settings']['menu_item_list_styles']['menu_item_spliticon'] = array(
      '#type'         => 'select',
      '#title'        => t('Split Item Icon (data-split-icon)'),
      '#default_value' => mobile_jquery_theme_get_setting('menu_item_spliticon'),
      '#options'      => $icon_options,
    );  
    
//HEADER  
  $form['mobile_jquery_settings']['header_styles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Header Settings'),
    '#states' => array(
      'visible' => array(
        ':input[name="use_global"]' => array('checked' => FALSE),
      ),
    ),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE, 
  );    
    $form['mobile_jquery_settings']['header_styles']['header_data_theme'] = array(
      '#type'         => 'select',
      '#title'        => t('Theme (data-theme)'),
      '#default_value' => mobile_jquery_theme_get_setting('header_data_theme'),
      '#options'      => $theme_settings,
    );  
    $form['mobile_jquery_settings']['header_styles']['header_data_position'] = array(
      '#type'         => 'select',
      '#title'        => t('Position (data-position)'),
      '#default_value' => mobile_jquery_theme_get_setting('header_data_position'),
      '#options'      => $position_options,
    );
    
//CONTENT  
  $form['mobile_jquery_settings']['content_styles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content Settings'),
    '#states' => array(
      'visible' => array(
        ':input[name="use_global"]' => array('checked' => FALSE),
      ),
    ),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE, 
  );    
    $form['mobile_jquery_settings']['content_styles']['content_data_theme'] = array(
      '#type'         => 'select',
      '#title'        => t('Theme (data-theme)'),
      '#default_value' => mobile_jquery_theme_get_setting('content_data_theme'),
      '#options'      => $theme_settings,
    );
    
//FOOTER  
  $form['mobile_jquery_settings']['footer_styles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Footer Settings'),
    '#states' => array(
      'visible' => array(
        ':input[name="use_global"]' => array('checked' => FALSE),
      ),
    ),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE, 
  );    
    $form['mobile_jquery_settings']['footer_styles']['footer_data_theme'] = array(
      '#type'         => 'select',
      '#title'        => t('Theme (data-theme)'),
      '#default_value' => mobile_jquery_theme_get_setting('footer_data_theme'),
      '#options'      => $theme_settings,
    );    
    $form['mobile_jquery_settings']['footer_styles']['footer_data_position'] = array(
      '#type'         => 'select',
      '#title'        => t('Position (data-position)'),
      '#default_value' => mobile_jquery_theme_get_setting('footer_data_position'),
      '#options'      => $position_options,
    );
    
      $form['mobile_jquery_settings']['viewport_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Viewport settings'),
    '#states' => array(
      'visible' => array(
        ':input[name="viewport"]' => array('checked' => TRUE),
      ),
    ),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE, 
  );
  $form['mobile_jquery_settings']['viewport_settings']['viewport_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width'),
    '#default_value' => mobile_jquery_theme_get_setting('viewport_width'),
    '#description' => t('The initial width of the page.'),
  );
  $form['mobile_jquery_settings']['viewport_settings']['viewport_initial_scale'] = array(
    '#type' => 'textfield',
    '#title' => t('Initial scale'),
    '#default_value' => mobile_jquery_theme_get_setting('viewport_initial_scale'),
    '#description' => t('The initial scaling of the page.'),
  );
  $form['mobile_jquery_settings']['viewport_settings']['viewport_min_scale'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum scale'),
    '#default_value' => mobile_jquery_theme_get_setting('viewport_min_scale'),
    '#description' => t('The minimum scaling of the site.'),
  );
  $form['mobile_jquery_settings']['viewport_settings']['viewport_max_scale'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum scale'),
    '#default_value' => mobile_jquery_theme_get_setting('viewport_max_scale'),
    '#description' => t('The maximum scaling of the site.'),
  );
  $form['mobile_jquery_settings']['viewport_settings']['viewport_user_scalable'] = array(
    '#type' => 'textfield',
    '#title' => t('Scalable by user'),
    '#description' => t('Determine if a user can resize the screen.'),
    '#default_value' => mobile_jquery_theme_get_setting('viewport_user_scalable'),
  );
}