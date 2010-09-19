<?php

function hosting_platform_checkout_hosting_feature() {
  $features['PlatformCheckout'] = array(
    'title' => t('Platform Checkout'),
    'description' => t('Platform Checkout.'),
    'status' => HOSTING_FEATURE_DISABLED,
    'module' => 'hosting_platform_checkout',
    'group' => 'experimental',
    );
  return $features;
}