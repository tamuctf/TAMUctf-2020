#!/bin/sh

while : 
do
    su -c "exec socat TCP-LISTEN:7393,reuseaddr,fork EXEC:\"python3 /crypto/server.py\",stderr" - cryptouser;
done
