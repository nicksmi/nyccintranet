<?php

/**
 * @file
 * Template overrides as well as (pre-)process and alter hooks for the
 * {{ THEME NAME }} theme.
 */

function intranet_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  // Adding the title of the current page to the breadcrumb.

  $breadcrumb[] = drupal_get_title();

  if (!empty($breadcrumb)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $output = '<div class="breadcrumb">' . implode(' ► ', $breadcrumb) . '</div>';
    return $output;
  }
}


  function intranet_form_alter(&$form, &$form_state, $form_id) {
    if ($form_id == "apachesolr_search_custom_page_search_form") {
        $form['basic']['keys']['#title'] = '';
        $form['basic']['keys']['#attributes'] = array(
          'placeholder' => 'Search...');
        $form['#attributes']['class'][] = 'contextual-search-form';
    };

    if($form_id == 'user_login'){
      drupal_add_js(drupal_get_path('theme', 'intranet') . '/js/spin.min.js');
      drupal_add_js(drupal_get_path('theme', 'intranet') . '/js/jquery.spin.js');
      drupal_add_js(drupal_get_path('theme', 'intranet') . '/js/intranet.login.js');
    }

  }

  function intranet_preprocess_username(&$vars) {
    // xml:lang alone is invalid in HTML5. Use the lang attribute instead.
    if (empty($vars['attributes_array']['lang'])) {
      $vars['attributes_array']['lang'] = '';
    }
    unset($vars['attributes_array']['xml:lang']);
    unset($vars['attributes_array']['property']);
    unset($vars['attributes_array']['rel']);
  }

  function intranet_html_head_alter(&$head_elements) {
    unset($head_elements['system_meta_generator']);
    foreach ($head_elements as $key => $element) {
      if (isset($element['#attributes']['charset']) && $element['#attributes']['charset'] == 'utf-8') {
        unset($head_elements[$key]);
      }
    }

    $head_elements['system_meta_generator'] = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array('http-equiv' => 'Content-Type', 'content' => 'text/html; charset=UTF-8'),
    );
  }

function intranet_file($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'file';
  element_set_attributes($element, array('id', 'name'));
  _form_set_class($element, array('form-file'));

  return '<input' . drupal_attributes($element['#attributes']) . ' />';
}

/**
 * Implementation of theme_element
 */
function intranet_form_element_label($vars) {
  // HTML5 fix: label@for attributes must refer to form controls
  switch($vars['element']['#type']) {
    case 'checkboxes':
    case 'radios':
    case 'password_confirm':
    case 'date':
    case 'mfw_managed_file':
    case 'managed_file':
      unset($vars['element']['#id']);
    default:
      return theme_form_element_label($vars);
  }
}

function intranet_preprocess_views_view_table(&$vars) {
    $vars['raw_result'] = $vars['view']->style_plugin->rendered_fields;
}

function intranet_preprocess_advanced_forum_topic_list_view(&$vars) {
  $vars['raw_result'] = $vars['view']->style_plugin->rendered_fields;
}


// Display real name on quotes rather than username
function intranet_quote($vars) {
  extract($vars);

  $user = user_load_by_name($quote_author);
  $quote_author = $user->realname;

  $zebra = $nest & 1 ? 'odd' : 'even';
  $quote_output = '<blockquote class="quote-msg quote-nest-' . $nest . ' ' . $zebra . '">';
  if ($quote_author != '') {
    $quote_author = t('%author wrote:', array('%author' => $quote_author));
  }
  else {
    $quote_author = t('Quote:');
  }
  $quote_author = '<div class="quote-author">' . $quote_author . '</div>';
  $quote_output .= $quote_author . $quote_content . '</blockquote>';

  return $quote_output;
}


?>
