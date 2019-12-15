//
//  image.h
//  montelight
//
//  Created by Wei Li on 2019-12-14.
//  Copyright © 2019 Victor Li. All rights reserved.
//

#ifndef image_h
#define image_h
#include "vector.h"

#include <vector>

struct Image {
    unsigned int width, height;
    Vector *pixels, *current;
    unsigned int *samples;
    std::vector<Vector> *raw_samples;
    //
    Image(unsigned int w, unsigned int h) : width(w), height(h) {
      pixels = new Vector[width * height];
      samples = new unsigned int[width * height];
      current = new Vector[width * height];
      //raw_samples = new std::vector<Vector>[width * height];
    }
    ~Image();
    
    Vector getPixel(unsigned int x, unsigned int y);
    void setPixel(unsigned int x, unsigned int y, const Vector &v);
    Vector getSurroundingAverage(int x, int y, int pattern=0);
    inline double toInt(double x);
    void save(std::string filePrefix);
    void saveHistogram(std::string filePrefix, int maxIters);
};

#endif /* image_h */
