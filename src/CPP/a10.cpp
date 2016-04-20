#include <iostream>

#include "a10.h"

using namespace std;

// Write your implementations here, or extend the Makefile if you add source
// files
void someFunction() {
    cout << "ok, that's a function" << endl;
}

void brush(Image &out, const int y, const int x, const vector<float> color, const Image &texture) {
    if (x < texture.width()/2.0 || (out.width() - x) < texture.width()/2.0 || y < texture.height()/2.0 || (out.height() - y) < texture.height()/2.0 ) {
        return;
    }

    for (int i = 0; i < texture.width(); i++ ) {
        for (int j=0; j<texture.height(); j++) {            
            out(x-texture.width()/2 + i, y - texture.height()/2 + j, 0) = texture(i,j,0) * color[0] + out(x-texture.width()/2 + i, y - texture.height()/2 + j, 0) * (1-texture(i,j,0));
            out(x-texture.width()/2 + i, y - texture.height()/2 + j, 1) = texture(i,j,1) * color[1] + out(x-texture.width()/2 + i, y - texture.height()/2 + j, 1) * (1-texture(i,j,1));
            out(x-texture.width()/2 + i, y - texture.height()/2 + j, 2) = texture(i,j,2) * color[2] + out(x-texture.width()/2 + i, y - texture.height()/2 + j, 2) * (1-texture(i,j,2));
        }
    }
}

void brushCone(Image &out, Image &zBuffer, const int y, const int x, const vector<float> color, const int size) {
    for (int i=0;i<size;i++) {
        for (int j=0;j<size;j++) {
            int xCoord = x-size/2+i;
            int yCoord = y-size/2+j;


            if (xCoord >=0 && xCoord < out.width() && yCoord >=0 && yCoord < out.height()) {
                float zB = pow(x-xCoord,2) + pow(y-yCoord,2);
                if (zB < zBuffer(xCoord,yCoord)) {
                    zBuffer(xCoord,yCoord) = zB;
                    out(xCoord, yCoord, 0) = color[0];
                    out(xCoord, yCoord, 1) = color[1];
                    out(xCoord, yCoord, 2) = color[2];
                }    
            }
        }
    }
}


void singleScalePaint(const Image &im, Image &out, const Image &importance, const Image &texture, const int size, const int N, const float noise) {
    float factor = min( float(size) / texture.width(), float(size) / texture.height() );
    Image scaledTexture = scaleLin(texture, factor);
    int counter = 0;

    // calculate importance average
    float importanceAvg = 0.0;
    for (int r=0;r<importance.width();r++)
    for (int s=0;s<importance.height();s++) {
        importanceAvg += importance(r,s);
    }
    importanceAvg /= importance.width() * importance.height();
    int weightedN = int(N / importanceAvg);

    srand (static_cast <unsigned> (time(0)));
    for (int i=0; i<weightedN; i++) {
        int x = rand() % out.width();
        int y = rand() % out.height();

        float importanceFactor = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        if (importanceFactor > importance(x,y)) {
            continue;
        }
        counter += 1;

        vector<float> noiseMult;
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        noiseMult.push_back(1 - noise/2 + noise*r);
        r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        noiseMult.push_back(1 - noise/2 + noise*r);
        r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        noiseMult.push_back(1 - noise/2 + noise*r);

        vector<float> color;
        color.push_back(im(x,y,0) * noiseMult[0]);
        color.push_back(im(x,y,1) * noiseMult[1]);
        color.push_back(im(x,y,2) * noiseMult[2]);

        brush(out, y, x, color, scaledTexture);
    }
    cout << "N values: " << N << endl << "Number of strokes: " << counter << endl;
}

void singleScalePaintCone(const Image &im, Image &out, Image &zBuffer, const Image &importance, const int size, const int N, const float noise) {
    int counter = 0;

    // calculate importance average
    float importanceAvg = 0.0;
    for (int r=0;r<importance.width();r++)
    for (int s=0;s<importance.height();s++) {
        importanceAvg += importance(r,s);
    }
    importanceAvg /= importance.width() * importance.height();
    int weightedN = int(N / importanceAvg);

    srand (static_cast <unsigned> (time(0)));
    for (int i=0; i<weightedN; i++) {
        int x = rand() % out.width();
        int y = rand() % out.height();

        float importanceFactor = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        if (importanceFactor > importance(x,y)) {
            continue;
        }
        counter += 1;

        vector<float> noiseMult;
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        noiseMult.push_back(1 - noise/2 + noise*r);
        r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        noiseMult.push_back(1 - noise/2 + noise*r);
        r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        noiseMult.push_back(1 - noise/2 + noise*r);

        vector<float> color;
        color.push_back(im(x,y,0) * noiseMult[0]);
        color.push_back(im(x,y,1) * noiseMult[1]);
        color.push_back(im(x,y,2) * noiseMult[2]);

        brushCone(out, zBuffer, y, x, color, size);
    }
    cout << "N values: " << N << endl << "Number of strokes: " << counter << endl;
}

Image sharpnessMap(const Image &im, float sigma, float truncate, bool clamp){
    Image lumi = color2gray(im);
    Image lowPass = gaussianBlur_separable(lumi, sigma, truncate, clamp);
    Image highPass = lumi - lowPass;
    Image energy = highPass * highPass;
    Image sharpness = gaussianBlur_separable(energy, sigma * 4, truncate, clamp);

    // normalize sharpness
    float max_ = 0;
    for (int x=0; x<sharpness.width(); x++)
    for (int y=0; y<sharpness.height(); y++) {
        max_ = max(max_, sharpness(x,y));
    }

    return sharpness / max_;
}

