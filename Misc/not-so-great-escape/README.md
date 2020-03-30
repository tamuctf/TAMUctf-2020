# Not So Great Escape

```text
We've set up a chroot for you to develop your musl code in. It's bare, so install whatever you need.

Feel free to log in with: socat -,raw,echo=0 tcp:172.17.0.2:4353
The password is "2ff6b0b9733a294cb0e0aeb7269dea5ae05d2a2de569e8464b5967c6c207548e".
```

## Setup

1. `docker build -t not-so-great-escape .`
2. `docker run --rm -ti --read-only --tmpfs /tmp:exec not-so-great-escape`

You MUST run this with all the flags listed!

## Brief Dev Description

Easy chroot escape. Have fun. :)

## Solution

You can copy/paste the contents of solution.bin into the terminal after connecting.
