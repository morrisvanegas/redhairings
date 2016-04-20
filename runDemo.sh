#!/bin/bash

if [ $# -eq 0 ]
  then
    echo "No arguments supplied, defaulting to test case"
    img="img/testoutanna.jpg"
  else
  	img=$1
fi

echo "...computing images..."
./src/build/FaceMatcher models/shape_predictor_68_face_landmarks.dat $img
./src/build/faceswap $img img/vic_crop.png src/ron_output
echo "running brush filter"
cd src
./a10
echo "...done..."