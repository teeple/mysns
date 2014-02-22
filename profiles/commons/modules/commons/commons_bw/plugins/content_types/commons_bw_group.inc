<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Commons Group Browsing widget'),
  'description' => t('Commons Group Browsing widget.'),
  'category' => t('Commons'),
  'single' => TRUE,
  'content type' => 'commons_bw_group',
  'all contexts' => TRUE,
);
 
/**
* Output function for the '[content_type]' content type.
*/
function commons_bw_commons_bw_group_content_type_render($subtype, $conf, $panel_args, $context) {
  $context = array_shift($context);
  $node = !empty($context->data) ? $context->data : NULL;

	// dpm( $node, 'bw_group content type render');

  $block = new stdClass();
  $block->title = '';

	// bhtak 2014/02/20
	// get all groups contents
	if ( ! empty( $node)) {
		// it has context data
		$widget = commons_bw_generate_group_widget($node);
		$block->content = drupal_render($widget['content']);
	}
	else {
		$groups = og_get_entity_groups( 'user');
		if ( isset( $groups['node'])) {
			$tabs = array();
			$weight = 0;

			foreach( $groups['node'] as $nid) {
				$node = node_load( $nid);
				$widget = commons_bw_generate_group_widget($node);

				$tabs[$nid] = array(
						'title' => $node->title,
						'contents' => array( 
							'#markup' => drupal_render( $widget['content']),
							'weight' => $weight++
							),
					);
				//dpm( $node, 'group node');
				//dpm( $tabs[$nid], 'Qtab');
			}
			$settings = array('style' => 'Navlist', 'ajax' => TRUE, 'html' => TRUE);
			$widget = quicktabs_build_quicktabs( 'gid', $settings, $tabs);
			//dpm( $widget, 'final qt');
			$block->content = drupal_render($widget['content']);
		}
	}

  return $block;
}
 
/**
* Returns an edit form for the custom type.
*/
function commons_bw_commons_bw_group_content_type_edit_form($form, $form_state) {
  return $form;
}
 
/**
* Returns an edit form for the custom type.
*/
function commons_bw_commons_bw_group_content_type_edit_form_submit($form, $form_state) {
  return $form;
}
