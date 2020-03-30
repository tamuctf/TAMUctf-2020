#!/bin/bash

while : 
do
    su -c "exec socat TCP-LISTEN:3424,reuseaddr,fork EXEC:/ctf/exec.sh,stderr" - ctfuser;
done
