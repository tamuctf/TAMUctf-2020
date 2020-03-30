# Corrupted Disk 
```text
We've recovered this disk image but it seems to be damaged.  Can you recover any useful information from it?  
```
<recovered_disk_image.img>

## Setup

1. `sudo ./build.sh`

It requires root because mounting.  I couldn't find a way to mount an image in docker without mounting it in the host first.  

## Brief Dev Description

basic file carving challenge

## Solution

I used `binwalk --dd='.*' recovered_disk.img` and then just checked photos one by one until one looked relevant.  