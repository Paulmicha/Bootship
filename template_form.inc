<?php

/**
 * @file
 * Provides form-related theme overrides and implementations.
 */


/**
 * Implements theme_button().
 */
function bootship_button($variables)
{
    $variables['element']['#attributes']['class'][] = 'btn';
    //return theme_button($variables);
    
    $element = $variables['element'];
    $element['#attributes']['type'] = 'submit';
    element_set_attributes($element, array('id', 'name', 'value'));

    $element['#attributes']['class'][] = 'form-' . $element['#button_type'];
    if (!empty($element['#attributes']['disabled'])) {
        $element['#attributes']['class'][] = 'form-button-disabled';
    }

    //      debug
    //kpr( $variables );
    //dsm( $element[ '#parents' ][ 0 ]);
    //dsm( $element );
    
    //      update paul 01:52 15/01/2013 - types de boutons
    if ( $element[ '#array_parents' ][ 0 ] == "actions" )
        $element[ '#attributes' ][ 'class' ][] = 'btn-large';
    //if ( $element[ '#parents' ][ 0 ] == "submit" )
        //$element[ '#attributes' ][ 'class' ][] = 'btn-primary';
    
    //      update paul 19:21 27/01/2013 - moar colorz
    switch( $element[ '#parents' ][ 0 ])
    {
        case 'submit' :
            $element[ '#attributes' ][ 'class' ][] = 'btn-primary';
            break;
        case 'preview' :
            $element[ '#attributes' ][ 'class' ][] = 'btn-info';
            break;
        case 'delete' :
            $element[ '#attributes' ][ 'class' ][] = 'btn-danger';
            break;
    }
    
    //      update Paul 23:22 27/01/2013 - Buttons loading state
    //      @see http://twitter.github.com/bootstrap/javascript.html#buttons
    $element[ '#attributes' ][ 'data-loading-text' ] = t( "Loading..." );
    
    //      Add More
    if ( isset( $element[ '#submit' ]) && $element[ '#submit' ][ 0 ] == "field_add_more_submit" )
        $element[ '#attributes' ][ 'class' ][] = 'btn-inverse';
    
    return '<input' . drupal_attributes($element['#attributes']) . ' />';
}



/**
 * Implements theme_fieldset().
 *
 * Rather unfortunately, the default theme implementation includes some markup
 * (the 'fieldset-wrapper' div) that's (a) indispensible, and (b) untouchable
 * without copying in the entire function. In this case, were we only want to
 * add a single class to the div in question, this seems kind of wasteful.
 */
function bootship_fieldset($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id'));
  _form_set_class($element, array('form-wrapper'));

  $output = '<fieldset' . drupal_attributes($element['#attributes']) . '>';
  if (!empty($element['#title'])) {
    // Always wrap fieldset legends in a SPAN for CSS positioning.
    $output .= '<legend><span class="fieldset-legend">' . $element['#title'] . '</span></legend>';
  }
  // Add 'row-fluid' class to fieldset wrapper div so that, by adding Bootstrap
  // span classes to the sub-elements, we can theme forms in a very flexible way:
  $output .= '<div class="fieldset-wrapper row-fluid">';
  if (!empty($element['#description'])) {
    $output .= '<div class="fieldset-description">' . $element['#description'] . '</div>';
  }
  $output .= $element['#children'];
  if (isset($element['#value'])) {
    $output .= $element['#value'];
  }
  $output .= '</div>';
  $output .= "</fieldset>\n";
  return $output;
}


/**
 * Implements theme_file().
 */
function bootship_file($variables) {
  // Assign the Bootstrap class:
  _form_set_class($variables['element'], array('input-file'));
  // Set a reasonably low default size:
  $variables['element']['#attributes']['size'] = '22';
  return theme_file($variables);
}


/**
 * Implements theme_form().
 */
function bootship_form($variables)
{
    //$form_classes = implode(' ', array_map('_one_shot_art_paris_css_safe', theme_get_setting('one_shot_art_paris_form__classes')));
    //$variables['element']['#attributes']['class'] = $form_classes;
    //return theme_form($variables);
    
    $element = $variables['element'];
    if (isset($element['#action'])) {
        $element['#attributes']['action'] = drupal_strip_dangerous_protocols($element['#action']);
    }
    element_set_attributes($element, array('method', 'id'));
    if (empty($element['#attributes']['accept-charset'])) {
        $element['#attributes']['accept-charset'] = "UTF-8";
    }
    
    //      update paul 23:43 14/01/2013 - test class .well
    //      update 00:01 15/01/2013 - not pretty
    //isset( $element['#attributes']['class']) ?
    //    $element['#attributes']['class'] .= ' well' :
    //    $element['#attributes']['class'] = 'well' ;

    return '<form' . drupal_attributes($element['#attributes']) . ' role="form">' . $element['#children'] . '</form>';
}

