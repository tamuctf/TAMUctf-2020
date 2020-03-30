# Description

NOTE: This probably shouldn't be called russian nesting doll, but I wanted to check with everyone else first.
Also, I'm putting off coming up with a more creative name.

Our monitoring systems noticed some funny-looking DNS traffic on one of our computers.
We have the network logs from around the time of the incident.
Want to take a look?

# Documetation

A pcap-based challenge (ugh, I know) in the spirit of the russian nesting doll.
I sent an encrypted tarball containing the flag via DNS tunneling.
There also some other hoops you have to jump through along the way.

## Setup

1. Deliver netlogs.pcap to the attacker.

# Solution

I think this one is pretty dfficult without being annoying like most pcaps challenges are.
I left out any red herring traffic, so almost every packet in the pcap is useful.
This makes it more of a "how well do you know wireshark/tshark/how to google things" rather than a search for a needle in a haystack.

First, extract the dns query names from the pcap somehow. I like to use tshark:

```
tshark -r <input_file> -T fields -e dns.qry.name > output
```

If you do it my way, there are a few duplicate lines; remove them:

```
uniq output > outputnodups
```

There's also one packet that says something like `dns._qry._test_qry` that you need to remove.
Now you have to strip the strings so they don't have the extra hostname junk on them.
I used awk:

```
awk -F"-" "{ print $2 }' outputnodups > outfile
```

Then, base64 decode the file to discover that it's a file encrypted by GPG.
Good thing there's still some traffic in the pcap.
The malicious actor decided to back up both GPG keys to the local unencrypted FTP server.
Download the keys from wireshark (they're in FTP-DATA packets) and unencrypt your file.
You can get the password by guessing (same PASS as the FTP server), or just use gpg2john.
File command shows it's a tarball (there might be another base64 decode in here somewhere).
Extracting reveals a bunch of files, and they all seem base64 encoded.
The one with the flag in it is `........encoded` (I generated all the rest with /dev/urandom).
Decode once again, and you should get an image of a shark.
Binwalk the shark and see there are two images in there.
For some reason, `binwalk -e` doesn't like to grab just the image on the inside, but `binwalk --dd="*" <file>` did the trick for me.
This picture is the flag drawn in MS Paint.
