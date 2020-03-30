#!/bin/sh

while : 
do
    su -c "exec socat -d tcp-listen:8812,reuseaddr,fork exec:\"python /crypto/game.py\",stderr" - cryptouser;
done
