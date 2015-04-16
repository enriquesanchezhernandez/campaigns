17 April 2015 upgrade instructions
==================================

Aside from the common update procedure described by the technical documentation, apply the following changes manually __BEFORE__ the actual update:

1. Edit [conf/config.json](conf/config.json) "variables" section and append the following variables (see [conf/config.template.json](config.template.json)):
  * varnish_version: 3 - Leave 3, currently supported version is Varnish 3
  * varnish_control_terminal: 127.0.0.1:6082 - Fill-in the __address:port__ of your Varnish server
  * varnish_control_key: "secret key" - Only if authentication is configured in Varnish
  * varnish_socket_timeout: 150 - A decent default for Varnish hosted on another machine

2. Edit `sites/default/settings.php` and append the following lines at the end of the file:

```
# Varnish cache configuration
$conf['cache_backends'][] = 'sites/all/modules/contrib/varnish/varnish.cache.inc';
$conf['cache_class_cache_page'] = 'VarnishCache';
```

3. A default tested Varnish VCL configuration file has been provided in conf/varnish-devel.vcl