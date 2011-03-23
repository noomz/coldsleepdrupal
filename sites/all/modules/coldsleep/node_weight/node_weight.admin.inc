<?php
/**
 * Settings form
 */
function node_weight_admin_settings_form(){
	$form['node_weight_allow_type'] = array(
		'#type' => 'checkboxes',
		'#title' => t('Allow content type'),
		'#options' => node_type_get_names(),
		'#default_value' => variable_get('node_weight_allow_type', array()),
		'#description' => t('Select content type to use node weight manager.'),
	);
  $form['#submit'][] = 'node_weight_admin_settings_form_submit';
	return system_settings_form($form);
}

/**
 * Settings form submit
 */
function node_weight_admin_settings_form_submit($form, $form_state){
	variable_set('node_weight_allow_type', $form_state['values']['node_weight_allow_type']);
	foreach ($form_state['values']['node_weight_allow_type'] as $type => $value) {
		if ($value) {
      node_weight_enable_content_type($value);
    }
	}
}

/**
 * Build the Node weight select type overview form.
 * Loads all node and builds an overview form with weight elements
 *
 * @ingroup forms
 * @see theme_node_weight_type_form()
 */
function node_weight_type_form() {
	$type = variable_get('node_weight_allow_type', NULL);
	$rows = array();
	if ($type) {
		foreach ($type as $key => $value) {
			if ($value) {
				$rows[] = array(array('data' => l($key, 'admin/content/node_weight/config/'.$key)));
			}
		}
	}
	if (count($rows) > 0) {
		$header = array(t('Content Type'));
		return theme('table', array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('id' => 'node-weight-type')
		));
	}
	else {
		return 'No content type to select, you can setting '. l('here', 'admin/content/node_weight/config', array('query' => drupal_get_destination()));
	}
}

/**
 * Build the Node weight overview form.
 * Loads all node and builds an overview form with weight elements
 *
 * @ingroup forms
 * @see _node_weight_overview_field()
 * @see theme_node_weight_overview_form()
 */
function node_weight_overview_form(&$node, $form_state, $node_type = NULL, $is_merge = FALSE) {
	$allow_type = variable_get('node_weight_allow_type', NULL);
	if ($allow_type) {
		foreach ($allow_type as $allow => $value) {
			if ($value) {
				$allow_types[] = $allow;
			}
		}
		if (isset($allow_types) && in_array($node_type, $allow_types)) {
		  $nodes = array();
			$result = db_query("SELECT n.nid, n.title, n.type, nw.weight FROM {node} AS n LEFT JOIN {node_weight} AS nw ON n.nid = nw.nid WHERE n.type = :type ORDER BY nw.weight, n.created DESC", array(':type' => $node_type));
			foreach ($result as $node) {
				$nodes[$node->nid] = $node;
			}

      $oform['#tree'] = TRUE;
      $oform['#theme'] = 'node_weight_overview_form';
			$oform['create_new'] = array(
			  '#type' => 'markup',
			  '#markup' => '<ul class="action-links"><li>' . l('Add new '.$node_type, 'node/add/'.str_replace('_', '-', $node_type), array('query' => array('destination' => $_GET['q']))) . '</li></ul>',
			);
			if ($nodes) {
        $settings = array(
          'delta' => $node_type,
          'display_title' => variable_get('nw_display_title_'.$node_type),
          'display_body' => variable_get('nw_display_title_'.$node_type),
        );
        $oform['delta'] = array('#type' => 'value', '#value' => $settings['delta']);
        $oform['display_title'] = array('#type' => 'value', '#value' => $settings['display_title']);
        $oform['display_body'] = array('#type' => 'value', '#value' => $settings['display_body']);
				foreach ($nodes as $nid => $node) {
					$oform[$nid] = _node_weight_overview_field($node, $settings);
				}

			}
			if (!isset($oform)) {
				drupal_goto('admin/content/node_weight');
			}

      if ($is_merge) {
        $oform['#is_merge'] = TRUE;
        $form['node_weight'] = array(
          '#type' => 'fieldset',
          '#title' => t('Node order'),
          '#tree' => TRUE,
          '#collapsible' => TRUE,
          '#collapsed' => FALSE,
          '#weight' => -10,
        );
        $form['node_weight'] = array_merge($form['node_weight'], $oform);
      }
      else {
        $oform['#is_merge'] = FALSE;
        $oform['submit'] = array(
          '#type' => 'submit',
          '#value' => t('Save changes'),
          '#disabled' => empty($nodes),
        );

        $form = $oform;
      }

			return $form;
		}
		else {
		  drupal_goto('admin/content/node_weight');
		}
  }
  else {
		$form['error'] = array(
			'#type' => 'markup',
			'#markup' => 'No content type to select, you can setting '. l('here', 'admin/content/node_weight/config', array('query' => drupal_get_destination())),
		);
		return $form;
	}
}

/**
* General submit handler for node_weight's overview form.
*
* Updates the weights of all nodes on the form.
*
* @ingroup formapi
* @see node_weight_overview_form()
*/
function node_weight_overview_form_submit($form, &$form_state) {
  $nodes = $form_state['values'];
  foreach($nodes as $node) {
    db_update("node_weight")
    ->fields(array(
    'weight' => $node['weight']
    ))
    ->condition('nid',$node['nid'])
    ->execute();
  }
}

/**
 * Build the overview form fields.
 *
 * This internal function should not be called outside the node_weight module,
 *
 * @ingroup forms
 * @see node_weight_overview_form()
 */
function _node_weight_overview_field($node, $settings=array()) {
  $dummy = node_load($node->nid);
	$form['nid'] = array(
		'#type' => 'hidden',
		'#value' => $node->nid,
	);
  $form['image'] = array(
    '#type' => 'markup',
    '#markup' => theme('image_style', array(
      'style_name' => 'node_weight_table_thumb',
      'path' => $dummy->{'node_weight_'.$settings['delta'].'_image'}['und'][0]['uri'],
      //'alt' => $node->title,
      //'title' => $node->title,
    )),
  );
	$form['title'] = array(
		'#type' => 'markup',
		'#markup' => l($node->title, 'node/'.$node->nid),
    '#access' => $settings['display_title'],
	);
	$form['weight'] = array(
		'#type' => 'weight',
		'#default_value' => $node->weight,
	);
	$form['edit'] = array(
		'#type' => 'markup',
		'#markup' => l('edit', 'node/'.$node->nid.'/edit', array('query' => array('destination' => $_GET['q']))),
	);
	$form['delete'] = array(
		'#type' => 'markup',
		'#markup' => l('delete', 'node/'.$node->nid.'/delete', array('query' => array('destination' => $_GET['q']))),
	);
	return $form;
}
