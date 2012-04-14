=== oik-nivo-slider ===
Contributors: bobbingwide
Donate link: http://www.oik-plugins.com/oik/oik-donate/
Tags: shortcode, Nivo, slider, [nivo], oik, jQuery, slideshow
Requires at least: 3.0.4
Tested up to: 3.3.1
Stable tag: 1.0

[nivo] shortcode for the jQuery "Nivo slider" for posts, pages, attachments and custom post types

== Description ==
The [nivo] shortcode implements the jQuery Nivo slider, which is considered by some to be "The Most Awesome jQuery Image Slider". 
See http://nivo.dev7studios.com for more info.

The [nivo] shortcode can be used to display a variety of slideshows with/without links.   
It can be used to direct the user to any post/page/custom content type.
The [nivo] shortcode uses the oik plugin's shortcode API for lazy smart shortcodes.

You can see an example of the code in action here:
 

http://rowlandscastlewebdesign.com/wp-pompey-mar2012/home/slideshows-2/slideshow-requirements/nivo/

see also the 'Nivo for posts' and 'Nivo for pages' pages on this WordPress Multi Site site. 


== Installation ==
1. Upload the contents of the oik-nivo-slider plugin to the `/wp-content/plugins/oik-nivo-slider' directory
1. Activate the oik-nivo-slider plugin through the 'Plugins' menu in WordPress
1. Whenever you want to produce some 'oik-nivo-slider'ed text use the [oik-nivo-slider] shortcode.

Note: oik-nivo-slider is dependent upon the oik plugin. You can activate it but it will not work unless oik is also activated.
Download oik from 
[oik download](http://wordpress.org/extend/plugins/oik/)

== Frequently Asked Questions ==
= Which version of the jQuery Nivo slider code is needed? = 
The plugin includes the FREE jQuery Nivo slider v2.7.1 from http://nivo.dev7studios.com/features/
excluding the demo files.
There is a minor change to the nivo-slider.css file to allow every image to be a link to another page.

= Which version of jQuery does it use? =
It uses the jQuery library provided by WordPress 

= What is the syntax for the [nivo] shortcode? = 

[nivo
post_type="attachment|post_type - Post type to display"
theme="default|orman|pascal - Theme for the slideshow"
class="|classes - CSS classes"]
and other parameters as for [bw_posts] 

Documentation to be completed! 

= What's OIK and why does it need it? = 
The oik Nivo slider is developed using the OIK (Often Included Key Information) API (Application Programming Interface).
Specifically, the code is dependent upon bw_get_posts() to obtain the list of attachments, posts, pages or custom post types
which populate the slider and bw_thumbnail() to select the image to display when it's not an attached image. 

= I typed [nivo] and got [nivo] back =
You need to activate both the oik-nivo-slider plugin and the oik base plugin.
The [nivo] shortcode only becomes functional when [oik] is loaded.

= I can't see some of the images in my slideshow =
The default image size is thumbnail=full.
At present the bw_thumbnail() function will only return an image for a particular post id
when there is an attached image; it won't find the featured image. As a workaround either specify the thumbnail parameter as small,medium,large or your preferred size (e.g. 150x100)
OR ensure that the image you want to display is attached to the post
OR exclude the post from the list ( exclude=id1,id2 )


= Do I need to make my images the same size? =
YES. There is no auto cropping?

= Can I control the slideshow transitions? =
This is planned for a future version.

= Can I provide my own themeing? =
This is planned for a future version.

= Can I put the [nivo] shortcode in my sidebar? =
YES. You can use the [nivo] shortcode in sidebars, headers and footers
as well as in posts, pages, and custom post types.
Remember you may need to set the post_parent parameter to control which posts are loaded.


= What's the difference between this plugin and Nivo's WordPress plugin =
I have not tried Nivo's plugin. But you can read about it and watch a video here
http://nivo.dev7studios.com/features/#wordpress


= Can you tell me more? =
YES. See http://www.oik-plugins.com/oik-plugins/oik-nivo-slider/


== Screenshots ==
1. 

== Upgrade Notice ==
= 1.0 =
* first version works with oik version 1.11

== Changelog ==
= 1.0 =
* initial version. Works with oik version 1.11 


== Further reading ==
If you want to read more about the oik plugins then please visit the
[oik plugin](http://www.oik-plugins.com/oik) 
**"the oik plugin - for often included key-information"**

