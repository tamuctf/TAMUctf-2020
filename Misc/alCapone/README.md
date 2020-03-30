# Description
Eliot Ness is the lead on taking down Al Capone. He has gained access to Capone's personal computer but being the good detective he is, he got the disk image of the computer rather than look through the actual computer. Can you help Ness out and find any information to take down the mob boss?

(hint: Al Capone knew his computer was going to be taken soon, so he deleted all important data to ensure no one could see it. Little did he know that Ness was smarter than him.)

# Documentation
This is a very simple challenge that gives beginners experience working with forensic toolkits.

# Set Up
Direct Download link: https://drive.google.com/uc?export=download&id=1sdReBozky4P0A2Albs5sPISc9zFYtzmw

# Solution
I used FTK Imager to upload the img file and inspected the Recycle Bin. Extracting all the text files and using strings or grep for each file yileds the flag.

# Write Up
Use FTK Imager or Autopsy to find deleted files. In one of the deleted files, the flag is among the mess. For me, it was hidden in Dc50.txt.

To recreate this challenge, follow these simple steps:
1. Download WindowsXP (I used Windows XP Professional) disk image
2. Download Oracle Virtual Box
3. Set up WindowsXP in Oracle (there are youtube videos -- it is fairly simple)
4. Within the VB, I created a couple text documents and then filled them with random strings then duplicated the documents to make the XP look cluttered. Within one of those text documents, the flag is part of the random strings. 
5. Then I grabbed all of them and deleted them (also keeping a bunch of the text docs on the desktop - none have the flag).
6. Now the XP is challenge is ready. All you gotta do next is create a img of the vdi (virtual disk image).
7. To do so, open up terminal and navigate to the Oracle->VirtualBox and use VBoxManage to clone the vdi to an img.
8. Now you have the challenge that I created!
