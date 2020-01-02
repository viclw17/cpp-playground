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
//#include <iomanip>
#include <iostream>
#include <fstream>
//#include <sstream>
using namespace std;



class Image {
private:
    unsigned int width, height;
    Vector *pixels;
    //unsigned int *samples;

public:
    Image(unsigned int w, unsigned int h) : width(w), height(h) {
        pixels = new Vector[width * height]; // new?
        //samples = new unsigned int[width * height];
        // initialize default value!
        for(int y=0; y<height; y++){
            for(int x=0; x<width; x++){
                unsigned int index = (height - y - 1) * width + x;
                pixels[index] = Vector(0);
                //samples[index] = 0;
            }
        }
    }
    ~Image();
    
    void setPixel(unsigned int x, unsigned int y, const Vector &v);
    inline int toInt(double x);
    void save(std::string filePrefix);
};


void Image::setPixel(unsigned int x, unsigned int y, const Vector &v) {
    unsigned int index = (height - y - 1) * width + x;
    pixels[index] += v;
    //samples[index] += 1;
}



inline int Image::toInt(double x) {
    return pow(x, 1 / 2.2f) * 255;
//    return int(pow(x, 1 / 2.2f) * 255); // gamma and remap to 0~255

}



void Image::save(string filePrefix) {
    string filename = filePrefix + ".ppm";
    ofstream f;
    f.open(filename.c_str(), ofstream::out);

    // PPM header: P3 => RGB, width, height, and max RGB value
    f << "P3 " << width << " " << height << " " << 255 << std::endl;
    // For each pixel, write the space-separated RGB values
    for (int i=0; i < width * height; i++) {
        auto p = pixels[i];// / samples[i];
        int r = fmin(255, toInt(p.x));
        int g = fmin(255, toInt(p.y));
        int b = fmin(255, toInt(p.z));
        f << r << " " << g << " " << b << std::endl;
    }
}



Image::~Image() {
  delete[] pixels;
  //delete[] samples;

}



#endif /* image_h */
