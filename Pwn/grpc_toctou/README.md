# Challenge Description
We have setup a secure echo service for your needs! To use the service, just download the provided python application and start echoing! It'll ask for a username and password, so please provide those to ensure secure communcations! (Note: this should be arbitrary and not any real username or password)

Hint: flag.txt can't be the username, that'd be too easy!

pip install grpcio grpcio-tools

# DISCLAIMER

This challenge was removed from TAMUctf mid-competition.

# Setup
Provide client/client.py and both client/protobuf_\*.py files to the user as well as the server/grpc_server.cc source file and server/server.o binary object file.
Run the following in the server directory:

        sudo docker build -t grpc_pwn .

        sudo docker run --rm -p 3010:3010 grpc_pwn 

For the client side, you should only have to install grpcio/grpcio-tools for python. The protocol buffer is already compiled with the two \*_pb2.py files, so you should not have to install protobuf.

# Solution
C++ disassembly is horrying to look at (atleast in Ghidra), sorry.

I have provided a solution script to solve the challenge. The issue exists within the ReceiveEcho function of the grpc server. There is a Time of Check to Time of Use vulnerability that allows the user to modify the contents of a variable after we do a check to make sure it will fit into the buffer it is being copied into. This allows the user to trigger a buffer overflow and overwrite into the next variable on the stack. You can overwrite that variable to read the flag from flag.txt.

When it reads the flag from flag.txt, it doesn't simply return that to the client application. Instead, it xor encrypts their message, so they then have to undo the easy xor with known plaintext that they provided.

I included an artificial usleep in there to make it slightly more obvious what needs to be done, as well as make it a little easier to script. The intended solution makes use of two threads: one to trigger the ReceiveEcho, and the other to overwrite the variable during the sleep with an overflow.
