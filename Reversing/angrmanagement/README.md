## Description

`nc rev.tamuctf.com 4322`

## Documentation

Reverse the password, use angr or similar tool if you don't hate yourself.  I grabbed the same url scheme that was used last year.  I assume it'll be the same this year but its possible that'll need to change.  

### Setup

1. docker build . -t angrmanagement
2. docker run --rm -it -p 4322:4322 angrmanagement

## Solution

I've attached a solver using angr.  It's pretty straightforward.  I make a symbolic variable of 32 bytes, tell it to write to stdin, and then give it memory addresses to find and avoid.  I also constrain it to printable characters, but that is more for convenience.  If I don't do that it is entirely possible it'll find a valid series of bytes that isn't entirely printable.  
