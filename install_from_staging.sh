#!/bin/bash

# Go to docroot/
cd docroot/

drush site-install -y

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
drush downsync_sql @osha.staging @osha.local -y -v

if [ ! -z "$pre_update" ]; then
echo "Run pre update"
../$pre_update
fi

# Devify - development settings
drush devify --yes
drush devify_solr

# Build the site
drush osha_build -y

drush cc all

if [ ! -z "$post_update" ]; then
echo "Run post update"
../$post_update
fi

# Post-install release 3
drush ne-import --file=../content/internal-doc-webform.drupal
drush php-script ../scripts/s9/post-update.php

drush cc all
