#!/bin/bash

while : 
do
    su -c "exec socat TCP-LISTEN:4765,reuseaddr,fork EXEC:/pwn/troll,stderr" - pwnuser;
done
