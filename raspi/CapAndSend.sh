#!/bin/bash

sudo echo "Hi, im in"
cd /home/pi/Desktop/RHUploaderTest/raspi
COUNTER=00

while true
do
echo "Capturing image"
sudo python python-picamera.py
#sudo python webcam.py

echo The counter is $COUNTER
let COUNTER=COUNTER+1

echo "Sending through dropbox API"
sudo ./dropbox_uploader.sh upload test.jpg "2.744 Red Hairing/master/img/test/${COUNTER}.jpg"

done