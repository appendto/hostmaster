<?php

function hosting_site_checkout_hosting_feature() {
  $features['SiteCheckout'] = array(
    'title' => t('Site Checkout'),
    'description' => t('Site Checkout.'),
    'status' => HOSTING_FEATURE_DISABLED,
    'module' => 'hosting_site_checkout',
    'group' => 'experimental',
    );
  return $features;
}