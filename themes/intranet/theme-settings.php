<?php

/**
 * @file
 * Theme settings file for the {{ THEME NAME }} theme.
 */

require_once dirname(__FILE__) . '/template.php';

/**
 * Implements hook_form_FORM_alter().
 */
function intranet_form_system_theme_settings_alter(&$form, $form_state) {
  // You can use this hook to append your own theme settings to the theme
  // settings form for your subtheme. You should also take a look at the
  // 'extensions' concept in the Omega base theme.
	$form['theme_settings']['responsive_menu_enable_width'] = array(
		'#type' => 'textfield',
		'#title' => t('Switch to responsive menu below this width:'),
		'#default_value' => theme_get_setting('responsive_menu_enable_width'),
	);

	$form['theme_settings']['carousel_speed'] = array(
		'#type' => 'textfield',
		'#title' => t('Define how often (in ms) to rotate the news carousel:'),
		'#default_value' => theme_get_setting('carousel_speed'),
	);	
}