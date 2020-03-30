## Description

The owner of this website often reuses passwords.  Can you find out the password they are using on this test server?  

## Documentation

An SQL injection challenge in which the flag is the password.  It can be extracted by using wildcards when injecting.  I decided I might as well tell them the goal because this was supposed to be an easy challenge.  

### Setup

1. docker build . -t passwordextraction
2. docker run -p 80:80 passwordextraction

## Solution

You could in theory do the entire thing manually with sql wildcards like so "'or password like 'g%'".  I imagine everyone will write a short script to just brute force it because the script to do so is pretty straightforward.  I've included a solver in solution.py.  