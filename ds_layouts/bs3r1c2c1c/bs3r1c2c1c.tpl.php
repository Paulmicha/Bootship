<?php

/**
 *  @file
 *  Simple Bootstrap grid - 3 rows : 1 col, 2 cols, 1 col
 *  
 *  Other examples / approaches to look at :
 *      http://foundation.zurb.com/templates.php
 *      http://csswizardry.com/2013/02/responsive-grid-systems-a-solution/
 *  
 *  4 regions :
 *      'top' => t( 'Top' )
 *      'left' => t( 'Left' )
 *      'right' => t( 'Right' )
 *      'footer' => t( 'Footer' )
 *  
 *  @author Paulmicha
 */

?>
<<?php print $layout_wrapper; print $layout_attributes; ?> class="<?php print $classes;?>">

    <!-- Needed to activate contextual links -->
    <?php if ( isset( $title_suffix[ 'contextual_links' ])): ?>
        <?php print render( $title_suffix[ 'contextual_links' ]); ?>
    <?php endif; ?>

    <!-- regions -->
    <?php if ( !empty( $top )): ?>
    <div class="row-fluid">
        <<?php print $top_wrapper ?> class="<?php print !empty( $top_classes ) ? $top_classes : 'span12'; ?>">
            <?php print $top; ?>
        </<?php print $top_wrapper ?>>
    </div>
    <?php endif; ?>
    
    <?php if ( !empty( $left ) || !empty( $right )): ?>
    <div class="row-fluid">
        <?php if ( !empty( $left )): ?>
        <<?php print $left_wrapper ?> class="<?php print !empty( $left_classes ) ? $left_classes : 'span6'; ?>">
            <?php print $left; ?>
        </<?php print $left_wrapper ?>>
        <?php endif; ?>
        <?php if ( !empty( $right )): ?>
        <<?php print $right_wrapper ?> class="<?php print !empty( $right_classes ) ? $right_classes : 'span6'; ?>">
            <?php print $right; ?>
        </<?php print $right_wrapper ?>>
        <?php endif; ?>
    </div>
    <?php endif; ?>
    
    <?php if ( !empty( $footer )): ?>
    <div class="row-fluid">
        <<?php print $footer_wrapper ?> class="<?php print !empty( $footer_classes ) ? $footer_classes : 'span12'; ?>">
            <?php print $footer; ?>
        </<?php print $footer_wrapper ?>>
    </div>
    <?php endif; ?>
    <!-- /regions -->

</<?php print $layout_wrapper ?>>

<!-- Needed to activate display suite support on forms -->
<?php if ( !empty( $drupal_render_children )): ?>
    <?php print $drupal_render_children ?>
<?php endif; ?>

