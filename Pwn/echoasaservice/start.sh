#!/bin/bash

while : 
do
    su -c "exec socat TCP-LISTEN:4251,reuseaddr,fork EXEC:/pwn/echoasaservice,stderr" - pwnuser;
done
