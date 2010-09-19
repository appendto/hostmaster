<?php

function hosting_server_management_hosting_feature() {
  $features['ServerManagement'] = array(
    'title' => t('Server Management'),
    'description' => t('Server Management.'),
    'status' => HOSTING_FEATURE_DISABLED,
    'module' => 'hosting_server_management',
    'group' => 'experimental',
    );
  return $features;
}