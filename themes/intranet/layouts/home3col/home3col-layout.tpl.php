

<?php print render($page['topbar']); ?>

<?php print render($page['topsearch']); ?>

<div class="navbar">
  <div class="l-container">
      <?php print render($page['topmenu']); ?>
  </div>
</div>

<div class="l-container">


<div class="l-page">
<?php print $breadcrumb; ?>

    <div class="l-content" role="main">
      <a id="main-content"></a>
      <?php print render($title_prefix); ?>
      <?php if ($title): ?>
        <h1><?php print $title; ?></h1>
      <?php endif; ?>
      <?php print render($title_suffix); ?>
      <?php print $messages; ?>
      <?php print render($tabs); ?>
      <?php print render($page['help']); ?>
      <?php if ($action_links): ?>
        <ul class="action-links"><?php print render($action_links); ?></ul>
      <?php endif; ?>

      <?php print $feed_icons; ?>
    </div>

    <div class="left-col">
      <?php print render($page['3_col_left']); ?>
    </div>

    <div class="center-col">
      <?php print render($page['3_col_center']); ?>
    </div>

    <div class="right-col">
      <?php print render($page['3_col_right']); ?>
    </div>


    <div class="span-3col-content full-column">
      <?php print render($page['content']); ?>
    </div>

  <footer class="l-footer" role="contentinfo">
    <?php print render($page['footer']); ?>
  </footer>
</div>

</div>

</div>