//
//  main_pt.cpp
//  CppTest
//
//  Created by Wei Li on 2019-12-25.
//  Copyright © 2019 Victor Li. All rights reserved.
//



#include "vector.h"
#include "image.h"
#include "shape.h"
#include "ray.h"
#include "tracer.h"
#include "triangle.h"
using namespace std;



double z = 5;
double R = 1000;
double r = .5;
double wall_offset = 1004;
Vector red = Vector(.75,.25,.25);
Vector blue = Vector(.25,.25,.75);
Vector white = Vector(.75);

vector<Shape *> testScene={
    // floor
    new Sphere(Vector( 0,-wall_offset, 0), R, white, Vector(),DIFF),
    new Sphere(Vector( 0, wall_offset, 0), R, white, Vector(),DIFF),
    new Sphere(Vector(-wall_offset, 0, 0), R, red  , Vector(),DIFF),
    new Sphere(Vector( wall_offset, 0, 0), R, blue , Vector(),DIFF),
    new Sphere(Vector( 0,0,wall_offset+5), R, white, Vector(),DIFF),
    new Sphere(Vector( 0,0,-wall_offset),  R, white, Vector(),DIFF),
    
    // light
    new Sphere(Vector( 0, 3, z-1), .5, Vector(1), Vector(1) * 400, LIGHT),
    //new Sphere(Vector(-2, -2, z), .5, Vector(1,0,0), Vector(1,0,0) * 200, LIGHT),
    //new Sphere(Vector( 2, -2, z), .5, Vector(0,1,0), Vector(0,1,0) * 200, LIGHT),
    
    // spheres
    //new Sphere(Vector( 0,  -1, z),    r, white, Vector(), REFL),
    //new Sphere(Vector( 1.5, 1, z+.5), r, red, Vector(), REFL),
    //new Sphere(Vector(-1.5, 0, z+.5), r, blue, Vector(), REFL),

    // 9 spheres
    //new Sphere(Vector( 0, 0, z), r, white, Vector(), REFL),
    //new Sphere(Vector(-1, 0, z), r, white, Vector(), REFL),
    //new Sphere(Vector( 1, 0, z), r, white, Vector(), REFL),
    //new Sphere(Vector(0, -1, z), r, white, Vector(), REFL),
    //new Sphere(Vector( 0, 1, z), r, white, Vector(), REFL),
    //new Sphere(Vector(-1,-1, z), r, white, Vector(), REFL),
    //new Sphere(Vector( 1,-1, z), r, white, Vector(), REFL),
    //new Sphere(Vector(-1, 1, z), r, white, Vector(), REFL),
    //new Sphere(Vector( 1, 1, z), r, white, Vector(), REFL),
    
    new Triangle(Vector(-1, -1, z+1), Vector(1, -1, z+1), Vector(-1, 1, z+1), white, Vector()),
    new Triangle(Vector(-1,  1, z+1), Vector(1,  1, z+1), Vector( 1,-1, z+1), white, Vector())
};



int main(){
    auto &scene = testScene;
    Tracer tracer = Tracer(scene);

    int w = 512;
    int h = 512;
//    w = 256;
//    h = 256;
    Image img(w,h);
    unsigned int SAMPLES = 1;
//    Sphere sphere(Vector(0,0,3), 1, Vector(0), Vector(0));
    for(int y=0; y<h/2; y++){
        fprintf(stderr, "\rRendering (%d spp) %5.2f%%", SAMPLES, 100.0*y / (h - 1));
        for(int x=0; x<w/2; x++){
            for (int s = 0; s < SAMPLES; ++s) {
//                double u = double(x)/w;
//                double v = double(y)/h;
                double u = double(x + drand48())/double(w); // 0~1
                double v = double(y + drand48())/double(h);
                //img.setPixel(y, x, Vector(u, v, 0)); // UV color
                u = u*2-1;
                v = v*2-1;
                Vector o = Vector(0, 0, 0);
                Vector d = Vector(u, v, 1.4) - o;
                // generate ray
                d = d.norm();
                Ray r = Ray(o, d);
                auto result = tracer.getIntersection(r); // pair<Shape *, double>
                Shape *hitObj = result.first;
                Vector hitPos = r.origin + r.direction * result.second;
                Vector norm = Vector();
                Vector radiance = Vector();
                if(hitObj != nullptr){
                    norm = hitObj->getNormal(hitPos);
                    radiance = tracer.getRadiance(r, 0);
                }
//                else{
//                    radiance = Vector(0.15f,0.21f,0.3f);
//                }
//                Vector normal = (norm+Vector(1))/2;
//                img.setPixel(x, y, normal/SAMPLES);
                img.setPixel(x, y, radiance/SAMPLES);
            }
        }
    }
        img.save("victor");

}