/**
 * Implements theme_form_element().
 *
 * Original function's notes retained here for reference below. Note that, in
 * the current implementation:
 *
 * - the strategy has been to alter the core function reproduced here as little
 *   as possible;
 * - everything works for all stock Drupal form elements (if it doesn't, it's a
 *   bug!);
 * - no work has yet been done to make sure the Webform module's forms will
 *   render nicely;
 * - we have opted to retain most or all native Drupal classes in addition to
 *   adding Bootstrap classes;
 * - #title_display settings should work but may be fragile;
 *
 *
 * Returns HTML for a form element.
 *
 * Each form element is wrapped in a DIV container having the following CSS
 * classes:
 * - form-item: Generic for all form elements.
 * - form-type-#type: The internal element #type.
 * - form-item-#name: The internal form element #name (usually derived from the
 *   $form structure and set via form_builder()).
 * - form-disabled: Only set if the form element is #disabled.
 *
 * In addition to the element itself, the DIV contains a label for the element
 * based on the optional #title_display property, and an optional #description.
 *
 * The optional #title_display property can have these values:
 * - before: The label is output before the element. This is the default.
 *   The label includes the #title and the required marker, if #required.
 * - after: The label is output after the element. For example, this is used
 *   for radio and checkbox #type elements as set in system_element_info().
 *   If the #title is empty but the field is #required, the label will
 *   contain only the required marker.
 * - invisible: Labels are critical for screen readers to enable them to
 *   properly navigate through forms but can be visually distracting. This
 *   property hides the label for everyone except screen readers.
 * - attribute: Set the title attribute on the element to create a tooltip
 *   but output no label element. This is supported only for checkboxes
 *   and radios in form_pre_render_conditional_form_element(). It is used
 *   where a visual label is not needed, such as a table of checkboxes where
 *   the row and column provide the context. The tooltip will include the
 *   title and required marker.
 *
 * If the #title property is not set, then the label and any required marker
 * will not be output, regardless of the #title_display or #required values.
 * This can be useful in cases such as the password_confirm element, which
 * creates children elements that have their own labels and required markers,
 * but the parent element should have neither. Use this carefully because a
 * field without an associated label can cause accessibility challenges.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #title, #title_display, #description, #id, #required,
 *     #children, #type, #name.
 *
 * @ingroup themeable
 */
