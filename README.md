# Mystery Morph

## Installation

We assume OpenCV is already installed (want to include in cmake?)

for mac os x:
`brew install opencv3 --c++11 --with-contrib --with-ffmpeg --with-tbb --with-qt5`

to build:

1. `cd src`
2. `mkdir build`
3. `./install.sh`

## Demo

To run the demo simply:

`./runDemo.sh`

If you'd like to run the demo on a new target image:

`./runDemo.sh target/image/path`

## Editing a10

If you edit a10_main.cpp (the script that turns the image into a painting), make sure to run the makefile again from inside src.

Items that belong to the a10 script are inside _build, CPP, and Eigen folders. 


## Running a dlib example

to build:

1. `cd examples`
2. `mkdir build`
3. `cd build`
4. `cmake ..`
5. `cmake --build . --config Release`

From dlib-master/examples/build:

`./webcam_face_pose_ex`


