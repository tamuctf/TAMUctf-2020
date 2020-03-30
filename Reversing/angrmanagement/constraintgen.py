import re
from random import shuffle, randint, choice, getrandbits
from string import printable, whitespace
printable = [x for x in printable if x not in ['\'', '\"', chr(0x0b), chr(10), "\\", "\n"] + [x for x in whitespace]]
eqs = "({} == \'{}\')"
neqs = "({} != \'{}\')"
eqs_index = "(string[{}] == \'{}\')"
ands = "({} && {})"
ors = "({} || {})"
gts = "({} >= {})"
lts = "({} <= {})"

pw = "(#P#;G~mT[$D5^E_$h.AC7{(Z.+c>AQj"

check_length = 3

def neconstraint(index):
	char = choice(printable)
	while char == pw[index]:
		char = choice(printable)
	return neqs.format("string[{}]".format(index), char)

def leconstraint(index):
    num = randint(ord(pw[index]), 0x7e)
    return lts.format("string[{}]".format(index), num)

def geconstrainst(index):
	num = randint(0x21, ord(pw[index]))
	return gts.format("string[{}]".format(index), num)

def cons1(index):
	r1 = randint(1, 100)
	r2 = randint(1, 100)
	r3 = randint(1, 100)
	r4 = randint(1, 100)
	r5 = randint(1, 100)
	lhs = "(string[{}] * {} % {})".format(index, r1, r2)
	rhs = ord(pw[index]) * r1 % r2
	return "({} == {})".format(lhs, rhs)


funcs = [neconstraint, leconstraint, geconstrainst, cons1]
constraints = []
output = []

for i in range(32):
	for j in range(check_length):
		constraints.append(choice(funcs)(i))
shuffle(constraints)

for i in range(0, 32*check_length, check_length):
	output.append(" && ".join(constraints[i:i+check_length]))

comparison = ""
for i in range(32):
	print("bool check_{}(char* string) {{ return {}; }}".format(i, output[i]))
	comparison += "check_{}(input) && ".format(i)

print(comparison)

