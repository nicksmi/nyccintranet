

<?php print render($page['topbar']); ?>


<?php print render($page['topsearch']); ?>

<div class="navbar">
  <div class="l-container">
    <?php print render($page['topmenu']); ?>
  </div>
</div>

<div class="l-container">

  <div class="l-page">

      <div class="home-left-col">

        <?php print $messages; ?>
        
        <?php print render($page['home_news']); ?>

        <?php print render($page['home_main']); ?>

      </div>

      <div class="home-right-col">

        <?php print render($page['home_right']); ?>

      </div>

  </div>


  <footer class="l-footer" role="contentinfo">
    <?php print render($page['footer']); ?>
  </footer>

</div>
