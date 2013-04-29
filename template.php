<?php

/**
 *  @file
 *  Main template.php file
 *  @author Paulmicha
 */

$theme_path = drupal_get_path( 'theme', 'bootship' );
include $theme_path ."/template_form.inc";
include $theme_path ."/template_menu.inc";


/**
 *  Implement hook_preprocess_page()
 *  -> includes Bootstrap base JS files,
 *  requires sites/all/libraries/bootstrap in place
 */
function bootship_preprocess_page( &$vars, $hook )
{
    drupal_add_js( 'sites/all/libraries/bootstrap/js/bootstrap-alert.js' );
    drupal_add_js( 'sites/all/libraries/bootstrap/js/bootstrap-button.js' );
    drupal_add_js( 'sites/all/libraries/bootstrap/js/bootstrap-dropdown.js' );
    drupal_add_js( 'sites/all/libraries/bootstrap/js/bootstrap-collapse.js' );
    drupal_add_js( 'sites/all/libraries/bootstrap/js/bootstrap-transition.js' );
}



/**
 *  Implement theme_menu_local_tasks()
 *  @see http://api.drupal.org/api/drupal/includes%21menu.inc/function/theme_menu_local_tasks/7
 *
 *  Returns HTML for primary and secondary local tasks.
 *
 *  @param $variables
 *   An associative array containing:
 *     - primary: (optional) An array of local tasks (tabs).
 *     - secondary: (optional) An array of local tasks (tabs).
 *
 *  @ingroup themeable
 *  @see menu_local_tasks()
 */
