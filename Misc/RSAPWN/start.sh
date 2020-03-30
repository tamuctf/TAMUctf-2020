#!/bin/sh

while : 
do
    su -c "exec socat -d tcp-listen:8573,reuseaddr,fork exec:\"python3 /misc/server.py\",stderr" - ctfuser;
done
