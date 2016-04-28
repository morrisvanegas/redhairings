#!/bin/sh

sudo echo "Hi, im in"
cd /home/pi/Desktop/RHUploaderTest/raspi
while true
do
echo "python"
sudo python webcam.py
sleep 2

echo "dropbox"
sudo ./dropbox_uploader.sh upload test.jpg "2.744 Red Hairing/master/img/test.jpg"
#sleep 2
done