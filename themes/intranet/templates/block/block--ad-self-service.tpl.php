<?php
	global $user;
	$renderBlock = true;

	if(empty($user->ldap_user_puid)){
		$renderBlock = false;
	}
?>

<?php if ($renderBlock): ?>
	<div<?php print $attributes; ?>>
	  <?php print render($title_prefix); ?>
	  <?php if ($block->subject): ?>
	    <h3<?php print $title_attributes; ?>><?php print $block->subject; ?></h3>
	  <?php endif; ?>
	  <?php print render($title_suffix); ?>
	  <div<?php print $content_attributes; ?>>
	    <?php print $content; ?>
	  </div>
	</div>
<?php endif; ?>