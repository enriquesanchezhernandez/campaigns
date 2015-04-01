#!/bin/sh

varnishd -d -a :8081 \
  -f ./conf/varnish-devel.vcl \
  -s malloc,1024M \
  -T localhost:6082 \
#  -p thread_pool_add_delay=2 \
#  -p thread_pools=8 \
#  -p thread_pool_min=500 \
#  -p thread_pool_max=4000 \
#  -p session_linger=50 \
#  -p sess_workspace=262144

