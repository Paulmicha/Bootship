<?php

/**
 * @file
 * Provides menu-related theme overrides and implementations.
 */


/**
 *  Implement [theme]_menu_tree__menu_block__[block id number]()
 *  Based on module "menu_block"'s README.txt suggestions
 *  @see http://api.drupal.org/api/drupal/includes%21menu.inc/function/theme_menu_tree/7
 */
function one_shot_art_paris_menu_tree__menu_block__1( $variables ) {
    return '<ul class="nav">'. $variables[ 'tree' ] .'</ul>';
}


/**
 *  Implement [theme]_menu_link__menu_block__[block id number]()
 *  Based on module "menu_block"'s README.txt suggestions
 *  @see http://api.drupal.org/api/drupal/includes%21menu.inc/function/theme_menu_link/7
 */
function one_shot_art_paris_menu_link__menu_block__1( array $variables )
{
    $element = $variables[ 'element' ];
    $sub_menu = '';
    
    //      modif Paul 12:41 28/01/2013 - pour les niveaux suivants, on a besoin de la classe "dropdown"
    //      @see http://twitter.github.com/bootstrap/javascript.html#dropdowns
    if ( $element[ '#below' ])
    {
        $element[ '#attributes' ][ 'class' ][] = "dropdown";
        $sub_menu = drupal_render( $element[ '#below' ]);
    }
    $output = l( $element[ '#title' ], $element[ '#href' ], $element[ '#localized_options' ]);
    return '<li'. drupal_attributes( $element[ '#attributes' ]) .'>'. $output . $sub_menu ."</li>\n";
}



?>