<?php

function intranet_preprocess_page(&$vars, $hook) {
	if(true){
		drupal_add_js(array('nyccIntranetTheme' => array('responsive_menu_enable_width' => theme_get_setting('responsive_menu_enable_width'))), 'setting');
		$vars['scripts'] = drupal_get_js();	
	}
}
