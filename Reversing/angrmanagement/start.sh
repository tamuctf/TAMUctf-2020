#!/bin/bash

while : 
do
    su -c "exec socat TCP-LISTEN:4322,reuseaddr,fork EXEC:./angrmanagement,stderr" - angrmanagement;
done
