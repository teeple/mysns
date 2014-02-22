<?php

mytodo_install();

/**
 * Implements hook_install().
 */
function mytodo_install() {
	// Create the default webform type.
	$mytodo_type = array(
		'type' => 'mytodo',
		'name' => t('My ToDo'),
		'base' => 'node_content',
		'description' => t('Create a new ToDo item.'),
		'custom' => TRUE,
		'modified' => TRUE,
		'locked' => FALSE,
	);

	$mytodo_type = node_type_set_defaults($mytodo_type);
	node_type_save($mytodo_type);
	node_add_body_field($mytodo_type);
}
