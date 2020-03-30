#!/bin/bash

CARGO_INCREMENTAL=0 cargo rustc --release -- --emit llvm-bc
cp target/release/deps/*.bc just-bc.bin
