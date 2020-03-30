# EternalGame

## Description

```text
No one has ever won my game except me!
<game.py link>
nc <ip here> 8812
```

## Documentation

`game.py` runs over socat, and competitors are provided with the source. It's a simple game in which players multiply a number
by any number between 2 and 10 (but each can only be used up to five times). The goal is to get to some huge number which is
impossible with the restrictions given. There must be another way.

### Setup

1. `docker build -t eternalgame .`
2. `docker run -p 8812:8812 -d eternalgame`

## Solution

The idea is well-described [here](https://blog.skullsecurity.org/2012/everything-you-need-to-know-about-hash-length-extension-attacks).

It boils down to the fact that we are using SHA-512 in a way it was not designed to be used (HMAC would be the appropriate
thing to use here). The solution is to extend a hash given to you by the game by adding the padding and then a bunch of 0x39
('9' characters) to beat the high score.
