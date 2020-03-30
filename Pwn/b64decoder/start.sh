#!/bin/bash

while : 
do
    su -c "exec socat TCP-LISTEN:2783,reuseaddr,fork EXEC:/pwn/b64decoder,stderr" - pwnuser;
done
