ans = ''
secret = 0x849182746352

with open('flag.txt', 'r') as flag_file:
    flag = flag_file.read().rstrip('\r\n').encode('utf-8')
    t = len(flag)
    flag = flag.hex()
    for i in range(t//6):
        print(hex(secret^int(flag[12*i:12*i+12], 16))[2:], end='')
    print()

