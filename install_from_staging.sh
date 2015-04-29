#!/bin/bash

# Go to docroot/
cd docroot/

drush sql-drop -y
ecode=$?
if [ ${ecode} != 0 ]; then
  echo "Error cleaning database"
  exit ${ecode};
fi

pre_update=  post_update=
while getopts b:a: opt; do
  case $opt in
  b)
      pre_update=$OPTARG
      ;;
  a)
      post_update=$OPTARG
      ;;
  esac
done

# Sync from edw staging
drush downsync_sql @osha.staging @osha.local -y
ecode=$?
if [ ${ecode} != 0 ]; then
  echo "downsync_sql has returned an error"
  exit ${ecode};
fi


if [ ! -z "$pre_update" ]; then
  echo "Run pre update"
  ../$pre_update
fi

# Devify - development settings
drush devify --yes
ecode=$?
if [ ${ecode} != 0 ]; then
  echo "Devify has returned an error"
  exit ${ecode};
fi

drush devify_solr
ecode=$?
if [ ${ecode} != 0 ]; then
  echo "Devify Solr has returned an error"
  exit ${ecode};
fi

# Build the site
drush osha_build -y
if [ ${ecode} != 0 ]; then
  echo "osha_build has returned an error"
  exit ${ecode};
fi

if [ ! -z "$post_update" ]; then
  echo "Run post update"
  ../$post_update
  drush cc all
fi

# Post-install release 3
# drush ne-import --file=../content/internal-doc-webform.drupal
# drush php-script ../scripts/s9/post-update.php
