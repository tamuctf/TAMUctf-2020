from pwn import *
import time

r = remote('127.0.0.1', 8573)
r.sendline('')
r.recvline()
r.recvline()
r.recvline()
r.recvline()
r.recvline()
r.recvline()
p = int(r.recvline())
for i in range(2,10000001):
    if p%i==0:
        r.sendline(str(i) + ' ' + str(p//i))
        r.recvline()
        print(r.recvline().decode('utf-8'), end='')
        exit()
