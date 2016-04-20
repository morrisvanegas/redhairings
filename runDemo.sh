#!/bin/bash

echo "...computing images..."
./src/build/FaceMatcher models/shape_predictor_68_face_landmarks.dat $1
./src/build/faceswap $1
echo "...done..."