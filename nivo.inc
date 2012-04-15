<?php
/**
 * Format the Nivo output for posts which have attached images 
 * 
 * When the thumbnail size is "full" then this will only work when there is an attached image
 * It won't find the featured image. This is a limitation of bw_thumbnail() **?**
 * 
*/
function bw_format_nivo( $post, $atts ) {
  setup_postdata( $post );
  if ( bw_validate_torf( $atts['caption'] ) )
    $atts['title'] = get_the_title( $post->ID );
  $atts['thumbnail'] = bw_array_get( $atts, "thumbnail", "full" );
  $thumbnail = bw_thumbnail( $post->ID, $atts );
  $permalink = get_permalink( $post->ID );
  if ( bw_validate_torf( $atts['link'] ) ) {
    alink( null, $permalink , $thumbnail, null);  
  } else {
    e( $thumbnail );
  }    
}

/** 
 * Return the 'correct' URL for the attached image
 *
 * @param integer $post_id - the ID of the attachment post
 * @return string $image - the URL for the attached image
 *
 * We cannot rely on $post->guid since the uploaded file may have been edited in the media dialog
 * and given a new name. We need to obtain the file name from the metadata and then fully qualify it for the browser
 *
*/ 
function bw_get_attached_file_name( $post_id ) {
  $images = get_post_custom_values( "_wp_attached_file", $post_id );
  //bw_trace2( $images ); 
  if ( $images ) {
    $upload_dir = wp_upload_dir();
    $image = $upload_dir['baseurl'] . '/' . $images[0];
  } else {
    $image = null;
  }  
  return( $image );
}

/**
 * Format the Nivo output for attached images
 *
 * Extract from Nivo's documentation
 * - To add a caption to an image you simply need to add a title attribute to the image. 
 * - To add an HTML Caption simply set the title attribute to the ID of a element that contains your caption (prefixed with a hash). 
 * - Note that the HTML element that contains your caption must have the CSS class nivo-html-caption applied and must be outside of the slider div.
 *
 * In this code we haven't YET implemented the HTML caption logic
 * 
*/ 
function bw_format_nivo_attachment( $post, $atts ) {
  if ( bw_validate_torf( $atts['caption'] ) ) {
    $title = get_the_title( $post->ID );
  } else {
    $title = null;
  }    
  $permalink = get_permalink( $post->ID );
  $image = bw_get_attached_file_name( $post->ID );
  if ( $image ) {
    $thumbnail = retimage( null, $image , $title );
    if ( bw_validate_torf( $atts['link'] ) ) {
      alink( null, $permalink , $thumbnail, null );  
    } else {
      e( $thumbnail );
    }    
  }  
}

/**
 * Enqueue the debug script if needed otherwise enqueue the minified (packed) one
*/
function bw_nivo_enqueue_script( ) {
  if ( defined('SCRIPT_DEBUG' ) && SCRIPT_DEBUG == true) {
    $script = 'jquery.nivo.slider.js';
  } else {
    $script = 'jquery.nivo.slider.pack.js'; 
  } 
  $oik_nc_script = 'jquery.oik-nc-click.js';  
  wp_enqueue_script( 'nivo-slider-js', plugin_dir_url( __FILE__) . $script, array( 'jquery') );
  wp_enqueue_script( 'oik-nc-click.js', plugin_dir_url( __FILE__) . $oik_nc_script, array( 'nivo-slider-js') ); 
}

/**
 * Set the nivoSlider to start for objects with an id of slider-n
 * Note: The .css file allows for up to 5 sliders per page.
*/
function bw_slider_id() {
  global $bw_slider_count; 
  if ( empty( $bw_slider_count ) ) {
    $bw_slider_count = 0;
  }  
  $bw_slider_count++;
  return( $bw_slider_count );
}

  
/**
 * Implement a Nivo slider for attachments or other post types
 *
 * The nivo slider consists of 
 * jQuery, the Nivo slider jQuery and something to attach nivoSlider to the div containing the images
 * Nivo is a bit pernickety about the html you use in order to create links with captions.
 *
 *
*/
function bw_nivo_slider( $atts=null ) {
  $atts[ 'post_type'] = bw_array_get( $atts, "post_type", "attachment" );
  $theme = bw_array_get( $atts, "theme", "default" );
  $class = bw_array_get( $atts, "class", null );
  $atts['link'] = bw_array_get( $atts, "link", "y" );
  $atts['caption'] = bw_array_get ($atts, "caption", "y" );
  $ribbon = bw_validate_torf( bw_array_get(  $atts, "ribbon", "y" ));
  oik_require( "shortcodes/oik-attachments.php" );
  $posts = bw_get_posts( $atts );
  if ( $posts ) {
    wp_enqueue_style( "nivo${theme}", plugin_dir_url( __FILE__). "themes/${theme}/${theme}.css" ); 
    wp_enqueue_style( 'nivoCSS', plugin_dir_url( __FILE__). 'nivo-slider.css' ); 
    bw_nivo_enqueue_script();
    $slider_id = bw_slider_id();
    e( '<script type="text/javascript">jQuery(window).load(function() {  jQuery(\'#slider-'. $slider_id. '\').nivoSlider(); });</script>' );
    if ( bw_validate_torf( $atts['link'] ) ) {
      e( '<script type="text/javascript">jQuery(window).load(function() {  jQuery(\'#slider-'. $slider_id. '\').oikNCClick(); });</script>' );
    }  
    sdiv( $class );
    sdiv( "slider-wrapper theme-${theme}" );
    if ( $ribbon )
      sediv( "ribbon" );
    sdiv( "nivoSlider", "slider-$slider_id" );
    $funcname = bw_funcname( "bw_format_nivo", $atts['post_type'] );
    foreach ( $posts as $post ) {
      $funcname( $post, $atts );
    }
    ediv();
    ediv();  
    ediv( $class ); 
  }  
  return bw_ret();
}

function nivo__help( $shortcode="nivo" ) {
  return( "Display the nivo slideshow for attachments or other post types." );
}

if ( !function_exists( '_sc_thumbnail_full' ) ) {  
function _sc_thumbnail_full() {   
  return( array( 'thumbnail'       => bw_skv( "full", "small|medium|large|nnn|wxh", "image size" )   
               ));
}        
}


/**
 *
*/ 
function nivo__syntax( $shortcode='nivo' ) {
  
  $nivo_syntax = array( "post_type" => bw_skv( "attachment", "<i>post_type</i>", "Post type to display" )
                 , "theme" => bw_skv( "default", "orman|pascal|oik", "Theme for the slideshow" )
                 , "class" => bw_skv( "", "<i>classes</i>", "CSS classes" )
                 , "link" => bw_skv( "y", "n", "Link the images to the target post/page" )
                 , "caption" => bw_skv( "y", "n", "Display the image title as the caption" )
                 , "ribbon" => bw_skv( "y", "n", "Display the ribbon, if the theme supports it" )
                 );
  $syntax = array_merge( $nivo_syntax, _sc_thumbnail_full() );
  $syntax = array_merge( $syntax, _sc_posts() );
  $syntax = array_merge( $syntax, $nivo_syntax ); // Re-apply the post_type values for this shortcode
  return( $syntax );
}

/**
 * Produce the code snippet for the nivo shortcode
 * Since the implementing function for the shortcode is not the same as the shortcode we need to let _sc__snippet know
*/ 
function nivo__snippet( $shortcode='nivo' ) {
  _sc__snippet( $shortcode, null, "bw_nivo_slider" );
}
