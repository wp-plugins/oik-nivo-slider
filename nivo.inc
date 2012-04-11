<?php
/**
 * Format the Nivo output for posts which have attached images 
 * 
 * When the thumbnail size is "full" then this will only work when there is an attached image
 * It won't find the featured image. This is a limitation of bw_thumbnail() **?**
 */
function bw_format_nivo( $post, $atts ) {
  setup_postdata( $post );
  $atts['title'] = get_the_title( $post->ID );
  $atts['thumbnail'] = bw_array_get( $atts, "thumbnail", "full" );
  $thumbnail = bw_thumbnail( $post->ID, $atts );
  $permalink = get_permalink( $post->ID );
  alink( null, $permalink , $thumbnail, null );  
}

/**
 * Format the Nivo output for attached images
 *
 * Extract from Nivo's documentation
 * - To add a caption to an image you simply need to add a title attribute to the image. 
 * - To add an HTML Caption simply set the title attribute to the ID of a element that contains your caption (prefixed with a hash). 
 * - Note that the HTML element that contains your caption must have the CSS class nivo-html-caption applied and must be outside of the slider div.
 *
*/ 
function bw_format_nivo_attachment( $post, $atts ) {
  $title = get_the_title( $post->ID );
  $permalink = get_permalink( $post->ID );
  $thumbnail = retimage( null, $post->guid, $title );
  //e( $thumbnail );
  //bw_link_thumbnail( $thumbnail, $post->ID, $atts );
  alink( null, $permalink , $thumbnail, null );  
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
  oik_require( "shortcodes/oik-attachments.php" );
  $posts = bw_get_posts( $atts );
  if ( $posts ) {
    wp_enqueue_style( 'nivodefault', plugin_dir_url( __FILE__). "themes/${theme}/${theme}.css" ); 
    wp_enqueue_style( 'nivoCSS', plugin_dir_url( __FILE__). 'nivo-slider.css' ); 
    wp_enqueue_script( 'nivo-slider-js', plugin_dir_url( __FILE__) . 'jquery.nivo.slider.js', array( 'jquery') );
    e( '<script type="text/javascript">jQuery(window).load(function() {  jQuery(\'#slider\').nivoSlider(); });</script>' );
    sdiv( "slider-wrapper theme-${theme} ${class}" );
    sediv( "ribbon" );
    sdiv( "nivoSlider", "slider" );
    $funcname = bw_funcname( "bw_format_nivo", $atts['post_type'] );
    foreach ( $posts as $post ) {
      $funcname( $post, $atts );
    }
    ediv();
    ediv();   
  }  
  return bw_ret();
}

function nivo__help( $shortcode="nivo" ) {
  return( "Display the nivo slideshow for attachments or other post types" );
}  


function nivo__syntax( $shortcode='nivo' ) {
  $syntax = array( "post_type" => bw_skv( "attachment", "<i>post_type</i>", "Post type to display" )
                 , "theme" => bw_skv( "default", "orman|pascal", "Theme for the slideshow" )
                 , "class" => bw_skv( "", "<i>classes</i>", "CSS classes" )
                 );
  return( $syntax );
}

/**
 * Produce the code snippet for the nivo shortcode
 * Since the implementing function for the shortcode is not the same as the shortcode we need to let _sc__snippet know
*/ 
function nivo__snippet( $shortcode='nivo' ) {
  _sc__snippet( $shortcode, null, "bw_nivo_slider" );
}
