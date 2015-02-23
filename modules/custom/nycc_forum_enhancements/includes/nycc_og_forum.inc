<?php

/**
 * @file
 * OG Forum module
 * 
 * THIS IS THE NYCC MODIFIED VERSION OF THE MODULE FILE!
 * This file contains differences from the original og_forum module
 */

/**
 * The role name of group forum moderator.
 */
define('OG_FORUM_MODERATOR', 'forum administrator');

/* Drupal Core API */

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Add the OG fields on forum form
 */
function nycc_forum_enhancements_form_forum_form_forum_alter(&$form, &$form_state) {

  _nycc_forum_enhancements_term_form_alter($form, $form_state);
}

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Add the OG fields on container form
 */
function nycc_forum_enhancements_form_forum_form_container_alter(&$form, &$form_state) {

  _nycc_forum_enhancements_term_form_alter($form, $form_state);
}

/**
 * Add the OG fields on the current taxonomy_term form.
 */
function _nycc_forum_enhancements_term_form_alter(&$form, &$form_state) {

  $term = new stdClass();
  $vocabulary = taxonomy_vocabulary_load($form['vid']['#value']);

  if (isset($form['tid']['#value'])) {
    $term = taxonomy_term_load($form['tid']['#value']);
  }
  else {

    $defaults = array(

      'name' => '',
      'description' => '',
      'format' => NULL,
      'vocabulary_machine_name' => $vocabulary->machine_name,
      'tid' => NULL,
      'weight' => 0,
    );
    foreach ($defaults as $key => $value) {
      $term->$key = $value;
    }
  }

  field_attach_form('taxonomy_term', $term, $form, $form_state);
}

/**
 * Implements hook_query_TAG_alter().
 *
 * Check all the taxonomy_term queries against the OG Audience table
 */
function nycc_forum_enhancements_query_term_access_alter(QueryAlterableInterface $query) {

  global $user;

  // Read meta-data from query, if provided.
  if (!$account = $query->getMetaData('account')) {
    $account = $user;
  }

  // If $account can bypass node access, or there are no node access
  // modules, we don't need to alter the query.
  if (user_access('bypass node access', $account)) {
    return;
  }

  // Prevent duplicate records.
  $query->distinct();

  // Load all the groups of the user for which the query is executed.
  $group_gids = array();
  $groups = og_get_entity_groups('user', $account);
  foreach ($groups as $gid => $value) {
    $group_gids[] = $gid;
  }

  // Find all instances of the {taxonomy_term_data} table being joined --
  // could appear more than once in the query, and could be aliased.
  // Join each one to the OG Group audience table.
  $tables = $query->getTables();
  foreach ($tables as $talias => $tableinfo) {

    $table = $tableinfo['table'];
    if (!($table instanceof SelectQueryInterface) && $table == 'taxonomy_term_data') {

      $audience_alias = $query->leftJoin('og_membership', 'ga', '%alias.etid = ' . $talias . '.tid
                                          AND %alias.entity_type = :entity_type
                                          AND %alias.field_name = :field_name',
                                        array(
                                          ':entity_type' => 'taxonomy_term',
                                          ':field_name' => 'og_group_access',
                                        ));
      $condition = db_or();
      $condition->isNull($audience_alias . '.gid');

      if (!empty($group_gids)) {
        $condition->condition($audience_alias . '.gid', $group_gids, 'IN');
      }

      $query->condition($condition);
    }
  }
}

/**
 * Implements hook_node_presave().
 *
 * Copy the OG Audience field values from the forum taxonomy term
 * to the topic node being saved
 */
