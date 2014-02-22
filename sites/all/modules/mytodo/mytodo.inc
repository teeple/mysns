<?php

function mytodo_entity_view($entity, $type, $view_mode, $langcode) 
{
	$links = mytodo_link($type, $entity, $view_mode == 'teaser');
	if (isset($links)) {
		$entity->content['links']['mytodo'] = array(
			'#theme' => 'links',
			'#links' => $links,
			'#attributes' => array('class' => array('links', 'inline')),
		);
	}
}

/**
 * Implements hook_link().
 *
 * This hook does not exist in Drupal 7, it is called from flag_entity_view().
 */
function mytodo_link($type, $object = NULL, $teaser = FALSE) {
  if (!isset($object) ) {
    return ;
  }
  global $user;

  // Get all possible flags for this content-type.
  /*
  $flags = flag_get_flags($type);

  foreach ($flags as $flag) {
    $content_id = $flag->get_content_id($object);

    if (!$flag->uses_hook_link($teaser)) {
      // Flag is not configured to show its link here.
      continue;
    }
    if (!$flag->access($content_id) && (!$flag->is_flagged($content_id) || !$flag->access($content_id, 'flag'))) {
      // User has no permission to use this flag or flag does not apply to this
      // content. The link is not skipped if the user has "flag" access but
      // not "unflag" access (this way the unflag denied message is shown).
      continue;
    }

    // The flag links are actually fully rendered theme functions.
    // The HTML attribute is set to TRUE to allow whatever the themer desires.
    $links['flag-' . $flag->name] = array(
      'title' => $flag->theme($flag->is_flagged($content_id) ? 'unflag' : 'flag', $content_id),
      'html' => TRUE,
    );
  }
  */

	if ( isset( $object->type) && $object->type != 'mytodo') {
		$links['mytodo'] = array(
		  'title' => 'ToDo',
		  'html' => TRUE,
		);
	}

  if (isset($links)) {
    return $links;
  }
}


/**
  * Implements hook_commons_bw_group_widget().
  */
function mytodo_commons_bw_group_widget() {
	return array(
		'mytodo' => array(
			'title' => 'ToDo',
			'type' => 'view',
			'vid' => 'commons_bw_mytodo',
			'display' => 'default',
			'weight' => 1,
			'bundle' => 'mytodo',
		),
	);
}


/**
	 * Implements hook_commons_bw_create_all_widget().
	  */
function mytodo_commons_bw_create_all_widget($group) {
	if (og_user_access('node', $group->nid, 'create mytodo content')) {
		dpm( 'create all widget');

		$link = l(t('Create a post'),'node/add/mytodo',
			array('attributes' => array('class' => 'mytodo-create'), 'query' => array('og_group_ref' => $group->nid))
		);

		return array(
			'mytodo' => array(
				'default' => TRUE,
				'link' => $link,
				'text' =>  t('Foster a topic through commenting'),
				'#weight' => -1,
				),
		);
	}
}

/**
 * Implements hook_views_pre_render().
function mytodo_views_pre_render(&$view) {
  if ($view->name == 'commons_bw_mytodo' && user_access('create mytodo')) {
	$group_id = $view->args[0];
	$view->attachment_before = l('Create a ToDo', 'node/add/mytodo', array('query' => array('og_group_ref' => $group_id)));
	}
}
 */


/**
   * Implements hook_form_FROM_ID_alter().
    */
function mytodo_form_commons_bw_partial_node_form_alter(&$form, &$form_state) {
	if (empty($form['#entity']) || $form['#entity']->type != 'mytodo') {
		return;
	}

	global $user;

	$language = $form['body']['#language'];
	$form['body'][$language][0]['value']['#title_display'] = 'invisible';
	$form['body'][$language][0]['value']['#required'] = TRUE;
	$form['body'][$language][0]['value']['#placeholder'] = t("What do you need to do ?");
	$form['body'][$language][0]['value']['#resizable'] = FALSE;

	//$language = $form['field_assignee']['#language'];
	$form['field_assignee'][$language]['#title_display'] = 'invisible';
	$form['field_assignee'][$language]['#default_value'] = $user->uid;

	// Set fields as hideable so the forms can be compacted.
	$form['body']['#attributes']['class'][] = 'trigger-field';
	foreach (array('field_media', 'field_image', 'og_group_ref', 'choice_wrapper', 'actions') as $field) {
		if (isset($form[$field])) {
			$form[$field]['#attributes']['class'][] = 'hideable-field';
		}
	}

	$form['actions']['submit']['#value'] = t('Save');
	$form['#pre_render'][] = 'mytodo_form_commons_bw_partial_node_form_after_build';

}

/**
* After-build call-back.
* See mytodo_form_commons_bw_partial_node_form_alter().
 */
function mytodo_form_commons_bw_partial_node_form_after_build($form) {
	$language = $form['body']['#language'];
	$form['body'][$language][0]['#pre_render'] = array();
	$form['body'][$language][0]['format']['#access'] = FALSE;
	$form['body'][$language][0]['value']['#rows'] = 3;

	dpm( $form, 'mytodo');
	return $form;
}


/**
	* add utility link 
	*/
function mytodo_commons_utility_links() {
	$links = array();

	if (user_is_logged_in()) {
		global $user;
		$account = $user;
		$links['todo']= array(
			'href' => 'mytodo/user/' . $account->uid ,
			'title' => t('ToDo'),
		);
	}

	return $links;
}

/** 
	* change views
function mytodo_views_pre_view(&$view, &$display_id, &$args) {
	if ( $view->name == 'commons_bw_mytodo') {
		$opts = $view->get_item($display_id, 'field', 'nothing');
		if (!empty($opts)) {
			dpm( $opts, 'opts');
			//$opts['alter']['text'] = base_path() . drupal_get_path('theme', 'THEME_NAME');
			$view->set_item($display_id, 'field', 'nothing', $opts);
		}
	}
}
	*/

function mytodo_views_post_render(&$view, &$output, &$cache) {
	if ( $view->name == 'commons_bw_mytodo') {
		// add check box in the output
		$output = strtr($output, array(
				'post-field-done-Uncompleted' => '<label class="checkbox"><input type="checkbox" name="checkbox-inline"><i></i></label>',
				'post-field-done-Completed' => '<label class="checkbox state-disabled"><input type="checkbox" name="checkbox-inline" checked="checked" disabled="disabled"> <i></i> </label>'
				));
	}
}
