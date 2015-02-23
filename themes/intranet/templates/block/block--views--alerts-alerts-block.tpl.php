<?php

/**
 * @file
 * Omega's implementation to display a block.
 *
 * Available variables:
 * - $block->subject: Block title.
 * - $content: Block content.
 * - $block->module: Module that generated the block.
 * - $block->delta: An ID for the block, unique within each module.
 * - $block->region: The block region embedding the current block.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - block: The current template type, i.e., "theming hook".
 *   - block-[module]: The module generating the block. For example, the user
 *     module is responsible for handling the default user navigation block. In
 *     that case the class would be 'block-user'.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Helper variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $block_zebra: Outputs 'odd' and 'even' dependent on each block region.
 * - $zebra: Same output as $block_zebra but independent of any block region.
 * - $block_id: Counter dependent on each block region.
 * - $id: Same output as $block_id but independent of any block region.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 * - $block_html_id: A valid HTML ID and guaranteed unique.
 *
 * @see template_preprocess()
 * @see template_preprocess_block()
 * @see template_process()
 *
 * @ingroup themeable
 */
?>

<?php if(user_is_logged_in() == TRUE): ?>
	<div class="user-info-wrapper">
	  	<div class="pull-right top-bar-widgets">
			<?php
				global $user;
				global $base_url;
				$userpath =  $base_url . '/user/' . $user->uid;
			?>
			<div class="user-info-wrapper-toggle pull-right">
				<i class="fa fa-angle-double-down fa-2x" data-ico="down"></i>
			</div>
		  	<a class="view-profile pull-right" href="<?php print($userpath) ?>">View My Profile</a>
		  	<div class="pull-right">
		    <?php
		      $user = user_load($user->uid);
		      $imagePath = 'public://silhouette_png.png';
		      if($user->picture){
		      	$imagePath = $user->picture->uri;
		      }
		    ?>
		      <a href="<?php print($userpath) ?>">
		      	<?php print theme('image_style', array('path' => $imagePath, 'style_name' => 'topprofile', 'alt' => format_username($user). ' profile picture')); ?>
		      </a>
		    
		 	</div>
			<?php print $content; ?>
    	</div>

		<div class="pull-right top-bar-text">
			<?php print format_username($user) ?>
		</div>
	</div>
<?php endif; ?>
