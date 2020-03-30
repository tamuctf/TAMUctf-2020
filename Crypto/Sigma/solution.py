s = input()

s = s[3:]
flag = 'g'
pref = ord('g')

cur = ''
for c in s:
    if len(cur) == 0 or int(cur) < pref:
        cur += c
    else:
        flag += chr(int(cur)-pref)
        pref = int(cur)
        cur = c

if len(cur) > 0 and int(cur) > pref:
    flag += chr(int(cur)-pref)

print(flag)
