#!/bin/bash
docker build -t gcc:debian -f Dockerfile.build .
docker run --net=host --user $(id -u):$(id -g) --rm -ti -v $(pwd):/opt/build gcc:debian vault.c -o vault 