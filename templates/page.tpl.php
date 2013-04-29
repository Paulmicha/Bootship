<?php

/**
 *  Main page template
 *
 *  @extends sites/all/themes/mothership/mothership/templates/page.tpl.php
 *  @author Paulmicha
 */

//      debug
//kpr(get_defined_vars());
//kpr($theme_hook_suggestions);
//template naming
//page--[CONTENT TYPE].tpl.php

?>
<header role="banner" class="main-head container">
    
    <?php if ($logo): ?>
    <figure class="logo">
        <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home">
            <img src="<?php print $logo; ?>" alt="<?php print !empty($site_name) ? $site_name : t('Site Logo'); ?>" />
        </a>
    </figure>
    <?php endif; ?>
    
    <!-- .breadcrumb -->
    <?php print $breadcrumb; ?>
    <!-- /.breadcrumb -->
    
    <?php if($page['header']): ?>
    <div class="header-region container">
        <?php print render($page['header']); ?>
    </div>
    <?php endif; ?>
    
</header>

<!-- #main-content -->
<div role="main" id="main-content" class="container">

    <?php if($page['highlighted'] OR $messages){ ?>
    <div class="drupal-messages">
    <?php print render($page['highlighted']); ?>
    <?php print $messages; ?>
    </div>
    <?php } ?>
    
    <?php if ($title): ?>
    <div class="page-header">
        <?php print render($title_prefix); ?>
        <h1><?php print $title; ?></h1>
        <?php print render($title_suffix); ?>
    </div>
    <?php endif; ?>

    <?php if (isset($tabs['#primary'][0]) || isset($tabs['#secondary'][0])): ?>
    <nav class="tabs alt-tabs-layout"><?php print render($tabs); ?></nav>
    <?php endif; ?>

    <?php if ($action_links): ?>
    <ul class="action-links nav nav-pills"><?php print render($action_links); ?></ul>
    <?php endif; ?>
    
    <!-- region content -->
    <?php print render($page['content']); ?>
    <!-- /region content -->
    
</div>
<!-- /#main-content -->
    
<footer role="contentinfo" class="container">
    <!-- region footer -->
    <?php print render($page['footer']); ?>
    <!-- /region footer -->
</footer>


