<?php

/**
 *  @file
 *  Custom DS layout
 *  Simple Bootstrap grid - 3 rows : 1 col, 2 cols, 1 col
 *  Other examples / approaches to look at :
 *      http://foundation.zurb.com/templates.php
 *      http://csswizardry.com/2013/02/responsive-grid-systems-a-solution/
 *  
 *  @author Paulmicha
 */


/**
 *  Template "Grid 1r2c"
 */
function ds_bs3r1c2c1c()
{
    return array(
        'label' => t( 'Simple Bootstrap grid 3r1c2c1c' ),
        'regions' => array(
            
            //      The key of this region name is also the variable used in
            //      the template to print the content of that region.
            'top' => t( 'Top' ),
            'left' => t( 'Left' ),
            'right' => t( 'Right' ),
            'footer' => t( 'Footer' ),
        ),
        
        //      Uncomment if you want to include a CSS file for this layout (example_layout.css)
        // 'css' => TRUE,
        
        //      Uncomment if you want to include a preview for this layout (example_layout.png)
        'image' => TRUE,
    );
}


?>