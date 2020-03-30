# Getting Confused

```text
We want to test how truly redass you are. In order to do so, we've set up a little test.

Connect to <REPLACE IP>:4352 and answer correctly. We'll even give you the binary the test has for fairness.
```

## Setup

1. `docker build -t getting-confused .`
2. `docker run --rm -p 4352:4352 -d getting-confused`

## Brief Dev Description

Just a little binary with a few prompts, socat'd to the world.

Unfortunately, there's stack reuse and fgets doesn't write anything if the file descriptor is closed.

## Solution

```text
$ socat -,raw,echo=0 tcp:172.17.0.2:4352
howdy
gig 'em
^D
```

Where ^D is EOF in CTTY.
