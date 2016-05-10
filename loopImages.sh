#!/bin/bash

while true
do

osascript -e 'quit app "Preview"'
img="img/child2_cropped.png"
open -a Preview $img ; /usr/bin/osascript -e 'tell application "Preview"' -e "activate" -e 'tell application "System Events"' -e 'keystroke "f" using {control down, command down}' -e "end tell" -e "end tell"

open -a Preview "src/GOODONES/covert3.png" ; /usr/bin/osascript -e 'tell application "Preview"' -e "activate" -e 'tell application "System Events"' -e 'keystroke "f" using {control down, command down}' -e "end tell" -e "end tell"
sleep 3
open -a Preview "src/GOODONES/covert5.png" ; /usr/bin/osascript -e 'tell application "Preview"' -e "activate" -e 'tell application "System Events"' -e 'keystroke "f" using {control down, command down}' -e "end tell" -e "end tell"
sleep 3
open -a Preview "src/GOODONES/covert6.png" ; /usr/bin/osascript -e 'tell application "Preview"' -e "activate" -e 'tell application "System Events"' -e 'keystroke "f" using {control down, command down}' -e "end tell" -e "end tell"
sleep 3
open -a Preview "src/GOODONES/covert4.png" ; /usr/bin/osascript -e 'tell application "Preview"' -e "activate" -e 'tell application "System Events"' -e 'keystroke "f" using {control down, command down}' -e "end tell" -e "end tell"
sleep 3
open -a Preview "src/GOODONES/covert11.png" ; /usr/bin/osascript -e 'tell application "Preview"' -e "activate" -e 'tell application "System Events"' -e 'keystroke "f" using {control down, command down}' -e "end tell" -e "end tell"
sleep 3
open -a Preview "src/GOODONES/covert8.png" ; /usr/bin/osascript -e 'tell application "Preview"' -e "activate" -e 'tell application "System Events"' -e 'keystroke "f" using {control down, command down}' -e "end tell" -e "end tell"
sleep 3
open -a Preview "src/GOODONES/covert7.png" ; /usr/bin/osascript -e 'tell application "Preview"' -e "activate" -e 'tell application "System Events"' -e 'keystroke "f" using {control down, command down}' -e "end tell" -e "end tell"
sleep 3
open -a Preview "src/GOODONES/covert10.png" ; /usr/bin/osascript -e 'tell application "Preview"' -e "activate" -e 'tell application "System Events"' -e 'keystroke "f" using {control down, command down}' -e "end tell" -e "end tell"
sleep 3
open -a Preview "src/GOODONES/covert9.png" ; /usr/bin/osascript -e 'tell application "Preview"' -e "activate" -e 'tell application "System Events"' -e 'keystroke "f" using {control down, command down}' -e "end tell" -e "end tell"
sleep 3
open -a Preview "src/GOODONES/covert12.png" ; /usr/bin/osascript -e 'tell application "Preview"' -e "activate" -e 'tell application "System Events"' -e 'keystroke "f" using {control down, command down}' -e "end tell" -e "end tell"
sleep 3
open -a Preview "src/GOODONES/covert13.png" ; /usr/bin/osascript -e 'tell application "Preview"' -e "activate" -e 'tell application "System Events"' -e 'keystroke "f" using {control down, command down}' -e "end tell" -e "end tell"
sleep 3

open -a Preview "src/GOODONES/out118.png" ; /usr/bin/osascript -e 'tell application "Preview"' -e "activate" -e 'tell application "System Events"' -e 'keystroke "f" using {control down, command down}' -e "end tell" -e "end tell"
sleep 3
open -a Preview "src/GOODONES/out196.png" ; /usr/bin/osascript -e 'tell application "Preview"' -e "activate" -e 'tell application "System Events"' -e 'keystroke "f" using {control down, command down}' -e "end tell" -e "end tell"
sleep 3
open -a Preview "src/GOODONES/out78.png" ; /usr/bin/osascript -e 'tell application "Preview"' -e "activate" -e 'tell application "System Events"' -e 'keystroke "f" using {control down, command down}' -e "end tell" -e "end tell"
sleep 3
open -a Preview "src/GOODONES/out191.png" ; /usr/bin/osascript -e 'tell application "Preview"' -e "activate" -e 'tell application "System Events"' -e 'keystroke "f" using {control down, command down}' -e "end tell" -e "end tell"
sleep 3



# creat an array with all the files inside ~/my directory
#declare -a array=( src/GOODONES/* )

# get array size
#array_size=${#array[@]}
#echo "Displaying ${#array[@]} images"

#sleep 2

# display images one at a time
#for i in "${array[@]}"; 
#do
#    open -a Preview $i ; /usr/bin/osascript -e 'tell application "Preview"' -e "activate" -e 'tell application "System Events"' -e 'keystroke "f" using {control down, command down}' -e "end tell" -e "end tell"
#    sleep 20

#done

#osascript -e 'quit app "Preview"'
#img="img/child2_cropped.png"
#open -a Preview $img ; /usr/bin/osascript -e 'tell application "Preview"' -e "activate" -e 'tell application "System Events"' -e 'keystroke "f" using {control down, command down}' -e "end tell" -e "end tell"


done