#!/bin/bash

docker build -t rust-nightly . -f Dockerfile.builder
docker run --rm --user "$(id -u)":"$(id -g)" -v "$PWD":/usr/src/rusty-at-reversing -w /usr/src/rusty-at-reversing rust-nightly ./build.sh
