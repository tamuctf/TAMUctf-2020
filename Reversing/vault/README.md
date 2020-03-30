# Vault

<link to the binary>

## Setup

1. `./build.sh`

## Brief Dev Description

The string stored inside the binary is obfuscated so that you can't find it with strings or similar tools.  The flag is deobfuscated before being compared to the input, so if you check the memory of the program while its running you can leak the flag.  Alternatively you could reverse the deobfuscate function.  It isn't very difficult.  

## Solution

1. ltrace ./vault
2. see the flag in the strcmp call
