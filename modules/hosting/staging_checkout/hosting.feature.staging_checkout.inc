<?php

function hosting_staging_checkout_hosting_feature() {
  $features['StagingCheckout'] = array(
    'title' => t('Staging Checkout'),
    'description' => t('Staging Checkout.'),
    'status' => HOSTING_FEATURE_DISABLED,
    'module' => 'hosting_staging_checkout',
    'group' => 'experimental',
    );
  return $features;
}