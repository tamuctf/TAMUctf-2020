from pwn import *
import time

ans = []
r = remote('172.17.0.2', 7393)
while len(ans) < 20:
    print(ans)
    # try yes
    print('Trying yes...')
    r.recvuntil("Exit\n")
    r.sendline('2')
    r.recvuntil('.\n')

    for i in range(len(ans)):
        r.recvline()
        r.sendline(ans[i])

    r.recvline()
    syes = time.time()
    r.sendline("Yes")
    resp = r.recvline()
    tyes = time.time() - syes

    for i in range(len(ans)+2, 21):
        if i != len(ans)+2:
            r.recvline()
        r.sendline("No")

    if resp.startswith(bytes("New", 'ascii')):
        ans.append("Yes")
        break

    r.close()
    time.sleep(.05)

    # try no
    print('Trying no...')
    r = remote('172.17.0.2', 7393)
    r.recvuntil("Exit\n")
    r.sendline('2')
    r.recvuntil('.\n')

    for i in range(len(ans)):
        r.recvline()
        r.sendline(ans[i])

    r.recvline()
    sno = time.time()
    r.sendline("No")
    resp = r.recvline()
    tno = time.time() - sno

    for i in range(len(ans)+2, 21):
        if i != len(ans)+2:
            r.recvline()
        r.sendline("No")

    if resp.startswith(bytes("New", 'ascii')):
        ans.append("No")
        break

    r.close()
    time.sleep(.05)

    r = remote('172.17.0.2', 7393)
    if tyes > tno:
        ans.append("Yes")
    else:
        ans.append("No")


r.interactive()

