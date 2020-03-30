#!/bin/sh

fallocate -l 4m file.img;
mkfs.ext4 file.img;
mkdir file;
mount file.img file;
convert -gravity center -extent 110x130% label:"gigem{wh3r3_w3r3_601n6_w3_d0n7_n33d_h34d3r5}" -strip flag.png;
cp document.docx file/document.docx;
cp dummy.pdf file/dummy.pdf;
cp reveille.jpg file/reveille.jpg;
cp snake.png file/snake.png;
cp yQw6zFn.jpg file/yQw6zFn.jpg;
cp flag.png file/flag.png;
umount file;
rm -rf file;
dd bs=1360 skip=1 if=file.img of=recovered_disk.img;
rm file.img
rm flag.png
