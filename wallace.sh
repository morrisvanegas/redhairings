#!/bin/bash

if [ -t 0 ]; then stty -echo -icanon -icrnl time 0 min 0; fi

osascript -e 'quit app "Preview"'

count=0
keypress=''

while [ "x$keypress" = "x" ]; do

	# Do what runDemo.sh does

	# creat an array with all the files inside ~/my directory
	declare -a array=( img/test/* )

	# get latest image in directory of images from Raspberry pi
	new_img="$(ls -t img/test/*.jpg | head -1)"
	echo ${new_img}

	# get array size
	array_size=${#array[@]}
	#echo ${#array[@]}
	#echo "...................."


	# do FaceMatches with new img
	./src/build/FaceMatcher models/shape_predictor_68_face_landmarks.dat ${new_img}

	# Do faceswap_RR with new img_name, array_size
	./src/build/faceswap_RR ${new_img} img/vic_crop.png src/wallace_output ${array_size}
	#${#array[@]}
	#echo ${output_number}

	# get latest image in directory of images from outputs created
	new_output="$(ls -t src/wallace_output/*.png | head -1)"
	echo ${new_output}
	echo ${old_output}

	# Display image on Frame if you have a new image
	if [ ${new_output} != ${old_output} ]
	  then
	    echo "......new image! save it!......."
	    old_output=$new_output
	#    #osascript -e 'quit app "Preview"'
	#    open -a Preview ${new_output} ; /usr/bin/osascript -e 'tell application "Preview"' -e "activate" -e 'tell application "System Events"' -e 'keystroke "f" using {control down, command down}' -e "end tell" -e "end tell"
	  #else
	  #  echo "same image, don't close Preview"
	fi

  	let count+=1
  	#echo -ne $count'\r'
  	keypress="`cat -v`"
done

if [ -t 0 ]; then stty sane; fi



echo "You pressed '$keypress' after $count loop iterations"

# creat an array with all the files inside ~/wallace_output
declare -a array=( src/wallace_output/*.png )

# get latest image in directory of images from Raspberry pi
wallace_img="$(ls -t src/wallace_output/*.png | head -1)"
echo ${wallace_img}

# get array size
array_size=${#array[@]}

if [ ${array_size} -eq 1 ]
	then
	wallace_img="src/wallace_output/wallace_output.png"
fi

# Open david's face
open -a Preview ${wallace_img} ; /usr/bin/osascript -e 'tell application "Preview"' -e "activate" -e 'tell application "System Events"' -e 'keystroke "f" using {control down, command down}' -e "end tell" -e "end tell"

#exit 0
















