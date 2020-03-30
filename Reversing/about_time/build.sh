#!/bin/bash

docker build -t about-time-builder -f Dockerfile.build .
docker run --rm -ti --mount "type=bind,source=$(pwd),target=/tmp/build" about-time-builder sh -c "cd /tmp/build; gcc -s -o about_time about_time.c"

docker build --rm -t about-time .
