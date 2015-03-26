<?php

/**
 * @file
 * Template to display a list of rows.
 */
?>

  <?php
    $my_total = 0;
  ?>

  <div class="dropdown pull-right">
    <ul class="dropdown-menu dropdown-alerts" role="menu">
      <?php foreach ($rows as $delta => $row): ?>
      	<?php $my_total++; ?>
      	<?php if($my_total < 6): ?>
          <li>
            <?php print $row; ?>
          </li>
        <?php endif; ?>
      <?php endforeach; ?>
    </ul>
    <a class="dropdown-toggle pull-right alert-link" data-toggle="dropdown">
      <i class="fa fa-bell"></i> &nbsp;
      <?php print $my_total; ?>
    </a>
  </div>

