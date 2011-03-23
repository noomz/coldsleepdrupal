<?php

/**
 * Settings form.
 */
function front_page_admin() {
  $form['site']['site_frontpage'] = array(
    '#type' => 'textfield',
    '#title' => t('Default front page'),
    '#default_value' => variable_get('site_frontpage', 'node'),
    '#size' => 40, 
    '#description' => t('Change this setting to <em>front_page</em> to activate your front page settings.'),
    '#field_prefix' => url(NULL, array('absolute' => TRUE)) . (variable_get('clean_url', 0) ? '' : '?q=')
  );
  return system_settings_form($form);
}
