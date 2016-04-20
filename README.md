# redhairings

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