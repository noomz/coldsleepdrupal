<?php

/**
 * Member form.
 */
function coldsleep_hooker_member_form() {
  // Add JavaScript.
  drupal_add_js(drupal_get_path('module', 'coldsleep_hooker') .'/js/pricing.js');
  $description = variable_get('pricing_form_description', '');
  $form['description'] = array(
    '#type' => 'item',
    '#markup' => $description,
  );
  $form['type'] = array(
    '#type' => 'radios',
    '#title' => t('Create Account or Sign in'),
    '#options' => array(
      'create' => t('I need to create an account'),
      'login' => t('I have an existing account'),
    ),
    '#default_value' => 'create',
  );
  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
  );
  $form['password'] = array(
    '#type' => 'textfield',
    '#title' => t('Password'),
  );
  $form['retype_password'] = array(
    '#type' => 'textfield',
    '#title' => t('Retype password'),
  );
  $form['create'] = array(
    '#type' => 'submit',
    '#value' => t('Create Account'),
  );
  $form['login'] = array(
    '#type' => 'submit',
    '#value' => t('Login'),
  );
  if (user_access('administer nodes')) {
    $form['edit'] = array(
      '#type' => 'item',
      '#markup' => l(t('Edit this page.'), 'admin/config/content/pricing', array('query' => drupal_get_destination())),
    );
  }
  if ($action = variable_get('pricing_form_action', '')) {
    $form['#action'] = $action;
  }
  return $form;
}
