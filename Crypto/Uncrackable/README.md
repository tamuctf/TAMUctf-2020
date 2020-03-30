# Uncrackable

## Description

e3f8e5110e29e6fde31a0861f0a4dd13530db5ffdd17113be6c2dd1c022f

## Documentation

Simple XOR cipher (key length is 6).

### Setup

Just put the description above (this is all that is needed for the challenge).

## Solution

Just guess that the first 6 will be gigem{ and you'll get a XOR key of length 6 that works.

An example of this is in `solve.rs`:
```
rustc solve.rs
for i in $(echo "e3f8e5110e29e6fde31a0861f0a4dd13530db5ffdd17113be6c2dd1c022f" | fold -w2 | paste -sd' ' -); do printf "\x$i"; done | ./solve
```
