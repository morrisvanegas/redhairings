#!/bin/bash

if [ $# -eq 0 ]
  then
    echo "No arguments supplied, defaulting to test case"
    #img="img/test.jpg"
  else
  	img=$1
fi

#Display an image first, just for fun
#osascript -e 'quit app "Preview"'
#open -a Preview "img/child2_cropped.png" ; /usr/bin/osascript -e 'tell application "Preview"' -e "activate" -e 'tell application "System Events"' -e 'keystroke "f" using {control down, command down}' -e "end tell" -e "end tell"

echo "...computing images..."

# Get the current (old) output
old_output="$(ls -t src/ron_output/*.png | head -1)"

while true
do
#cp img/test.jpg img/test_copy.jpg

# creat an array with all the files inside ~/my directory
declare -a array=( img/test/* )

# get latest image in directory of images from Raspberry pi
new_img="$(ls -t img/test/*.jpg | head -1)"
echo ${new_img}

# get array size
array_size=${#array[@]}
echo ${#array[@]}


# do FaceMatches with new img
./src/build/FaceMatcher models/shape_predictor_68_face_landmarks.dat ${new_img}

# Do faceswap_RR with new img_name, array_size
./src/build/faceswap_RR ${new_img} img/child1_cropped.png src/ron_output ${array_size}
#${#array[@]}
#echo ${output_number}

# get latest image in directory of images from outputs created
new_output="$(ls -t src/ron_output/*.png | head -1)"
echo ${new_output}
echo ${old_output}

# Display image on Frame if you have a new image
if [ ${new_output} != ${old_output} ]
  then
    echo "......new image! open it!......."
    old_output=$new_output
    #osascript -e 'quit app "Preview"'
    open -a Preview ${new_output} ; /usr/bin/osascript -e 'tell application "Preview"' -e "activate" -e 'tell application "System Events"' -e 'keystroke "f" using {control down, command down}' -e "end tell" -e "end tell"
  #else
  #  echo "same image, don't close Preview"
fi

echo "...done..."
done