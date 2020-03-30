'''
Just outputs prefix sums of ascii.
'''

with open('flag.txt', 'r') as flag_file:
    flag = flag_file.read().rstrip('\r\n')
    flag = [ord(c) for c in flag]
    pref = 0
    for i in flag:
        pref += i
        print(pref, end='')
