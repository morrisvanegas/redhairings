#ifndef A10_H_PHUDVTKB
#define A10_H_PHUDVTKB

#include "Image.h"
#include "basicImageManipulation.h"
#include "filtering.h"
#include "matrix.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <ctime>
#include <vector>
#include <cmath>

// Write your declarations here, or extend the Makefile if you add source
// files

void brush(Image &out, const int y,const int x,const vector<float> color, const Image &texture);
void brushCone(Image &out, Image &zBuffer, const int y, const int x, const vector<float> color, const int size);
void singleScalePaint(const Image &im, Image &out, const Image &importance, const Image &texture, const int size=10, const int N=1000, const float noise=0.3);
void singleScalePaintCone(const Image &im, Image &out, Image &zBuffer, const Image &importance, const int size=10, const int N=1000, const float noise=0.3);
Image sharpnessMap(const Image &im, float sigma=1.0, float truncate=3.0, bool clamp=true);
Image painterly(const Image &im, const Image &texture, const int N=10000, const int size=50, const float noise=0.3);
Image computeAngles(const Image &im);
void singleScaleOrientedPainting(const Image &im, Image &out, const Image &thetas, const Image &importance, const Image &texture, const int size=10, const int N=100000, const float noise=0.3, const int nAngles=36);
Image orientedPaint(const Image &im, const Image &texture, const int N=7000, const int size=50, const float noise=0.2);
Image conePainting(const Image &im, const int N=7000, float size=160, const float noise=0.3);
#endif /* end of include guard: A10_H_PHUDVTKB */

