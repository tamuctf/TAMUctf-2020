# 652AHS

```text
Adam the admin spent awhile writing a really nifty Python server to do admin things. He protected it with state of the art cryptography.

nc <host-ip> 7393
<insert-script-download-link>
```

## Setup

1. `docker build -t 652ahs .`
2. `docker run --rm -p 7393:7393 -d 652ahs`

## Brief Dev Description

A Python server running over socat which has password reset feature to be exploited. The flag is printed after one successfully logs in with a password that has been updated.

## Solution

See `solver.py`. It's a rather simple timing based attack, since correct answers take longer to get a response than incorrect answers.

