//
//  image.h
//  CppTest
//
//  Created by Wei Li on 2019-12-17.
//  Copyright © 2019 Victor Li. All rights reserved.
//

#ifndef image_h
#define image_h
#include "vector.h"

#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Image {
private:
    unsigned int width, height;
    Vector *pixels, *current;
    unsigned int *samples;
//    std::vector<Vector> *raw_samples;

public:
    Image(unsigned int w, unsigned int h) : width(w), height(h) {
        // new?
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

Vector Image::getPixel(unsigned int x, unsigned int y) {
  unsigned int index = (height - y - 1) * width + x;
  return current[index];
}

void Image::setPixel(unsigned int x, unsigned int y, const Vector &v) {
  unsigned int index = (height - y - 1) * width + x;
  pixels[index] += v;
  samples[index] += 1;
  current[index] = pixels[index] / samples[index];
  //raw_samples[index].push_back(v);
}

//Vector Image::getSurroundingAverage(int x, int y, int pattern) {
//  unsigned int index = (height - y - 1) * width + x;
//  Vector avg;
//  int total;
//  for (int dy = -1; dy < 2; ++dy) {
//    for (int dx = -1; dx < 2; ++dx) {
//      if (pattern == 0 && (dx != 0 && dy != 0)) continue;
//      if (pattern == 1 && (dx == 0 || dy == 0)) continue;
//      if (dx == 0 && dy == 0) {
//        continue;
//      }
//      if (x + dx < 0 || x + dx > width - 1) continue;
//      if (y + dy < 0 || y + dy > height - 1) continue;
//      index = (height - (y + dy) - 1) * width + (x + dx);
//      avg += current[index];
//      total += 1;
//    }
//  }
//  return avg / total;
//}

inline double Image::toInt(double x) {
  return pow(x, 1 / 2.2f) * 255; // gamma and remap to 0~255
}

void Image::save(string filePrefix) {
  string filename = filePrefix + ".ppm";
  ofstream f;
  f.open(filename.c_str(), ofstream::out);
  // PPM header: P3 => RGB, width, height, and max RGB value
  f << "P3 " << width << " " << height << " " << 255 << std::endl;
  // For each pixel, write the space-separated RGB values
  for (int i=0; i < width * height; i++) {
    auto p = pixels[i] / samples[i];
    unsigned int r = fmin(255, toInt(p.x)), g = fmin(255, toInt(p.y)), b = fmin(255, toInt(p.z));
    f << r << " " << g << " " << b << std::endl;
  }
}

//void Image::saveHistogram(std::string filePrefix, int maxIters) {
//  std::string filename = filePrefix + ".ppm";
//  std::ofstream f;
//  f.open(filename.c_str(), std::ofstream::out);
//  // PPM header: P3 => RGB, width, height, and max RGB value
//  f << "P3 " << width << " " << height << " " << 255 << std::endl;
//  // For each pixel, write the space separated RGB values
//  for (int i=0; i < width * height; i++) {
//    auto p = samples[i] / maxIters;
//    unsigned int r, g, b;
//    r= g = b = fmin(255, 255 * p);
//    f << r << " " << g << " " << b << std::endl;
//  }
//}

Image::~Image() {
  delete[] pixels;
  delete[] samples;
}

#endif /* image_h */
