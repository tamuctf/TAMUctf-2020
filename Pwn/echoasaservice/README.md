## Description

Echo as a service (EaaS) is going to be the newest hot startup!  We've tapped a big market: Developers who really like SaaS.    

## Documentation

Basic string formatting pwn challenge.  

### Setup

1. docker build . -t eaas
2. docker run --rm -it -p 4251:4251 eaas

## Solution

Look through the disassembled main function to figure out where its putting the data it reads and then grab that memory with sufficient %x.  I've attached a solver.   
