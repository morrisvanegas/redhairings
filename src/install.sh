#!/bin/bash

# install brush annanizer
make
make install
mkdir morris_output
# install face swapper
g++ faceSwap.cpp -I/usr/local/opt/opencv3/include/ -L/usr/local/opt/opencv3/lib -lopencv_calib3d -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_highgui -lopencv_imgproc -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_superres  -lopencv_video -lopencv_videostab -lopencv_imgcodecs -o build/faceswap
cd build
cmake ..
make