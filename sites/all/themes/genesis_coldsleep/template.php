<?php
// $Id: template.php,v 1.10 2011/01/14 02:57:57 jmburnz Exp $

/**
 * Preprocess and Process Functions SEE: http://drupal.org/node/254940#variables-processor
 * 1. Rename each function to match your subthemes name,
 *    e.g. if you name your theme "themeName" then the function
 *    name will be "themeName_preprocess_hook". Tip - you can
 *    search/replace on "genesis_SUBTHEME".
 * 2. Uncomment the required function to use.
 */

/**
 * Override or insert variables into all templates.
 */
/* -- Delete this line if you want to use these functions
function genesis_SUBTHEME_preprocess(&$vars, $hook) {
}
function genesis_SUBTHEME_process(&$vars, $hook) {
}
// */

/**
 * Override or insert variables into the html templates.
 */
/* -- Delete this line if you want to use these functions
function genesis_SUBTHEME_preprocess_html(&$vars) {
  // Uncomment the folowing line to add a conditional stylesheet for IE 7 or less.
  // drupal_add_css(path_to_theme() . '/css/ie/ie-lte-7.css', array('weight' => CSS_THEME, 'browsers' => array('IE' => 'lte IE 7', '!IE' => FALSE), 'preprocess' => FALSE));
}
function genesis_SUBTHEME_process_html(&$vars) {
}
// */

/**
 * Override or insert variables into the page templates.
 */
function genesis_coldsleep_preprocess_page(&$vars) {
}
function genesis_coldsleep_process_page(&$vars) {
  $path = drupal_get_path_alias($_GET['q']);
  $paths = explode('/', $path);
  $vars['top_title'] = $vars['title'];
  if ($paths[0] == 'support') {
    $vars['top_title'] = t('Support');
  }
  else {
    unset($vars['title']);
  }
}

/**
 * Override or insert variables into the node templates.
 */
/* -- Delete this line if you want to use these functions
function genesis_SUBTHEME_preprocess_node(&$vars) {
}
function genesis_SUBTHEME_process_node(&$vars) {
}
// */

/**
 * Override or insert variables into the comment templates.
 */
/* -- Delete this line if you want to use these functions
function genesis_SUBTHEME_preprocess_comment(&$vars) {
}
function genesis_SUBTHEME_process_comment(&$vars) {
}
// */

/**
 * Override or insert variables into the block templates.
 */
/* -- Delete this line if you want to use these functions
function genesis_SUBTHEME_preprocess_block(&$vars) {
}
function genesis_SUBTHEME_process_block(&$vars) {
}
// */

/**
 * Override or insert variables into the menu item link templates.
 */
function genesis_coldsleep_menu_item_link($link) {
  // doesn't matter old code
  if (empty($link['localized_options'])) {
    $link['localized_options'] = array();
  }

  $current_path = drupal_get_path_alias($_GET['q']);
  $current_path = preg_replace('/(\?|\/*\?).*$/', '', $current_path) .'/';

  if (strpos($current_path, drupal_get_path_alias($link['href']) .'/') !== FALSE) {
    if (isset($link['localized_options']['attributes']['class'])) {
      $link['localized_options']['attributes']['class'] .= ' active';
    }
    else {
      $link['localized_options']['attributes']['class'] = 'active';
    }
  }

  return l($link['title'], $link['href'], $link['localized_options']);
}
