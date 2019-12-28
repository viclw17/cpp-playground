//
//  main_pt.cpp
//  CppTest
//
//  Created by Wei Li on 2019-12-25.
//  Copyright © 2019 Victor Li. All rights reserved.
//

#include <stdio.h>

#include "vector.h"
#include "image.h"
#include "shape.h"
#include "ray.h"
#include "tracer.h"
using namespace std;

vector<Shape *> simpleScene = {
  // Left sphere
  new Sphere(Vector(1e5+1,40.8,81.6), 1e5f, Vector(.75,.25,.25), Vector()),
  // Right sphere
  new Sphere(Vector(-1e5+99,40.8,81.6), 1e5f, Vector(.25,.25,.75), Vector()),
  // Back sphere
  new Sphere(Vector(50,40.8, 1e5), 1e5f, Vector(.75,.75,.75), Vector()),
  // Floor sphere
  new Sphere(Vector(50, 1e5, 81.6), 1e5f, Vector(.75,.75,.75), Vector()),
  // Roof sphere
  new Sphere(Vector(50,-1e5+81.6,81.6), 1e5f, Vector(.75,.75,.75), Vector()),
  // Traditional mirror sphere
  new Sphere(Vector(27,16.5,47), 16.5f, Vector(1,1,1) * 0.799, Vector()),
  // Traditional glass sphere
  new Sphere(Vector(73,16.5,78), 16.5f, Vector(1,1,1) * 0.799, Vector()),
  // Light source
  //new Sphere(Vector(50,681.6-.27,81.6), 600, Vector(1,1,1) * 0.5, Vector(12,12,12))
  new Sphere(Vector(50,65.1,81.6), 8.5, Vector(), Vector(4,4,4) * 100) // Small = 1.5, Large = 8.5
};

vector<Shape *> testScene={
    new Sphere(Vector(0,0,3),1,Vector(0),Vector(0)),
    new Sphere(Vector(0,1,3),1,Vector(0),Vector(0))
};

int main()
{
    auto &scene = testScene;
    Tracer tracer = Tracer(scene);

    Image img(64,64);
    //Sphere sphere(Vector(0,0,3), 1, Vector(0), Vector(0));
    for(int i=0; i<64; i++){
        for(int j=0; j<64; j++){
            double u = double(i)/64;
            double v = double(j)/64;
    //            img.setPixel(i, j, Vector(u, v, 1));
            u = u*2-1;
            v = v*2-1;
            Vector o = Vector(0, 0, 0);
            Vector d = Vector(u, v, 1) - o;
            d = d.norm();
            Ray r = Ray(o, d);
            pair<Shape *, double> trace_result = tracer.getIntersection(r);
            double t = trace_result.second; // = sphere.intersects(r);
    //            img.setPixel(i, j, Vector(t));
            Vector hit = o + d * t;
            Vector n = Vector(0);
    //            if(t!=0){
    //                n = sphere.getNormal(hit).norm();
                n = trace_result.first->getNormal(hit).norm();
    //                n = (n+Vector(1))/2;
    //            }
            img.setPixel(i, j, n);
        }
    }
    //    img.save("victor");

}

