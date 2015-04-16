#!/bin/sh

sudo varnishd -F -a :80 \
  -f /Users/cristiroma/Work/osha/project/conf/varnish-devel.vcl \
  -s malloc,256M \
  -T localhost:6082 \
  -p sess_workspace=262144 \
  -p log_hashstring=off \
  -p ping_interval=1 \
  -p shm_workspace=32768 \
  -p thread_pools=4 \
  -p thread_pool_min=100 \
  -p esi_syntax=1 \
  -p thread_pool_add_delay=2 \
  -p thread_pool_max=4000 \
  -p session_linger=50 \