Image painterly(const Image &im, const Image &texture, const int N, const int size, const float noise) {
    Image out(im.width(), im.height(), im.channels());
    Image firstPassImportance = Image(im.width(), im.height(), 1);
    firstPassImportance = firstPassImportance + 1;

    singleScalePaint(im, out, firstPassImportance, texture, size, N, noise);

    Image sM = sharpnessMap(im);
    singleScalePaint(im, out, sM, texture, size/4, N, noise);

    return out;
}

Image computeTensor(const Image &im, float sigmaG, float factorSigma) {
    // // --------- HANDOUT  PS07 ------------------------------
    // Compute xx/xy/yy Tensor of an image. (stored in that order)
    Image luminance = lumiChromi(im)[0];
    Image blurred = gaussianBlur_separable(luminance, sigmaG);
    Image gradX = gradientX(blurred);
    Image gradY = gradientY(blurred);

    Image output(im.width(), im.height(), im.channels());
    for (int x=0; x<output.width(); x++) {
        for (int y=0; y<output.height(); y++) {
            output(x,y,0) = pow(gradX(x,y),2);
            output(x,y,1) = gradX(x,y) * gradY(x,y);
            output(x,y,2) = pow(gradY(x,y),2);
        }
    }
    return gaussianBlur_separable(output, sigmaG * factorSigma);
}

Image computeAngles(const Image &im) {
    Image output(im.width(), im.height(), im.channels());

    float sigmaG = 3.0;
    float factorSigma = 5;
    Image tensor = computeTensor(im, sigmaG, factorSigma);

    for (int x=0; x<tensor.width(); x++)
    for (int y=0; y<tensor.height(); y++) {
        float xx = tensor(x,y,0);
        float xy = tensor(x,y,1);
        float yy = tensor(x,y,2);

        Matrix mat(2,2);
        mat << xx, xy,
               xy, yy;

        Eigen::EigenSolver<Matrix> es(mat);
        float eig1 = es.pseudoEigenvalueMatrix().col(0).x();
        float eig2 = es.pseudoEigenvalueMatrix().col(1).y();

        Vec2f eigenvector;
        if (eig1 < eig2) {
            eigenvector = es.pseudoEigenvectors().col(0);
        } else {
            eigenvector = es.pseudoEigenvectors().col(1);
        }
        output(x,y) = atan2(eigenvector.x(), eigenvector.y()) + M_PI/2.0;
    }

    return output;
}

void singleScaleOrientedPainting(const Image &im, Image &out, const Image &thetas, const Image &importance, const Image &texture, const int size, const int N, const float noise, const int nAngles) {
    float factor = min( float(size) / texture.width(), float(size) / texture.height() );
    Image scaledTexture = scaleLin(texture, factor);
    int counter = 0;

    // calculate importance average
    float importanceAvg = 0.0;
    for (int r=0;r<importance.width();r++)
    for (int s=0;s<importance.height();s++) {
        importanceAvg += importance(r,s);
    }
    importanceAvg /= importance.width() * importance.height();
    int weightedN = int(N / importanceAvg);

    srand (static_cast <unsigned> (time(0)));
    for (int i=0; i<weightedN; i++) {
        int x = rand() % out.width();
        int y = rand() % out.height();

        float importanceFactor = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        if (importanceFactor > importance(x,y)) {
            continue;
        }
        counter += 1;

        vector<float> noiseMult;
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        noiseMult.push_back(1 - noise/2 + noise*r);
        r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        noiseMult.push_back(1 - noise/2 + noise*r);
        r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        noiseMult.push_back(1 - noise/2 + noise*r);

        vector<float> color;
        color.push_back(im(x,y,0) * noiseMult[0]);
        color.push_back(im(x,y,1) * noiseMult[1]);
        color.push_back(im(x,y,2) * noiseMult[2]);

        Image rotatedTexture = rotate(scaledTexture, thetas(x,y));
        brush(out, y, x, color, rotatedTexture);
    }
    cout << "N values: " << N << endl << "Number of strokes: " << counter << endl;
}

Image orientedPaint(const Image &im, const Image &texture, const int N, const int size, const float noise) {
    Image out(im.width(), im.height(), im.channels());
    Image firstPassImportance = Image(im.width(), im.height(), 1);
    firstPassImportance = firstPassImportance + 1;
    Image thetas = computeAngles(im);

    singleScaleOrientedPainting(im, out, thetas, firstPassImportance, texture, size, N, noise);

    Image sM = sharpnessMap(im);
    singleScaleOrientedPainting(im, out, thetas, sM, texture, size/4, N, noise);

    return out;
}

Image conePainting(const Image &im, const int N, float size, const float noise) {
    Image out(im.width(), im.height(), im.channels());
    Image zBuffer(im.width(), im.height(), 1);
    zBuffer = zBuffer + 1e8;
    Image firstPassImportance = Image(im.width(), im.height(), 1);
    firstPassImportance = firstPassImportance + 1;

    singleScalePaintCone(im, out, zBuffer, firstPassImportance, size, N, noise);

    Image sM = sharpnessMap(im);
    for (int i=0; i<10; i++) {
        singleScalePaintCone(im, out, zBuffer, sM, size, N, noise);
        size = size * 3/4.0;    
    }
    
    return out;
}