function bootship_form_element($variables) {

  $element = &$variables['element'];
  // This is also used in the installer, pre-database setup.
  $t = get_t();
  
  //        debug
  //dsm( $element[ '#type' ] );
  //if ( $element[ '#type' ] == "textfield" )
    //dsm( $element );

  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
  );

  // Add element #id for #type 'item'.
  if (isset($element['#markup']) && !empty($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  // Add element's #type and #name as class to aid with JS/CSS selectors.

  $attributes['class'] = array();
  if(! theme_get_setting('mothership_classes_form_wrapper_formitem')){
    $attributes['class'] = array('form-item');
  }

  //date selects need the form-item for the show/hide end date
	if(isset($element['#type'])){
	  if ($element['#type'] == 'date_select' OR $element['#type'] == 'date_text' OR $element['#type'] == 'date_popup' ){ //AND
	    $attributes['class'] = array('form-item');
	  }

	}

  if (!empty($element['#type'])) {
    if(!theme_get_setting('mothership_classes_form_wrapper_formtype')){
      $attributes['class'][] = 'form-type-' . strtr($element['#type'], '_', '-');
    }
  }
  if (!empty($element['#name'])) {
    if(!theme_get_setting('mothership_classes_form_wrapper_formname')){
      $attributes['class'][] = 'form-item-' . strtr($element['#name'], array(' ' => '-', '_' => '-', '[' => '-', ']' => ''));
    }
  }
  // Add a class for disabled elements to facilitate cross-browser styling.
  if (!empty($element['#attributes']['disabled'])) {
    $attributes['class'][] = 'form-disabled';
  }

  //if the form element is reguired add a form-required class
  if( !empty( $element['#required'] )) {
    $attributes['class'][] = 'form-required';
  }


  //freeform css class killing \m/
  if($attributes['class']){
    $remove_class_form = explode(", ", theme_get_setting('mothership_classes_form_freeform'));
    $attributes['class'] = array_values(array_diff($attributes['class'],$remove_class_form));
  }
  
    //      update Paul 11:56 21/01/2013 - need wrapper class
    //      @evol : only when prefixes don't contain any html
    //      update 12:29 21/01/2013 - doesn't work so well on dark BG
    /**
    if ( !empty( $element[ '#field_prefix' ]) && !empty( $element[ '#field_suffix' ]))
    {
        //      @evol 12:21 21/01/2013 - when I'll get more time I'll filter those cases
        //      in the meantime, we'll just use bootstrap wrapper classes
        //if ( !is_numeric( strpos( $element[ '#field_prefix' ], '<' )))
        
        $attributes['class'][] = "input-prepend input-append";
    }
    else if ( !empty( $element[ '#field_prefix' ]))
        $attributes['class'][] = "input-prepend";
    else if ( !empty( $element[ '#field_suffix' ]))
        $attributes['class'][] = "input-append";
    /**/
  
  
  //  update paul 21:08 27/01/2013 - pour les champs textes, un "row-fluid" autour, avec un "span12" comme classe pour l'input, ça rendrait peut-être pas mal
  //  ok, ça a pas l'air mal, mais rajouter ça aussi pour les textareas
  //  update 22:07 27/01/2013 - exclure les champs type "date" et "time"
  //  update 22:20 27/01/2013 - make it reusable, we'll need it in theme_textfield() and theme_textareas() as well for "span12"
  if ( _row_fluid_element_is_applicable( $element )) {
    $attributes[ 'class' ][] = "row-fluid";
  }
  
  
  if($attributes['class']){
    $output =  '<div' . drupal_attributes($attributes) . '>' . "\n";
  }else{
    $output =  "\n" . '<div>' . "\n";
  }

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  //        update Paul 11:36 21/01/2013 - add-on classes for form prefixes
  //        OR use "help-inline"
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix help-inline">' . $element['#field_prefix'] . '</span> ' : '';
  //$prefix = isset($element['#field_prefix']) ? '<span class="field-prefix add-on">' . $element['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix help-inline">' . $element['#field_suffix'] . '</span>' : '';
  //$suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix add-on">' . $element['#field_suffix'] . '</span>' : '';

  switch ($element['#title_display']) {
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;

    case 'after':
      $output .= ' ' . $prefix . $element['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $variables) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;
  }

  if (!empty($element['#description'])) {

    /*
    changes the description <div class="description"> to <small>
    */
    if(!theme_get_setting('mothership_classes_form_description')){
      $output .= "\n" . '<div class="description">' . $element['#description'] . "</div>\n";
    }else{
      $output .= "\n" . '<small>' . $element['#description'] . "</small>\n";
    }


  }

  $output .= "</div>\n";

  return $output;
}



/**
 *  Custom helper function to tell when "row-fluid" with "span12" for inputs is applicable
 *  @evol 22:24 27/01/2013 - configurable matching criterias
 *  return Boolean
 */
function _row_fluid_element_is_applicable( $element )
{
    //      This is for applying "row-fluid" on container element
    $element_types_whitelist = array( 'textfield', 'textarea' );
    
    //      This is for "span12" on input element
    $element_last_parent_blacklist = array( 'date', 'time', 'count_child', 'INTERVAL', 'INTERVAL_child' );
    
    $test_last_parent = @array_pop( $element[ '#parents' ]);
    
    //      Fix Notices
    if ( empty( $test_last_parent ))
        $test_last_parent = '';
    if ( empty( $element[ '#type' ]))
        $element[ '#type' ] = '';
    
    //      debug
    //dsm( $element[ '#type' ] .' / '. $test_last_parent );
    
    return (
        in_array( $element[ '#type' ], $element_types_whitelist ) &&
        !in_array( $test_last_parent, $element_last_parent_blacklist )
    );
}



/**
 * Implements theme_form_element_label().
 *
 * Specifically, it entirely duplicates the core function but adds a single
 * class to the attributes array. A little more consistency in how form elements
 * are themed in core would not be unwelcome...
 */
function bootship_form_element_label($variables) {
  $element = $variables['element'];
  // This is also used in the installer, pre-database setup.
  $t = get_t();

  // If title and required marker are both empty, output no label.
  if ((!isset($element['#title']) || $element['#title'] === '') && empty($element['#required'])) {
    return '';
  }

  // If the element is required, a required marker is appended to the label.
  $required = !empty($element['#required']) ? theme('form_required_marker', array('element' => $element)) : '';

  $title = filter_xss_admin($element['#title']);

  $attributes = array();
  // Style the label as class option to display inline with the element.
  if ($element['#title_display'] == 'after') {
    $attributes['class'] = 'option';
  }
  // Show label only to screen readers to avoid disruption in visual flows.
  elseif ($element['#title_display'] == 'invisible') {
    $attributes['class'] = 'element-invisible';
  }

  if (!empty($element['#id'])) {
    $attributes['for'] = $element['#id'];
  }

  // Add Bootstrap-related class to label:
  if (isset($attributes['class'])) {
    $attributes['class'] .= ' control-label';
  }
  else {
    $attributes['class'] = 'control-label';
  }

  // The leading whitespace helps visually separate fields from inline labels.
  return ' <label' . drupal_attributes($attributes) . '>' . $t('!title !required', array('!title' => $title, '!required' => $required)) . "</label>\n";
} // one_shot_art_paris_form_element_label()


/**
 *  Implement theme_textfield
 */
function bootship_textfield( $variables )
{
  $element = $variables['element'];
  $element['#size'] = '30';

  //is this element requred then lest add the required element into the input
   $required = !empty($element['#required']) ? ' required' : '';

  //dont need to set type in html5 its default so lets remove it because we can
  $element['#attributes']['type'] = 'text';

	//placeholder
  if (!empty($element['#title']) AND theme_get_setting('mothership_classes_form_placeholder_label') ) {
    $element['#attributes']['placeholder'] =  $element['#title'];
  }

  element_set_attributes($element, array('id', 'name', 'value', 'size', 'maxlength'));

  //remove the form-text class
  if(!theme_get_setting('mothership_classes_form_input')){
    _form_set_class($element, array('form-text'));
  }
  
  $extra = '';
  if ($element['#autocomplete_path'] && drupal_valid_path($element['#autocomplete_path'])) {
    drupal_add_library('system', 'drupal.autocomplete');
    $element['#attributes']['class'][] = 'form-autocomplete';

    $attributes = array();
    $attributes['type'] = 'hidden';
    $attributes['id'] = $element['#attributes']['id'] . '-autocomplete';
    $attributes['value'] = url($element['#autocomplete_path'], array('absolute' => TRUE));
    $attributes['disabled'] = 'disabled';
    $attributes['class'][] = 'autocomplete';
  
    //  hack paul 21:13 27/01/2013 - adding "span12" class
    //  @todo 21:13 27/01/2013 - configurable number of columns for the grid
    $attributes['class'][] = 'span12';

    $extra = '<input' . drupal_attributes($attributes) . $required .' />';
  }

  //  hack paul 21:13 27/01/2013 - adding "span12" class
  //  @todo 21:13 27/01/2013 - configurable number of columns for the grid
  //  update 21:57 27/01/2013 - except for "date" and "time" textfields
  //  update 22:29 27/01/2013 - reusable
  //dsm( $element );
  if ( _row_fluid_element_is_applicable( $element ))
    $element['#attributes']['class'][] = 'span12';
  
  $output = '<input' . drupal_attributes($element['#attributes']) . $required . ' />';

  return $output . $extra;
}



/**
 * Implements theme_textarea().
 */
function bootship_textarea($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id', 'name', 'cols', 'rows'));
  // Add non-Drupal class here:
  _form_set_class($element, array('input-xlarge'));

  // Add resizable behavior.
  if (!empty($element['#resizable'])) {
    drupal_add_library('system', 'drupal.textarea');
    // Don't add usual Drupal wrapper class here:
    $wrapper_attributes['class'][] = 'resizable';
  }
  else {
    $wrapper_attributes = array();
  }
  
  //  hack Paul 21:21 27/01/2013 - textarea grid 12 aussi
  $element['#attributes']['class'][] = 'span12';

  $output = '<div' . drupal_attributes($wrapper_attributes) . '>';
  $output .= '<textarea' . drupal_attributes($element['#attributes']) . '>' . check_plain($element['#value']) . '</textarea>';
  $output .= '</div>';
  return $output;
}


