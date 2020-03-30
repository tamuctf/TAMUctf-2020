# Sigma

## Description

10320831141252164475480592397410881183128414021520157116851780189419421991209921942315241625302578269728072902300131153236334834643575368637343782389340044129

## Documentation

A simple adhoc crypto challenge. The "encryption" method is simply to take prefix sums of the ascii values
of the flag string and concatenate their prefix sums together.

### Setup
1. Put desired flag in flag.txt.
2. Run `python encrypt.py > encrypted_flag.txt`, which outputs the encrypted flag to the file.
3. This encrypted flag is all that is needed for the challenge.

## Solution

One could pretty easily solve this by hand after noticing that the first three digits are the ascii value of 'g', the first
character of the flag. From there, subtracting by hand the next substring which has a decimal value greater than the previous
is sufficient. The script `solution.py` automates this.
