<?php
// $Id$

function drush_hosting_alias_pre_hosting_task() {
  if (module_exists('hosting_alias')) {
    $task =& drush_get_context('HOSTING_TASK');
    if ($task->ref->type == 'site') {
      $aliases = implode(',', hosting_alias_get_aliases($task->ref));
      $task->context_options['aliases'] = ($aliases) ? $aliases : 'null';
      $task->context_options['redirection'] = 'null';
//      $task->context_options['redirection'] = db_result(db_query("SELECT redirection FROM {hosting_site_alias} WHERE vid=%d", $task->ref->vid));
    }
  }
}
