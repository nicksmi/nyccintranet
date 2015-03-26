<?php
/**
 * @file
 * nycc_social.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function nycc_social_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function nycc_social_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_flag_default_flags().
 */
function nycc_social_flag_default_flags() {
  $flags = array();
  // Exported flag: "Comment like".
  $flags['comment_like'] = array(
    'entity_type' => 'comment',
    'title' => 'Comment like',
    'global' => 0,
    'types' => array(
      0 => 'comment_node_blog',
      1 => 'comment_node_forum',
      2 => 'comment_node_article',
    ),
    'flag_short' => '<i class="fa fa-thumbs-o-up"></i> Like ([comment:flag-comment-like-count])',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => '<i class="fa fa-thumbs-up"></i> ([comment:flag-comment-like-count])',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 'full',
      'token' => 0,
    ),
    'show_as_field' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => 0,
    'api_version' => 3,
    'module' => 'nycc_social',
    'locked' => array(
      0 => 'name',
    ),
  );
  // Exported flag: "Node like".
  $flags['node_like'] = array(
    'entity_type' => 'node',
    'title' => 'Node like',
    'global' => 0,
    'types' => array(
      0 => 'page',
      1 => 'blog',
      2 => 'article',
    ),
    'flag_short' => '<i class="fa fa-thumbs-o-up"></i> Like ([node:flag-node-like-count])',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => '<i class="fa fa-thumbs-up"></i> ([node:flag-node-like-count])',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 'full',
      'teaser' => 0,
      'rss' => 0,
      'search_index' => 0,
      'search_result' => 0,
      'news_summary' => 0,
      'print' => 0,
      'token' => 0,
    ),
    'show_as_field' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => 0,
    'i18n' => 0,
    'api_version' => 3,
    'module' => 'nycc_social',
    'locked' => array(
      0 => 'name',
    ),
  );
  // Exported flag: "Read Message".
  $flags['read_message'] = array(
    'entity_type' => 'message',
    'title' => 'Read Message',
    'global' => 0,
    'types' => array(),
    'flag_short' => 'Flag as read <i class="fa fa-flag"></i>',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Unflag as read <i class="fa fa-flag-o"></i>',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 0,
      'token' => 0,
    ),
    'show_as_field' => 1,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => 0,
    'api_version' => 3,
    'module' => 'nycc_social',
    'locked' => array(
      0 => 'name',
    ),
  );
  // Exported flag: "Read Node".
  $flags['read_node'] = array(
    'entity_type' => 'node',
    'title' => 'Read Node',
    'global' => 0,
    'types' => array(
      0 => 'alert',
      1 => 'page',
      2 => 'blog',
      3 => 'forum',
      4 => 'intranet_group',
      5 => 'article',
      6 => 'policy_document',
    ),
    'flag_short' => 'Flag as read',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Unflag as read',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 0,
      'teaser' => 0,
      'rss' => 0,
      'search_index' => 0,
      'search_result' => 0,
      'news_summary' => 0,
      'print' => 0,
      'token' => 0,
    ),
    'show_as_field' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => 0,
    'i18n' => 0,
    'api_version' => 3,
    'module' => 'nycc_social',
    'locked' => array(
      0 => 'name',
    ),
  );
  // Exported flag: "Status comment like".
  $flags['status_comment_like'] = array(
    'entity_type' => 'status_comment',
    'title' => 'Status comment like',
    'global' => 0,
    'types' => array(),
    'flag_short' => '<span><i class="fa fa-thumbs-o-up"></i> Like ([status_comment:flag-status-comment-like-count])</span>',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => '<span><i class="fa fa-thumbs-up"></i> ([status_comment:flag-status-comment-like-count])</span>',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 'full',
      'token' => 0,
    ),
    'show_as_field' => FALSE,
    'show_on_form' => FALSE,
    'access_author' => '',
    'show_contextual_link' => 0,
    'api_version' => 3,
    'module' => 'nycc_social',
    'locked' => array(
      0 => 'name',
    ),
  );
  // Exported flag: "Status like".
  $flags['status_like'] = array(
    'entity_type' => 'status',
    'title' => 'Status like',
    'global' => 0,
    'types' => array(),
    'flag_short' => '<i class="fa fa-thumbs-o-up"></i> Like ([status:flag-status-like-count])',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => '<i class="fa fa-thumbs-up"></i> ([status:flag-status-like-count])',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 'full',
      'token' => 0,
    ),
    'show_as_field' => FALSE,
    'show_on_form' => FALSE,
    'access_author' => '',
    'show_contextual_link' => 0,
    'api_version' => 3,
    'module' => 'nycc_social',
    'locked' => array(
      0 => 'name',
    ),
  );
  // Exported flag: "Subscribe to forum".
  $flags['subscribe_to_forum'] = array(
    'entity_type' => 'taxonomy_term',
    'title' => 'Subscribe to forum',
    'global' => 0,
    'types' => array(
      0 => 'forums',
    ),
    'flag_short' => '<i class="fa fa-bookmark-o"></i> <span>Subscribe</span> ',
    'flag_long' => 'Subscribe to this forum',
    'flag_message' => '',
    'unflag_short' => '<i class="fa fa-bookmark"></i> <span>Subscribed</span>',
    'unflag_long' => 'Unsubscribe from this forum',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 0,
      'token' => 0,
    ),
    'show_as_field' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => 0,
    'api_version' => 3,
    'module' => 'nycc_social',
    'locked' => array(
      0 => 'name',
    ),
  );
  // Exported flag: "Subscribe to node".
  $flags['subscribe_to_node'] = array(
    'entity_type' => 'node',
    'title' => 'Subscribe to node',
    'global' => 0,
    'types' => array(
      0 => 'forum',
      1 => 'page',
    ),
    'flag_short' => '<i class="fa fa-bookmark-o"></i> Subscribe',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => '<i class="fa fa-bookmark"></i> Unsubscribe',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 'full',
      'teaser' => 0,
      'rss' => 0,
      'search_index' => 0,
      'search_result' => 0,
      'news_summary' => 0,
      'print' => 0,
      'token' => 0,
    ),
    'show_as_field' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => 0,
    'i18n' => 0,
    'api_version' => 3,
    'module' => 'nycc_social',
    'locked' => array(
      0 => 'name',
    ),
  );
  // Exported flag: "Subscribe to tag".
  $flags['subscribe_to_tag'] = array(
    'entity_type' => 'taxonomy_term',
    'title' => 'Subscribe to tag',
    'global' => 0,
    'types' => array(
      0 => 'tags',
    ),
    'flag_short' => '<i class="fa fa-bookmark-o"></i> Subscribe to \'[term:name]\' tag',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => '<i class="fa fa-bookmark"></i> Unsubscribe from \'[term:name]\' tag',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 'full',
      'token' => 0,
    ),
    'show_as_field' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => 0,
    'api_version' => 3,
    'module' => 'nycc_social',
    'locked' => array(
      0 => 'name',
    ),
  );
  // Exported flag: "Top Task User Default".
  $flags['top_task_user_default'] = array(
    'entity_type' => 'node',
    'title' => 'Top Task User Default',
    'global' => 1,
    'types' => array(
      0 => 'top_task',
    ),
    'flag_short' => '<i class="fa fa-flag fa-fw"></i> Flag as user default',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => '<i class="fa fa-flag-o fa-fw"></i> Unflag as user default',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 'full',
      'teaser' => 0,
      'rss' => 0,
      'search_index' => 0,
      'search_result' => 0,
      'news_summary' => 0,
      'print' => 0,
      'token' => 0,
    ),
    'show_as_field' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => 0,
    'i18n' => 0,
    'api_version' => 3,
    'module' => 'nycc_social',
    'locked' => array(
      0 => 'name',
    ),
  );
  // Exported flag: "User Confirm Read".
  $flags['user_confirm_read'] = array(
    'entity_type' => 'node',
    'title' => 'User Confirm Read',
    'global' => 0,
    'types' => array(
      0 => 'alert',
      1 => 'blog',
      2 => 'article',
      3 => 'policy_document',
    ),
    'flag_short' => 'Click to confirm you have read and understood this alert',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Cancel read confirmation',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 0,
      'teaser' => 0,
      'rss' => 0,
      'search_index' => 0,
      'search_result' => 0,
      'news_summary' => 0,
      'print' => 0,
      'token' => 0,
    ),
    'show_as_field' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => 0,
    'i18n' => 0,
    'api_version' => 3,
    'module' => 'nycc_social',
    'locked' => array(
      0 => 'name',
    ),
  );
  return $flags;

}

/**
 * Implements hook_node_info().
 */
function nycc_social_node_info() {
  $items = array(
    'alert' => array(
      'name' => t('Alert'),
      'base' => 'node_content',
      'description' => t('Send a global or group alert - it will appear in the notification area and latest updates feed.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
