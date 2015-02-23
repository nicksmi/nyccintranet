<article<?php print $attributes; ?>>
  <?php print render($title_prefix); ?>
  <div class="comment-title-bar">
      <div class="comment-author-image">
          <?php print $user_picture; ?>
      </div>

      <div class="comment-info">
          <h2 <?php print $title_attributes; ?>>
            <?php if ($new): ?>
              <mark class="new"><?php print $new; ?></mark>
            <?php endif; ?>

            <?php if(isset($title))
              {
                print $title;
              }
              print $author
            ?>
          </h2>
          <?php print render($title_suffix); ?>

          <?php print $created; ?>
      </div>

  </div>

  <div <?php print $content_attributes; ?>>
    <?php
      // We hide the links now so that we can render them later.
      hide($content['links']);
      print render($content);
    ?>
    <?php if ($signature): ?>
    <div class="user-signature comment__signature">
      <?php print $signature; ?>
    </div>
    <?php endif; ?>
  </div>

  <?php print render($content['links']) ?>
</article>
