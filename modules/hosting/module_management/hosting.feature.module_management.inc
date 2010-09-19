<?php

function hosting_module_management_hosting_feature() {
  $features['ModuleManagement'] = array(
    'title' => t('Module Management'),
    'description' => t('Module Management.'),
    'status' => HOSTING_FEATURE_DISABLED,
    'module' => 'hosting_module_management',
    'group' => 'experimental',
    );
  return $features;
}