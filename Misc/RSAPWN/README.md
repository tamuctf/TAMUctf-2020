# RSAPWN

## Description

```text
We must train the next generation of hackers.
nc <ip here> 8573
```

## Documentation


### Setup

1. `docker build -t rsapwn .`
2. `docker run -p 8573:8573 -d rsapwn`

## Solution

Just have to write a script to factor in O(\sqrt{n}).
