file = open("morse_flag.txt", "r")
flag = file.readline()

morse_flag = ""
for letter in flag:
    if letter == "-":
        morse_flag += "woof "
    if letter == ".":
        morse_flag += "bark "
    if letter == " ":
        morse_flag += "ruff "

print(morse_flag)