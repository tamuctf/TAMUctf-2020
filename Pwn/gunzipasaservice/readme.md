# Gunzip as a service

```text
nc 172.17.0.2 4709
```
<link to the binaries>
## Setup

1. `docker build -t gunzipasaservice .`
2. `docker run --rm -d --read-only gunzipasaservice`

## Brief Dev Description

It is a buffer overflow problem with the NX bit set so you can't use shellcode.  The program uses execl and has a /bin/sh string so its pretty easy to get a shell from overwriting the return address.  the buffer overflow vulnerability is not in the program input but in the buffer that the gzipped input decompresses to.  

## Solution

1. Determine offset required to overwrite the return address.  I just paused it in gdb and used info frame to get the return address.  
2. Get address of execl and a /bin/sh string.  Both are used in the binary so its pretty easy to grab them with objdump and strings.  
3. Create payload.  It should be 1048 bytes to the return address and then the execl address / placeholder / /bin/sh address
4. Compress payload using gzip
5. Send payload to binary
6. Enjoy your new shell