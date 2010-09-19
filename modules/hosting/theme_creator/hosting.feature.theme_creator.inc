<?php

function hosting_theme_creator_hosting_feature() {
  $features['ThemeCreator'] = array(
    'title' => t('Theme Creator'),
    'description' => t('Theme Creator.'),
    'status' => HOSTING_FEATURE_DISABLED,
    'module' => 'hosting_theme_creator',
    'group' => 'experimental',
    );
  return $features;
}