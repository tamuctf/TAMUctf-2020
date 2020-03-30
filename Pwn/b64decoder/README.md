## Description


We put together a demo for our high performance computing server.  Why don't you check it out?  

[libc.so.6](libc.so.6)
[b64decoder](b64decoder)


## Documentation

Fairly straightforward %n formatting challenge.  

### Setup

1. docker build . -t b64decoder
2. docker run --rm -it -p 2783:2783 b64decoder

## Solution

Use %n to overwrite a64l with system in got.plt and then pass "a64l" whatever argument you want.  The address of a64l and system shift around so I provide the version of libc in the container.  solver.py will do the exploit and give you shell.  