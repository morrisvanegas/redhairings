#!/bin/bash

if [ $# -eq 0 ]
  then
    echo "No arguments supplied, defaulting to test case"
    img="img/test.jpg"
  else
  	img=$1
fi

echo "...computing images..."
while true
do
cp img/test.jpg img/test_copy.jpg

./src/build/FaceMatcher models/shape_predictor_68_face_landmarks.dat $img
./src/build/faceswap $img img/vic_crop.png src/ron_output

#echo "running brush filter"
#cd src
#./a10
echo "...done..."