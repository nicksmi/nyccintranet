<?php

/**
 * @file
 * Contains a pre-process hook for 'region'.
 */

/**
 * Implements hook_preprocess_region().
 */
function intranet_preprocess_region(&$variables) {
  // Sidebar regions common template suggestion for all sidebars.
  if (strpos($variables['region'], 'sidebar') === 0) {
    // Allow a region-specific template to override region--sidebar.
    array_unshift($variables['theme_hook_suggestions'], 'region__sidebar');
  }
  // Use a template with no wrapper for the content region.
  elseif ($variables['region'] == 'content') {
    // Allow a region-specific template to override region--minimal.
    array_unshift($variables['theme_hook_suggestions'], 'region__minimal');
  }

  if($variables['region'] === 'home_news'){
    drupal_add_js(array('nyccIntranetTheme' => array('carousel_speed' => theme_get_setting('carousel_speed'))), 'setting');
    $vars['scripts'] = drupal_get_js();

    $blocklist = block_list('home_news');
    $variables['blocklist'] = $blocklist;
  }

  // Use BEM syntax for the modifier class.
  $css_region_name = drupal_clean_css_identifier($variables['region']);
  $variables['classes_array'] = preg_replace('/^region-' . $css_region_name . '$/', 'l-region--' . $css_region_name, $variables['classes_array']);
  // Use the prefix "l-" on region class names as described in SMACSS.
  $variables['classes_array'] = preg_replace('/^region$/', 'l-region', $variables['classes_array']);




}
