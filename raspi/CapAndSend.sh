#!/bin/bash

sudo echo "Hi, im in"
while true
do
echo "python"
sudo python webcam.py
sleep 2

echo "dropbox"
sudo ./dropbox_uploader.sh upload test.jpg test.jpg
#sleep 2
done