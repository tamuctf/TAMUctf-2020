# Description
Lorelei, a nuclear engineer, is practicing how to create folders to organize her notes. She works closely with POTUS to secure our nuclear missiles. In order for her to send the nuclear codes to the correct authorities, she needs to zip all the files and make the data hard to find. Your mission, should you choose to accept it, is to intercept and find the codes (the flag).

# Documentation
This is a simple forensics challenge aimed for beginners. The focus is developing a script that can easily search through files to find what you may need.

# Set Up
Run the zipFile.py and it will recursively create more zipped folders. At the end, there will be a bunch of random text files and something else.

# Write Up
Use command line to unzip the folder until you get to the end and then look at the extensions of all the files and you'll notice there is a png in there. Using an online stego tool, you will find the flag ecoded in the picture.