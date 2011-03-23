$Id: README.txt,v 1.0.0.0 2009/09/28 19:45:25 dzieyzone Exp $

----------------------------------------------------
#####									Overview								 #####
----------------------------------------------------

This module allows Drupal to replace textarea fields with the
FCKeditor.
This HTML text editor brings many of the powerful functions of known
desktop editors like Word to the web. It's relatively lightweight and
doesn't require any kind of installation on the client computer.

----------------------------------------------------
#####						Required components						 #####
----------------------------------------------------

To use belatedpng  in Drupal, you will need to download the latest DD_belatedPNG script
http://www.dillerdesign.com/experiment/DD_belatedPNG/

----------------------------------------------------
#####			  More information and licence			 #####
----------------------------------------------------

DD_belatedPNG
Copyright (c) 2008 Drew Diller

DD_belatedPNG is free software under the MIT License.
		http://www.dillerdesign.com/experiment/DD_belatedPNG/#license

For further information visit:
    http://www.dillerdesign.com/experiment/DD_belatedPNG

----------------------------------------------------
#####					  		Requirements							 #####
----------------------------------------------------
  - Drupal 6.x :)

----------------------------------------------------
#####					  		Configuration							 #####
----------------------------------------------------

   1. Unzip the files in the sites/all/modules directory.
   2. Download the latest DD_belatedPNG javascript from 
	 		http://www.dillerdesign.com/experiment/DD_belatedPNG/#download.
	 		I recommend to use the compressed version.
   3. Copy the javascript to sites/all/modules/belatedpng and rename it to belatedpng.js.
   4. Enable the module as usual from Drupal's admin pages.
   5. Under "Administer > Site configuration > belatedPNG", enter elements you want to apply inside the textarea.
	 		Separate each element with comma. You can use element type, classes and ids. e.x. (#belatedpng, .belatedpng, .li)

----------------------------------------------------
#####			Installation troubleshooting				 #####
----------------------------------------------------

The script file is required with this module. Make sure that belatedpng.js exist in the modules folder.

----------------------------------------------------
#####			  Upgrading instructions						 #####
----------------------------------------------------

This module is using DD_belatedPNG_0.0.8a.js version when it was written. Assuming that
the script was updated, all you have to do is to rename it with belatedpng.js
   
----------------------------------------------------
#####			 					  Credits									 #####
---------------------------------------------------- 

 - belatedpng for Drupal Core functionality was originally written by Mark Jayson Nicolas (http://www.dzieyzone.com) under
 	 Spinweb Productions, Inc. (http://www.spinweb.ph)

 - DD_belatedPNG is currently maintained by Drew Diller.
     http://www.dillerdesign.com/experiment/DD_belatedPNG
     Copyright (c) 2008 Drew Diller