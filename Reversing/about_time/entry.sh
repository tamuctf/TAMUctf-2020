#!/bin/sh

while : 
do
    socat TCP-LISTEN:4321,reuseaddr,fork EXEC:/rvrs/about_time,stderr
done
