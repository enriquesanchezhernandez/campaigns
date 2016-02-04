@echo off

rem Go to docroot/
cd docroot/

call drush sql-drop -y

rem Sync from edw staging
call drush downsync_sql @osha.staging.sync @osha.local -y -v

rem Devify - development settings
call drush devify --yes
call drush devify_solr

rem Build the site
call drush osha_build -y
