## Description

There's a troll who thinks his challenge won't be solved until the heat death of the universe.

## Documentation

Basic stack overflow rand seed challenge.

### Setup

1. docker build . -t troll
2. docker run --rm -it -p 4765:4765 troll

## Solution

Overflow the name string to overwrite the seed, then predict correctly. Just
write your own code that prints the first 100 numbers from whatever seed you give.
This is implemented in `solver.py` and `zeroseed.c`.

Could also maybe overwrite RIP to flag printing code but that's extra.
