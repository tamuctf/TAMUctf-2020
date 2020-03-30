file = open("secret.txt", "r")
flag = file.readline()

morse_flag = ""
for word in flag.split(" "):
    if word == "woof":
        morse_flag += "-"
    if word == "bark":
        morse_flag += "."
    if word == "ruff":
        morse_flag += " "

print(morse_flag)