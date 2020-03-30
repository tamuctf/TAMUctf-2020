#!/bin/bash

cargo clean
RUSTFLAGS='-C link-arg=-s' cargo +nightly build --release
