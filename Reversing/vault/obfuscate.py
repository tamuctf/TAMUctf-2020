flag = bytearray(b"gigem{p455w0rd_1n_m3m0ry1}")


for i in range(len(flag)):
	print("{} - {}".format(i,(i+1) % len(flag)))
	flag[i] ^= flag[(i+1) % len(flag)]
for i in range(len(flag)):
	flag[i] ^= 43
for i in range(len(flag)):
	flag[i] += 15
for i in range(0,len(flag),2):
	flag[i], flag[i+1] = flag[i+1], flag[i]

print(len(flag))
print(flag)