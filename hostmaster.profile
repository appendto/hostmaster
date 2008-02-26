<?php
// $Id$

include_once('profiles/hostmaster/modules/install_profile_api/crud.inc');

/**
 * Return an array of the modules to be enabled when this profile is installed.
 *
 * @return
 *  An array of modules to be enabled.
 */
function hostmaster_profile_modules() {
  return array(
    /* core */ 'block', 'color', 'filter', 'help', 'menu', 'node', 'system', 'user', 'watchdog',
    /* contrib */ 'drush', 'nodequeue', 'token', 'views', 'views_ui',
    /* custom */ 'provision', 'provision_apache', 'provision_mysql', 'provision_drupal', 'hosting');
}

/**
 * Return a description of the profile for the initial installation screen.
 *
 * @return
 *   An array with keys 'name' and 'description' describing this profile.
 */
function hostmaster_profile_details() {
  return array(
    'name' => 'Hostmaster',
    'description' => 'Select this profile to manage the installation and maintenance of hosted Drupal sites.'
  );
}

/**
 * Perform any final installation tasks for this profile.
 *
 * @return
 *   An optional HTML string to display to the user on the final installation
 *   screen.
 */
function hostmaster_profile_final() {
  /* Default node types and default node */
  node_types_rebuild();
  
  /* Default client */
  $node = new stdClass();
  $node->type = 'client';
  $node->email = ($_SERVER['SERVER_ADMIN']) ? $_SERVER['SERVER_ADMIN'] : 'changeme@example.com';
  $node->name = 'Administrator';
  $node->status = 1;
  node_save($node);
  variable_set('hosting_default_client', $node->nid);  

  /* Default database server */
  global $db_url;
  $url = parse_url($db_url);

  $node = new stdClass();
  $node->type = 'db_server';
  $node->title = $url['host'];
  $node->db_type = $url['scheme'];
  if (_provision_mysql_can_create_database()) {
    $node->db_user = $url['user'];
    $node->db_passwd = $url['pass'];
  }
  else {
    $node->db_user = 'root';
    $node->db_passwd = 'password';    
  }
  $node->status = 1;
  node_save($node);
  variable_set('hosting_default_db_server', $node->nid);
  variable_set('hosting_own_db_server', $node->nid);
  
  $node = new stdClass();
  $node->type = 'web_server';
  $node->title = $_SERVER['HTTP_HOST'];
  $node->script_user = provision_get_script_owner();
  $node->web_group = provision_get_group_name();
  $node->status = 1;
  node_save($node);

  $node = new stdClass();
  $node->type = 'platform';
  $node->title = "Drupal " . VERSION;
  $node->publish_path = $_SERVER['DOCUMENT_ROOT'];
  $node->web_server = variable_get('hosting_default_web_server', 3);
  $node->status = 1;
  variable_set('hosting_default_platform', $node->nid);
  variable_set('hosting_own_platform', $node->nid);
  
  # Action queue
  $queue = (object) array(
     'title' => 'Hosting queue',
     'size' => '0',
     'link' => '',
     'link_remove' => '',
     'owner' => 'nodequeue',
     'show_in_ui' => '1',
     'show_in_tab' => '1',
     'show_in_links' => '0',
     'reference' => '0',
     'subqueue_title' => '',
     'reverse' => '0',
     'subqueues' => '1',
     'types' => 
        array (
          0 => 'action',
        ),
    );

   $queue->add_subqueue = array($queue->title);
   nodequeue_save($queue);
   
   variable_set('hosting_action_queue', $queue->qid);
   $subqueue = nodequeue_load_subqueues_by_queue($queue->qid);
   variable_set('hosting_action_subqueue', $subqueue->qid);

   #verify platform
   hosting_add_action(4, "verify");
   
   install_add_block("views", "platforms", "garland", 1, 0, "right");
   install_add_block("views", "servers", "garland", 1, 0, "right");
   install_add_block("views", "nodequeue_1", "garland", 1, -1, "right");
   
   #initial configuration of hostmaster - todo
   
   variable_set('site_frontpage', 'sites');
   
   // @todo create proper roles, and set up views to be role based
   install_set_permissions(install_get_rid('anonymous user'), array('access content', 'access all views'));
   install_set_permissions(install_get_rid('authenticated user'), array('access content', 'access all views'));
   views_invalidate_cache();
   menu_rebuild();
   
   /**
    * Generate administrator account
    */
   $user = new stdClass();
   $edit['name'] = 'Administrator';
   $edit['pass'] = user_password();
   $edit['mail'] = ($_SERVER['SERVER_ADMIN']) ? $_SERVER['SERVER_ADMIN'] : 'changeme@example.com';
   $edit['status'] = 1;
   $user = user_save($user,  $edit);
   $GLOBALS['user'] = $user;
   
   drupal_get_messages();
   drupal_goto('sites');
}
