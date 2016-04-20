#!/bin/bash

echo "...computing images..."
./src/build/FaceMatcher models/shape_predictor_68_face_landmarks.dat img/$1
./src/build/faceswap img/$1
echo "...done..."