import datetime
from pwn import *

def decrypt1(encrypted, value):
    #undo character alphabet rotation
    decrypted = ''
    for i,char in enumerate(encrypted):
        if i % 3 == 0:
            if ord(char) >= ord('a') and ord(char) <= ord('z'):
                decrypted += chr((((ord(char)-ord('a'))+13-value) % 26) + ord('a'))
            elif ord(char) >= ord('A') and ord(char) <= ord('Z'):
                decrypted += chr((((ord(char)-ord('A'))+13-value) % 26) + ord('A'))
            else:
                decrypted += char
        else:
            decrypted += char
    return decrypted

def decrypt2(encrypted, value):
    #undo the array rotation
    newval = len(encrypted) - value
    return encrypted[newval:] + encrypted[:newval]

def decrypt3(encrypted, value):
    #undo the numeral addition
    decrypted = ''
    for i,char in enumerate(encrypted):
        #make note that the source binary adds to the numerals.
        #This means that they can be characters not between '0' and '9'
        if ord(char) >= ord('0') and ord(char) < ord('A'):
            decrypted += chr(ord(char) - value)
        else:
            decrypted += char
    return decrypted

#connect
p = remote('localhost',4321)

#read prompt
original = p.read().decode().split(' ')

#the minute section is important in making decisions
#use the time given by the server, as your time might be slightly different than the server time
minute = int(original[0].split('T')[1].split(':')[1])
value = (minute % 6) + 2

#get the encrypted password
encrypted = original[3].split('\n')[0]

#setup function pointer array
fun_ptr = [decrypt1,decrypt2,decrypt3]

#go backwards through the encryption process seen in the binary.
intermediate1 = fun_ptr[(value + 2) % 3](encrypted,value)
intermediate2 = fun_ptr[(value + 1) % 3](intermediate1,value)
decrypted = fun_ptr[value % 3](intermediate2,value)

#send password and get flag
p.send(decrypted + '\n')
print(p.read())

