

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

      <div class="home-left-col">


        <?php print render($page['home_news']); ?>

        <?php print render($page['home_main']); ?>

      </div>

      <div class="home-right-col">

        <?php print render($page['home_right']); ?>

      </div>

      <div class="home-full-col full-column">

        <?php print render($page['home_full']); ?>

      </div>
  </div>


  <footer class="l-footer" role="contentinfo">
    <?php print render($page['footer']); ?>
  </footer>

</div>
