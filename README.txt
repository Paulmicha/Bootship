/**
 *  Bootship Readme
 *  
 *  This is a base theme extending the Mothership theme,
 *  "Fixing everything that is wrong (tm)" \m/
 *  So send http://morten.dk/ some beers.
 *  
 *  Tested with :
 *      Twitter Bootstrap v2.3.0
 *      FontAwesome v3.0.2
 *
 *  @extends    /sites/all/themes/mothership/mothership
 *  @requires   http://drupal.org/project/mothership
 *  @requires   http://twitter.github.com/bootstrap/
 *  @requires   http://fortawesome.github.com/Font-Awesome/
 *  @requires   http://drupal.org/project/conditional_styles
 *  @requires   http://drupal.org/project/elements
 *  @requires   http://drupal.org/project/html5_tools
 *  @author     Paulmicha
 */


----------------------------------------------------
    Quickstart:
----------------------------------------------------

0.  Download Mothership theme @ http://drupal.org/project/mothership
    Drush command copy/paste :
        drush dl mothership
    Then apply the following patches to it :
        http://drupal.org/node/1904236
    Required modules to install :
        http://drupal.org/project/conditional_styles
        http://drupal.org/project/elements
        http://drupal.org/project/html5_tools
    Drush command copy/paste :
        drush dl conditional_styles elements html5_tools && drush en conditional_styles elements html5_tools -y
    Recommended modules to install as well :
        http://drupal.org/project/styleguide
    Drush command copy/paste :
        drush dl styleguide && drush en styleguide -y

1.  Download Twitter Bootstrap (branch 2.x) in folder /sites/all/libraries/bootstrap/
    Note : use the version from Github to get the source LESS files
    The only folders required are :
    /sites/all/libraries/bootstrap/js
    /sites/all/libraries/bootstrap/less

2.  Install bootship in one of the usual places for the themes:
    /sites/all/themes
    /sites/default/themes
    /sites/[SITENAME]/themes

3.  Copy the "NEWTHEME" folder inside the usual places for themes:
    /sites/all/themes/NEWTHEME
    /sites/[SITENAME]/themes/NEWTHEME
    Rename the NEWTHEME folder & NEWTHEME.info (as well as all occurences of NEWTHEME inside it)

4.  Download FontAwesome fonts inside the "font" folder of your new theme
    For example, if you used /sites/all/themes/NEWTHEME, the only required files are :
    /sites/all/themes/NEWTHEME/font/fontawesome-webfont.ttf
    /sites/all/themes/NEWTHEME/font/fontawesome-webfont.woff
    /sites/all/themes/NEWTHEME/font/fontawesome-webfont.eot

5.  Enable & Set as default this (now renamed) NEWTHEME

6.  Adapt the theme settings to your liking in admin URL admin/appearance/settings/NEWTHEME
    Look in mothership/documentation for documentation of all the settings.


