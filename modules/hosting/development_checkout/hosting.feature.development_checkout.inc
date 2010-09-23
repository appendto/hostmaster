<?php

function hosting_development_checkout_hosting_feature() {
  $features['DevelopmentCheckout'] = array(
    'title' => t('Development Checkout'),
    'description' => t('Site Checkout.'),
    'status' => HOSTING_FEATURE_DISABLED,
    'module' => 'hosting_development_checkout',
    'group' => 'experimental',
    );
  return $features;
}