import random
import hashlib

'''
Encrypt plaintext using SHA-256
'''
def encrypt(plaintext):
    # sha256
    return hashlib.sha256(plaintext.encode()).hexdigest()

'''
Checks that plaintext hashes to ciphertext
'''
def check(plaintext, ciphertext, redundancy_check=100000):
    good = True

    # needed to make sure cosmic rays haven't flipped any bits
    for x in range(redundancy_check):
        good = good and (encrypt(plaintext) == ciphertext)
        if not good:
            return good

    return good

'''
Main menu
'''
def print_menu():
    print('Welcome admin. Select an option:\n')
    print('\t1. Enter password')
    print('\t2. Reset password')
    print('\t3. Exit')

'''
Admin login
'''
def login():
    print('-------------------------')
    print('          Login          ')
    print('-------------------------')

    password = input('Password: ')

    with open('password_hash.txt', 'r') as pwfile:
        pw_hash = pwfile.readline().rstrip()
        if check(password, pw_hash):
            print('Welcome admin!')
        else:
            print('Incorrect password.') # :(

'''
Reset admin password using security questions
'''
def reset():
    print('--------------------------')
    print('      Password Reset      ')
    print('--------------------------')

    print('Please answer the following yes/no security questions to prove your identity. Type either "Yes" or "No" for each (without quotation marks).')
    questions = open('questions.txt', 'r').readlines()

    with open('security_hashes.txt', 'r') as securityfile:
        good = True
        for q in questions:
            answer = input(q)
            answer_hash = securityfile.readline().rstrip()
            good = good and check(answer, answer_hash)

        if good:
            new_pw = input('New password:\n')

            with open('flag.txt', 'r') as flagfile:
                print(flagfile.readline()) # :)
                exit()
            with open('password_hash.txt', 'w') as pwfile:
                pwfile.write(encrypt(new_pw))
        else:
            # incorrect
            print('You\'re not who you say you are.') # :(


# what more could an admin want?
options = [login, reset, exit]
def run_server():
    while True:
        print_menu()
        option = int(input())
        options[option-1]() # sneak

if __name__ == '__main__':
    # let's run the server!
    run_server()


