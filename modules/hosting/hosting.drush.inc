<?php


function hosting_drush_command() {
  $items['hosting-dispatch'] = array(
    'description' => dt('Centralized command for dispatching the various queue processors (hosting, cron, backup etc.)'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL
  );

  $items['hosting-setup'] = array(
    'description' => dt('Set up initial configuration settings such as the cron entry for the queue dispatcher and more.'),
  );



  $queues = hosting_get_queues();
  foreach ($queues as $queue => $info) {
    $dispatch = dt("Dispatched: @items items every @frequency minutes", array('@items' => $info['items'], '@frequency' => round($info['frequency'] / 60)));
    $items['hosting-' . $queue] = array(
      'callback' => 'hosting_run_queue', 
      'description' => $info['description'] . " " . $dispatch,
      'queue' => $queue,
    );
  }

  $items['hosting-task'] = array(
    'description' => 'execute a specific queue item',
    'arguments' => array(
      '@context_name' => 'Context to work on',
      'command' => 'provision-[command] to invoke',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL
  );

  return $items;
}