function bootship_menu_local_tasks( &$variables )
{
    $output = '';
    if ( !empty( $variables[ 'primary' ]))
    {
        $variables['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>';
        $variables['primary']['#prefix'] .= '<ul class="nav nav-tabs primary">';
        $variables['primary']['#suffix'] = '</ul>';
        $output .= drupal_render($variables['primary']);
    }
    if ( !empty( $variables[ 'secondary' ]))
    {
        $variables['secondary']['#prefix'] = '<h2 class="element-invisible">' . t('Secondary tabs') . '</h2>';
        $variables['secondary']['#prefix'] .= '<ul class="nav nav-pills secondary">';
        $variables['secondary']['#suffix'] = '</ul>';
        $output .= drupal_render($variables['secondary']);
    }
    return $output;
}



/**
 *  Implement theme_breadcrumb()
 *
 *  Returns HTML for a breadcrumb trail.
 *  @param $variables
 *    An associative array containing:
 *    - breadcrumb: An array containing the breadcrumb links.
 */
function bootship_breadcrumb( $variables )
{
    $output = '';
    $breadcrumb = $variables[ 'breadcrumb' ];
    
    //      update 18:26 21/01/2013 - hide breadcrumb when there's only "home"
    if ( count( $breadcrumb ) == 1 )
        return '';
    
    if ( !empty( $breadcrumb ))
    {
        //      Provide a navigational heading to give context for breadcrumb links to
        //      screen-reader users. Make the heading invisible with .element-invisible.
        $output .= '<h2 class="element-invisible">' . t( 'You are here' ) . '</h2>';
        $output .= '<ul class="breadcrumb">'. implode( ' <span class="divider">/</span> ', $breadcrumb ) .'</ul>';
    }
    
    return $output;
}



/**
 *  Implement theme_status_messages()
 *  @see http://api.drupal.org/api/drupal/includes%21theme.inc/function/theme_status_messages/7
 */
function bootship_status_messages( $variables )
{
    $display = $variables[ 'display' ];
    $output = '';
    $status_heading = array(
        'status' => t('Status message'),
        'error' => t('Error message'),
        'warning' => t('Warning message'),
    );
    foreach ( drupal_get_messages( $display ) as $type => $messages )
    {
        //$output .= "<div class=\"messages $type\">\n";
        $output .= "<div class=\"alert alert-". str_replace( array( 'warning', 'status' ), array( 'info', 'success' ), $type ) ."\">\n<a class=\"close\" data-dismiss=\"alert\">×</a>";
        if (!empty($status_heading[$type])) {
            $output .= '<h2 class="element-invisible">' . $status_heading[$type] . "</h2>\n";
        }
        if (count($messages) > 1)
        {
            $output .= " <ul>\n";
            foreach ($messages as $message)
            {
                //$output .= '  <li>' . $message . "</li>\n";
                
                //      update 16:08 21/01/2013 - adds FontAwesome icons before messages
                $output .= '  <li><i class="icon-'. str_replace( array( 'status', 'warning', 'error' ), array( 'ok', 'warning-sign', 'remove' ), $type ) .'"></i>&nbsp;' . $message . "</li>\n";
            }
            $output .= " </ul>\n";
        }
        else {
            //$output .= $messages[0];
            $output .= '<i class="icon-'. str_replace( array( 'status', 'warning', 'error' ), array( 'ok', 'warning-sign', 'remove' ), $type ) .'"></i>&nbsp;'. $messages[ 0 ];
        }
        $output .= "</div>\n";
    }
    return $output;
}



/**
 * Returns HTML for a query pager.
 *
 * Menu callbacks that display paged query results should call theme('pager') to
 * retrieve a pager control so that users can view other results. Format a list
 * of nearby pages with additional query results.
 *
 * @param $vars
 *   An associative array containing:
 *   - tags: An array of labels for the controls in the pager.
 *   - element: An optional integer to distinguish between multiple pagers on
 *     one page.
 *   - parameters: An associative array of query string parameters to append to
 *     the pager links.
 *   - quantity: The number of pages in the list.
 *
 * @ingroup themeable
 */
function bootship_pager( $variables )
{
  $output = "";
  $tags = $variables['tags'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $quantity = $variables['quantity'];

  global $pager_page_array, $pager_total;

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);
  // current is the page we are currently paged to
  $pager_current = $pager_page_array[$element] + 1;
  // first is the first page listed by this pager piece (re quantity)
  $pager_first = $pager_current - $pager_middle + 1;
  // last is the last page listed by this pager piece (re quantity)
  $pager_last = $pager_current + $quantity - $pager_middle;
  // max is the maximum page number
  $pager_max = $pager_total[$element];
  // End of marker calculations.

  // Prepare for generation loop.
  $i = $pager_first;
  if ($pager_last > $pager_max)
  {
    // Adjust "center" if at end of query.
    $i = $i + ($pager_max - $pager_last);
    $pager_last = $pager_max;
  }
  if ($i <= 0)
  {
    // Adjust "center" if at start of query.
    $pager_last = $pager_last + (1 - $i);
    $i = 1;
  }

  // End of generation loop preparation.
  $li_first = theme('pager_first', array('text' => (isset($tags[0]) ? $tags[0] : t('first')), 'element' => $element, 'parameters' => $parameters));
  $li_previous = theme('pager_previous', array('text' => (isset($tags[1]) ? $tags[1] : t('previous')), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
  $li_next = theme('pager_next', array('text' => (isset($tags[3]) ? $tags[3] : t('next')), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
  $li_last = theme('pager_last', array('text' => (isset($tags[4]) ? $tags[4] : t('last')), 'element' => $element, 'parameters' => $parameters));

  if ($pager_total[$element] > 1)
  {
    if ($li_previous) {
      $items[] = array(
        'class' => array('prev'), 
        'data' => $li_previous,
      );
    }

    // When there is more than one page, create the pager list.
    if ($i != $pager_max)
    {
      if ($i > 1) {
        $items[] = array(
          'class' => array('pager-ellipsis', 'disabled'),
          'data' => '<a>…</a>',
        );
      }
      // Now generate the actual pager piece.
      for (; $i <= $pager_last && $i <= $pager_max; $i++)
      {
        if ($i < $pager_current) {
          $items[] = array(
           // 'class' => array('pager-item'), 
            'data' => theme('pager_previous', array('text' => $i, 'element' => $element, 'interval' => ($pager_current - $i), 'parameters' => $parameters)),
          );
        }
        if ($i == $pager_current) {
          $items[] = array(
            'class' => array('active'), // Add the active class 
            'data' => l($i, '#', array('fragment' => '','external' => TRUE)),
          );
        }
        if ($i > $pager_current) {
          $items[] = array(
            //'class' => array('pager-item'), 
            'data' => theme('pager_next', array('text' => $i, 'element' => $element, 'interval' => ($i - $pager_current), 'parameters' => $parameters)),
          );
        }
      }
      if ($i < $pager_max) {
        $items[] = array(
          'class' => array('pager-ellipsis', 'disabled'),
          'data' => '<a>…</a>',
        );
      }
    }
    // End generation.
    if ($li_next)
    {
      $items[] = array(
        'class' => array('next'), 
        'data' => $li_next,
      );
    }
    
    return '<div class="pagination pagination-centered">'. theme('item_list', array(
      'items' => $items, 
    )) . '</div>';
  }
  
  return $output;
}


