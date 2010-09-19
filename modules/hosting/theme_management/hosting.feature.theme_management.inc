<?php

function hosting_theme_management_hosting_feature() {
  $features['ThemeManagement'] = array(
    'title' => t('Theme Management'),
    'description' => t('Theme Management.'),
    'status' => HOSTING_FEATURE_DISABLED,
    'module' => 'hosting_theme_management',
    'group' => 'experimental',
    );
  return $features;
}