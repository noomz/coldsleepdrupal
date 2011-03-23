<?php

/**
 * Pricing settings.
 */
function coldsleep_hooker_pricing_form() {
  $form['pricing_form_description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#rows' => 5,
    '#default_value' => variable_get('pricing_form_description', ''),
  );
  $form['pricing_form_action'] = array(
    '#type' => 'textfield',
    '#title' => t('Form action'),
    '#default_value' => variable_get('pricing_form_action', ''),
  );
  return system_settings_form($form);
}
