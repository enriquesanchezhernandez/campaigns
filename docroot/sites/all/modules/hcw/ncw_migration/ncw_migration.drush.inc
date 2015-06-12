<?php

/**
 * Implements COMMANDFILE_drush_command().
 */
function ncw_migration_drush_command() {
  return array('ncw-import-all' => array(
    'description' => 'Import all content from the corporate website',
  ));
}

function drush_ncw_migration_ncw_import_all() {
  /* BE AWARE OF THE MIGRATIONS ORDERING! */
  $migrations = array(
    'tax_country_status',
    'tax_country',
    'tax_fop_link_sections',
    'tax_newsletter_sections',
    'tax_publication_types',
    'tax_tags',

    'events',
    'infographic',
    'news',
    'note_to_editor',
    'press_contact',
    'press_release',
    'publications',
  );
  foreach($migrations as $migration) {
    ncw_migration_run_single($migration);
  }
}
