17 April 2015 upgrade instructions
==================================

Aside from the common update procedure described in the technical documentation, apply the following manual changes:

__BEFORE__ the update:

1. Edit [conf/config.json](conf/config.json) "variables" section and append the following variables (see [conf/config.template.json](config.template.json)):
  * varnish_version: 3 - Leave 3, currently supported version is Varnish 3
  * varnish_control_terminal: 127.0.0.1:6082 - Fill-in the __address:port__ of your Varnish server
  * varnish_control_key: "secret key" - Only if authentication is configured in Varnish
  * varnish_socket_timeout: 150 - A decent default for Varnish hosted on another machine

__AFTER__ the update:

1. Edit `sites/default/settings.php` and append the following lines at the end of the file:
```
# Varnish cache configuration
$conf['cache_backends'][] = 'sites/all/modules/contrib/varnish/varnish.cache.inc';
$conf['cache_class_cache_page'] = 'VarnishCache';
```
A default tested Varnish VCL configuration file has been provided in (conf/varnish-devel.vcl)[conf/varnish-devel.vcl]

2. Configure the binding passwords for LDAP connection.

a. password for read-only account by visiting /admin/config/people/ldap/servers/edit/osha and set the field *Password for non-anonymous search* (under section BINDING METHOD)
b. password for writable account by visiting /admin/config/people/ldap/servers/edit/osha-write and set the field *Password for non-anonymous search* (under section BINDING METHOD)


3. Set-up a CRON job to automatically synchronize the users and sections, using `crontab -e` as user 'root'.
```
*/15 * * * * /expert/osha/.composer/vendor/bin/drush osha-ldap-sync 2>&1
```

4. Setup Drupal CRON (currently disabled)
```
0 * * * * wget -O - -q -t 1 http://osha-corp-staging.mainstrat.com/cron.php?cron_key=CRON_KEY
```
where CRON_KEY is taken from `/admin/config/system/cron` screen. Cron above will run on every hour.

5. LDAP checklist

  a. Create the following group in LDAP cn=ADMIN,ou=MainSite,ou=Sites,dc=osha,dc=europa,dc=eu
  a. Create the following group in LDAP cn=READ,ou=MainSite,ou=Sites,dc=osha,dc=europa,dc=eu

6. Drupal role review

  a. A new role has been created 'Events Editor' with no specifications - someone needs to review the permissions
