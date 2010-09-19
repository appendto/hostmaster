<?php

function hosting_security_hosting_feature() {
  $features['Security'] = array(
    'title' => t('Security Testing and secure code testing'),
    'description' => t('Test a site or platform for security holes. Checks security based on checked options for the security methods to check.'),
    'status' => HOSTING_FEATURE_DISABLED,
    'module' => 'hosting_security',
    'group' => 'experimental',
    );
  return $features;
}
