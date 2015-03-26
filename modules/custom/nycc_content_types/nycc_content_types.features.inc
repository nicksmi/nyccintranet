<?php
/**
 * @file
 * nycc_content_types.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function nycc_content_types_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function nycc_content_types_node_info() {
  $items = array(
    'article' => array(
      'name' => t('News'),
      'base' => 'node_content',
      'description' => t('Create a news article and specify where you\'d like it to appear (ie. corporate or service news).'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'bulk_file_upload' => array(
      'name' => t('Bulk file upload'),
      'base' => 'node_content',
      'description' => t('Upload multiple files at once.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'event_calendar' => array(
      'name' => t('Event Calendar'),
      'base' => 'node_content',
      'description' => t('A content type to create events for calendar.'),
      'has_title' => '1',
      'title_label' => t('Event Title'),
      'help' => '',
    ),
    'intranet_group' => array(
      'name' => t('Intranet Group'),
      'base' => 'node_content',
      'description' => t('Create a group to allow members to receive alerts and access specific forums.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'landing_page' => array(
      'name' => t('Landing page'),
      'base' => 'node_content',
      'description' => t('Landing pages display a series of icons that link to sub-pages.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'marketplace_for_sale' => array(
      'name' => t('Marketplace'),
      'base' => 'node_content',
      'description' => t('List an item for sale or post a wanted item.'),
      'has_title' => '1',
      'title_label' => t('Title of item'),
      'help' => '',
    ),
    'page' => array(
      'name' => t('Page'),
      'base' => 'node_content',
      'description' => t('This is a content page that will appear in standard navigation menus.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'policy_document' => array(
      'name' => t('Policy'),
      'base' => 'node_content',
      'description' => t('Use this option to create a web version of a policy (rather than a pdf/word document).'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'top_task' => array(
      'name' => t('Top task'),
      'base' => 'node_content',
      'description' => t('Add new top tasks items here.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
