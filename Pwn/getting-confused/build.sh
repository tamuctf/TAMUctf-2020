#!/bin/bash

docker build -t gcc:alpine -f Dockerfile.build .
docker run --user $(id -u):$(id -g) --rm -ti -v $(pwd):/opt/build gcc:alpine -o getting-confused getting-confused.c
