import random
import string
import zipfile
import os
import io
import sys

sys.setrecursionlimit(1100)

def createString():
    return ''.join([random.choice(string.ascii_letters + string.digits) for i in range(10)])
    
def createZip(num):
    if num == 0:
        zip_bytes = io.BytesIO()
        zip = zipfile.ZipFile(zip_bytes, "w")
        randomI = random.randint(0, 550)
        for i in range(550):
            if i == randomI:
                zip.write("random150.png")
            else:
                zip.writestr("random%s.txt" % i, createString())
        zip.close()
        return zip_bytes.getvalue()
    zip_bytes = io.BytesIO()
    zip = zipfile.ZipFile(zip_bytes, "w")
    zip.writestr("keepGoin.zip", createZip(num-1))
    zip.close()
    return zip_bytes.getvalue()

   
open("zipFolder.zip", "wb").write(createZip(2))


    