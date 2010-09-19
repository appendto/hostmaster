<?php

function hosting_aegir_services_hosting_feature() {
  $features['AegirServices'] = array(
    'title' => t('Aegir Services'),
    'description' => t('Aegir Services'),
    'status' => HOSTING_FEATURE_DISABLED,
    'module' => 'hosting_aegir_services',
    'group' => 'experimental',
    );
  return $features;
}