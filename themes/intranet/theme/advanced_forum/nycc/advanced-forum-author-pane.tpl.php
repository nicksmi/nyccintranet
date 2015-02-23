<?php
/**
 * @file
 * Theme implementation to display information about the post/profile author.
 *
 * See author-pane.tpl.php in Author Pane module for a full list of variables.
 */
?>

<?php
  // This bit of debugging info will show the full path to and name of this
  // template file to make it easier to figure out which template is
  // controlling which author pane.
  if (!empty($show_template_location)) {
    print __FILE__;
  }
?>

<div class="author-pane">
 <div class="author-pane-inner">
    <?php /* General section */ ?>
    <div class="author-pane-section author-pane-general">
        <div class="author-bar">
            <?php /* User picture / avatar (has div in variable) */ ?>
            <?php if (!empty($picture)): ?>
                <?php print $picture; ?>
            <?php endif; ?>
            <?php /* Account name */ ?>
            <div class="author-pane-line author-name">
                <?php print $account_name; ?>
            </div>
        </div>

        <div class="author-info">
          <?php /* Online status */ ?>
          <?php if (!empty($online_status)): ?>
            <div class="author-pane-line <?php print $online_status_class ?>">
               <span class="author-pane-label">Availability:</span>
               <span class="online-status"><?php print $online_status; ?></span>
            </div>
          <?php endif; ?>

          <?php /* Last active */ ?>
          <?php if (!empty($last_active)): ?>
            <div class="author-pane-line">
               <span class="author-pane-label"><?php print t('Last seen'); ?>:</span> <?php print t('!time ago', array('!time' => $last_active)); ?>
            </div>
          <?php endif; ?>

        </div>
    </div>

    <?php /* Contact section */ ?>
    <div class="author-pane-section author-pane-contact">
      <?php /* Contact / Email */ ?>
      <?php if (!empty($contact)): ?>
        <div class="author-pane-line author-pane-link-line author-contact">
          <?php print $contact; ?>
        </div>
      <?php endif; ?>

      <?php /* Private message */ ?>
      <?php if (!empty($privatemsg)): ?>
        <div class="author-pane-line author-pane-link-line author-privatemsg">
          <?php print $privatemsg; ?>
        </div>
      <?php endif; ?>

      <?php /* User relationships */ ?>
      <?php if (!empty($user_relationships)): ?>
        <div class="author-pane-line author-pane-link-line author-user-relationship">
          <?php print $user_relationships; ?>
        </div>
      <?php endif; ?>

      <?php /* Flag friend */ ?>
      <?php if (!empty($flag_friend)): ?>
        <div class="author-pane-line author-pane-link-line author-flag-friend">
          <?php print $flag_friend; ?>
        </div>
      <?php endif; ?>
    </div>

    <?php /* Admin section */ ?>
    <div class="author-pane-section author-pane-admin">
      <?php /* IP */ ?>
      <?php if (!empty($user_stats_ip)): ?>
        <div class="author-pane-line author-ip">
          <span class="author-pane-label"><?php print t('IP'); ?>:</span> <?php print $user_stats_ip; ?>
        </div>
      <?php endif; ?>

     <?php /* Fasttoggle block */ ?>
     <?php if (!empty($fasttoggle_block_author)): ?>
        <div class="author-fasttoggle-block"><?php print $fasttoggle_block_author; ?></div>
      <?php endif; ?>
    </div>
  </div>
</div>