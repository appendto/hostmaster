<?php
// $Id$

/**
 * Implements a D6 preprocess emulation layer.
 */
function _phptemplate_variables($hook, $vars) {
  global $theme;
  $function = "{$theme}_preprocess_{$hook}";
  if (function_exists($function)) {
    $function($vars);
  }
  return $vars;
}

/**
 * Preprocessor for theme_page().
 */
function eldir_preprocess_page(&$vars) {
  $vars['logo'] = l($vars['site_name'], '<front>');

  if ($primary = menu_primary_local_tasks()) {
    $vars['tabs'] = "<ul class='links tabs clear-block'>{$primary}</ul>";
  }

  if ($secondary = menu_secondary_local_tasks()) {
    $vars['tabs2'] = "<ul class='links tabs clear-block'>{$secondary}</ul>";
  }

  if (!empty($vars['node'])) {
    // Add a node type label on node pages to help users.
    $types = node_get_types();
    $type = $vars['node']->type;
    if (!empty($types[$type])) {
      $vars['title'] = "<span class='label'>{$types[$type]->name}</span> {$vars['title']}";
    }

    $vars['body_classes'] .= " node-page";
    $vars['body_classes'] .= " ntype-{$type}";
  }

  $vars['sidebar_left'] = trim($vars['sidebar_left']);
  $vars['sidebar_right'] = trim($vars['sidebar_right']);
  $vars['body_classes'] .= empty($vars['sidebar_left']) && empty($vars['sidebar_right']) ? ' wide' : '';

  // Add path-based class for a last line of defense
  if (!empty($_GET['q'])) {
    $vars['body_classes'] .= ' path-'. str_replace('/', '-', $_GET['q']);
  }

  // Add special body class for error pages
  if (menu_get_active_item() === 0) {
    $vars['body_classes'] .= ' error-page';
  }

  // Add IE 6 compatibility stylesheet
  $vars['styles_ie6'] = base_path() . path_to_theme() . '/ie6.css';
}

/**
 * Preprocessor for theme_node().
 */
function eldir_preprocess_node(&$vars) {
  if (!empty($vars['node'])) {
    // Add a node type label on node pages to help users.
    $types = node_get_types();
    $type = $vars['node']->type;
    if (!empty($types[$type])) {
      $vars['title'] = "<span class='label'>{$types[$type]->name}</span> {$vars['title']}";
    }
  }
}

