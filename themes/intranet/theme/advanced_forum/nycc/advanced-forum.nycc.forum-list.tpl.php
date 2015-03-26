<?php
/**
 * @file
 * Default theme implementation to display a list of forums and containers.
 *
 * Available variables:
 * - $forums: An array of forums and containers to display. It is keyed to the
 *   numeric id's of all child forums and containers.
 * - $forum_id: Forum id for the current forum. Parent to all items within
 *   the $forums array.
 *
 * Each $forum in $forums contains:
 * - $forum->is_container: Is TRUE if the forum can contain other forums. Is
 *   FALSE if the forum can contain only topics.
 * - $forum->depth: How deep the forum is in the current hierarchy.
 * - $forum->zebra: 'even' or 'odd' string used for row class.
 * - $forum->name: The name of the forum.
 * - $forum->link: The URL to link to this forum.
 * - $forum->description: The description of this forum.
 * - $forum->new_topics: True if the forum contains unread posts.
 * - $forum->new_url: A URL to the forum's unread posts.
 * - $forum->new_text: Text for the above URL which tells how many new posts.
 * - $forum->old_topics: A count of posts that have already been read.
 * - $forum->total_posts: The total number of posts in the forum.
 * - $forum->last_reply: Text representing the last time a forum was posted or
 *   commented in.
 * - $forum->forum_image: If used, contains an image to display for the forum.
 *
 * @see template_preprocess_forum_list()
 * @see theme_forum_list()
 */
?>

<?php
/*
  The $tables variable holds the individual tables to be shown. A table is
  either created from a root level container or added as needed to hold root
  level forums. The following code will loop through each of the tables.
  In each table, it loops through the items in the table. These items may be
  subcontainers or forums. Subcontainers are printed simply with the name
  spanning the entire table. Forums are printed out in more detail. Subforums
  have already been attached to their parent forums in the preprocessing code
  and will display under their parents.
 */
?>

<?php foreach ($tables as $table_id => $table): ?>
<div class="forum" id="forum-<?php print $table_id; ?>">
  <?php $table_info = $table['table_info']; ?>
    
    <div class="forum-table-superheader">
        <div class="forum-table-name">
            <?php if (empty($table_info->link)): ?>
                <?php print $table_info->name; ?>
            <?php else: ?>
                <a href="<?php print $table_info->link; ?>"><?php print $table_info->name; ?></a>
            <?php endif; ?>
        </div>
        <?php if ($collapsible): ?>
            <span id="forum-collapsible-<?php print $table_info->tid; ?>" class="forum-collapsible" >&nbsp;</span>
        <?php endif; ?>
        <div class="forum-table-description"><?php print $table_info->description; ?></div>
    </div>

    <div id="forum-table-<?php print $table_info->tid; ?>" class="forum-wrapper">
        <?php foreach ($table['items'] as $item_id => $item): ?>
              <div class="subscribe-button">
                  <?php print flag_create_link('subscribe_to_forum', $item_id); ?> 
              </div>
            
            <div class="forum-item pull-left <?php print $item->zebra; ?> container-<?php print $item_id; ?>-child">


                <div class="forum-image pull-left">
                    <?php
                      if(isset($item->forum_image)){
                        print $item->forum_image;
                      }
                    ?>
                </div>

                <div class="forum-detail pull-left">
                    <a href="<?php print $item->link; ?>" title="Visit the <?php print $item->name; ?> forum">
                        <h3>
                            <?php print $item->name; ?>
                        </h3>
                    </a>
                    <a href="<?php print $item->link; ?>" title="Visit the <?php print $item->name; ?> forum">    
                        <?php if (!empty($item->description)): ?>
                            <small>
                                <?php print $item->description; ?>
                            </small>                           
                        <?php endif; ?>
                    </a>
                </div>

                <div class="pull-right forum-info-square">
                    <h4>Posts</h4>
                    <span>
                        <?php print $item->total_posts ?>
                    </span>
                </div>
                <div class="pull-right forum-info-square grey">
                    <h4>Topics</h4>
                    <span>
                        <?php print $item->total_topics ?>
                    </span>
                </div>
            </div>
            <div class="forum-sub">
                <?php /* Display the last post details */ ?>
                
                <div class="last-post">
                    Last Post: <?php print $item->last_post ?>
                </div>

                <?php /* Display subforums if we've any... */?>
                <?php if (!empty($item->subforums)): ?>
                <div class="forum-subforums">
                    <span class="forum-subforums-label">
                        <?php print t("Subforums") ?>:
                    </span> 
                    <?php print $item->subforums; ?>
                </div>
                <?php endif; ?>
            </div>
        <?php endforeach; ?>
    </div>
</div>
<?php endforeach; ?>