function nycc_forum_enhancements_node_presave($node) {

  if (_forum_node_check_node_type($node)) {

    $gids = og_get_entity_groups('taxonomy_term', taxonomy_term_load($node->taxonomy_forums[LANGUAGE_NONE][0]['tid']));

    if (!empty($gids)) {
      $node->{OG_AUDIENCE_FIELD}[LANGUAGE_NONE] = array();
      foreach ($gids as $group) {
        foreach ($group as $gid) {
          $node->{OG_AUDIENCE_FIELD}[LANGUAGE_NONE][] = array('target_id' => $gid);
        }
      }
    }
    $node->{OG_CONTENT_ACCESS_FIELD}[LANGUAGE_NONE][0]['value'] = 2;
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Hide the OG Field on the topic form
 */
function nycc_forum_enhancements_form_forum_node_form_alter(&$form, &$form_state) {

  $form[OG_AUDIENCE_FIELD]['#type'] = 'hidden';
  $form[OG_CONTENT_ACCESS_FIELD]['#type'] = 'hidden';
}

/**
 * Implements hook_node_access().
 */
function nycc_forum_enhancements_node_access($node, $op, $account) {

  if (!is_object($node) || $node->type != 'forum') {
    return NODE_ACCESS_IGNORE;
  }

  switch ($op) {

    case 'view':
      $user_group = og_get_entity_groups();
      $node_group = og_get_entity_groups('node', $node);

      $access = NODE_ACCESS_DENY;

      if (count($node_group) == 0) {
        return NODE_ACCESS_IGNORE;
      }

      foreach ($node_group['node'] as $gid) {
        if (array_key_exists('node', $user_group) && in_array($gid, $user_group['node'])) {
          $access = NODE_ACCESS_ALLOW;
        }
      }

      return $access;
  }

  return NODE_ACCESS_IGNORE;
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function nycc_forum_enhancements_form_comment_node_forum_form_alter(&$form, &$form_state) {

  $form['comment_body'][LANGUAGE_NONE][0]['#title'] = t('Response');
}

/**
 * Implements of hook_comment_view().
 */
function nycc_forum_enhancements_comment_view($comment, $view_mode, $langcode) {

  if (!module_exists('forum_access')) {
    return;
  }

  $comment->content['#node'] = node_load($comment->nid);
  $comment->content['#comment'] = $comment;
  forum_access_comment_view_alter($comment->content);
}

/* OG Api */

/**
 * Implements hook_og_default_roles().
 */
function nycc_forum_enhancements_og_default_roles() {

  return array(OG_FORUM_MODERATOR);
}

/**
 * Implements hook_og_permission().
 */
function nycc_forum_enhancements_og_permission() {

  return array(

    'moderate' => array(
      'title' => t('Moderate the forum'),
      'description' => t("Allow the user to moderate the group forum (Require Forum Access Module)"),
      'default role' => array(OG_FORUM_MODERATOR, OG_ADMINISTRATOR_ROLE),
    ),
  );
}

/**
 * Implements hook_og_role_grant().
 */
function nycc_forum_enhancements_og_role_grant($gid, $uid, $rid) {

  if (!module_exists('forum_access')) {
    return;
  }

  $perms = og_role_permissions(array($rid => $rid));
  if (isset($perms[$rid]['moderate']) && $perms[$rid]['moderate']) {

    $query = new SelectQuery('og_membership', 'om');
    $query->innerJoin('taxonomy_term_data', 'td', '%alias.tid = om.etid');
    $query->innerJoin('taxonomy_vocabulary', 'tv', '%alias.vid = td.vid
                      AND %alias.machine_name = :forums', 
                    array(
                      ':forums' => 'forums'
                    ));
    $query->addField('om', 'etid', 'tid');
    $forums = $query->where('om.entity_type = :taxonomy_term', array(':taxonomy_term' => 'taxonomy_term'))
      ->where('om.gid = :gid', array(':gid' => $gid))
      ->execute();

    foreach ($forums as $record) {
      $acl_id = _forum_access_get_acl($record->tid);
      acl_add_user($acl_id, $uid);
    }
  }
}

/**
 * Implements hook_og_role_revoke().
 */
function nycc_forum_enhancements_og_role_revoke($gid, $uid, $rid) {

  if (!module_exists('forum_access')) {
    return;
  }

  $perms = og_role_permissions(array($rid => $rid));
  if (isset($perms[$rid]['moderate']) && $perms[$rid]['moderate'] && !og_user_access($gid, 'moderate', user_load($uid))) {

    $query = new SelectQuery('og_membership', 'om');
    $query->innerJoin('taxonomy_term_data', 'td', '%alias.tid = om.etid');
    $query->innerJoin('taxonomy_vocabulary', 'tv', '%alias.vid = td.vid
                      AND %alias.machine_name = :forums', 
                    array(
                      ':forums' => 'forums'
                    ));
    $query->addField('om', 'etid', 'tid');
    $forums = $query->where('om.entity_type = :taxonomy_term', array(':taxonomy_term' => 'taxonomy_term'))
      ->where('om.gid = :gid', array(':gid' => $gid))
      ->execute();

    foreach ($forums as $record) {
      $acl_id = _forum_access_get_acl($record->tid);
      acl_remove_user($acl_id, $uid);
    }
  }
}

/**
 * Implements hook_og_membership_insert().
 */
function nycc_forum_enhancements_og_membership_insert(OgMembership $og_membership) {

  if (!module_exists('forum_access')) {
    return;
  }

  if ($og_membership->entity_type == 'taxonomy_term' && !empty($og_membership->gid)) {

    $node = entity_load_single($og_membership->group_type, $og_membership->gid);
    $rids = nycc_forum_enhancements_get_roles_by_permission($og_membership->group_type, $node->type, $og_membership->gid, 'moderate');
    $acl_id = _forum_access_get_acl($og_membership->etid);

    $users = og_get_users_by_roles($og_membership->gid, array_keys($roles));
    $new_user = array($node->uid);
    foreach ($users as $user) {
      $new_user[] = $user->uid;
    }

    $new_user = array_unique($new_user);

    foreach ($new_user as $user) {
      acl_add_user($acl_id, $user);
    }
  }
}

/**
 * Implements hook_og_membership_delete().
 */
function nycc_forum_enhancements_og_membership_delete(OgMembership $og_membership) {

  if (!module_exists('forum_access')) {
    return;
  }

  if ($og_membership->entity_type == 'taxonomy_term' && !empty($og_membership->gid)) {

    $node = entity_load_single($og_membership->group_type, $og_membership->gid);
    $rids = nycc_forum_enhancements_get_roles_by_permission($og_membership->group_type, $node->type, $og_membership->gid, 'moderate');
    $acl_id = _forum_access_get_acl($og_membership->etid);

    $users = og_get_users_by_roles($og_membership->gid, array_keys($roles));
    $old_user = array($node->uid);
    foreach ($users as $user) {
      $old_user[] = $user->uid;
    }

    $old_user = array_unique($old_user);

    foreach ($old_user as $user) {
      acl_remove_user($acl_id, $user);
    }
  }
}

/* OG Context API */

/**
 * Implements hook_og_context_negotiation_info().
 */
function nycc_forum_enhancements_og_context_negotiation_info() {

  $providers = array();

  $providers['og_forum'] = array(

    'name' => t('OG Forum'),
    'description' => t('OG Forum group detection.'),
    'callback' => 'nycc_forum_enhancements_forum_group_handler',
    'menu path' => array(
      'forum/%',
      'comment/reply/%',
      'comment/%',
      'forum/active',
      'forum/unanswered',
      'forum/new',
    ),
  );

  return $providers;
}

/**
 * Context handler; Get groups from existing custom context.
 */
function nycc_forum_enhancements_forum_group_handler() {

  $item = menu_get_item();

  switch ($item['path']) {

    case 'forum/%':
      // og_set_global_access_module('og_forum');
      return _group_context_handler_entity('taxonomy_term', $item['map'][1]);

    case 'comment/reply/%':
      return (_group_context_handler_entity('node', $item['map'][2]));

    case 'comment/%':
      $item['map'][1] = comment_load($item['map'][1]);
    case 'comment/%/edit':
      $node = node_load($item['map'][1]->nid);
      return _group_context_handler_entity('node', $node);

    case 'forum/active':
    case 'forum/unanswered':
    case 'forum/new':
      if (isset($_GET['forum'])) {

        if (is_array($_GET['forum'])) {
          $_GET['forum'] = $_GET['forum'][0];
        }

        return _group_context_handler_entity('taxonomy_term', taxonomy_term_load($_GET['forum']));
      }
      break;
  }

  return array();
}

/* Replacements for now removed og 1.x functions */

/**
 * Get all the roles with certain permissions in a group.
 *
 * @param $group_type
 *   The group entity type.
 * @param $bundle
 *   The group entity bundle.
 * @param $gid
 *   The group unique ID.
 * @param $permission
 *   The name of the selected permission.
 * @return
 *   Array with the role IDs.
 */
function nycc_forum_enhancements_get_roles_by_permission($group_type, $bundle, $gid, $permission) {
  $roles = og_roles($group_type, $bundle, $gid);
  $permissions = og_role_permissions($roles);
  $rids = array();
  foreach ($permissions AS $rid => $permissions) {
    if (array_key_exists($permission, $permissions)) {
      $rids[] = $rid;
    }
  }
  return $rids;
}

/**
 * Get all the users with certain roles in a group.
 *
 * @param $gid
 *   The group unique ID.
 * @param $roles
 *   Array with the role IDs to query.
 * @return
 *   Array with the user IDs.
 */
function nycc_forum_enhancements_get_users_by_roles($gid, $rids = array()) {
  if (empty($rids)) { 
    return array();
  }

  $query = db_select('og_users_roles', 'og_users_roles');
  return $query->fields('og_users_roles', array('uid'))
    ->condition('gid', $gid)
    ->condition('rid', $rids, 'IN')
    ->execute()
    ->fetchAll();
}