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
cp ~/Desktop/test.jpg ~/Desktop/test1.jpg
#sleep 1

./src/build/FaceMatcher models/shape_predictor_68_face_landmarks.dat $img
./src/build/faceswap $img img/donald_trump.jpg src/ron_output
#./src/build/faceswap $img img/vic_crop.png src/ron_output
#open src/ron_output/output.png
#echo "running brush filter"
#cd src
#./a10
echo "...done..."
done