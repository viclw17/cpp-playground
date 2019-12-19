//
//  main.cpp
//  Leetcode
//
//  Created by Wei Li on 2019-12-14.
//  Copyright © 2019 Victor Li. All rights reserved.
//

#include <iostream>
#include "stdio.h"

#include "class.hpp"
#include "child.h"
#include "val_ref.h"

#include "vector.h"
#include "image.h"
#include "shape.h"
#include "ray.h"
#include "tracer.h"
using namespace std;
std::vector<Shape *> simpleScene = {
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

//val_ref.h
//int main() {
//    int x = 3;
//    f1(x);
//    cout << "by val: " << x << endl;
//    f2(x);
//    cout << "by ref: " << x << endl;
//    return 1;
//}

int main()
{
    // Default constructor called automatically
    // when the object is created
//    class1 c; // default
//    c = class1(1,2,3);
//    class1* c_ptr = &c;
//    cout << c_ptr << endl; // address
//    cout << "a thru ptr: " << c_ptr->a << endl;
//    cout << "a thru dot: " << c.a << endl;
//    cout << "b: " << c.b << endl;
//    cout << c.getC() << endl;
//    c.setC(333);
//    cout << c.getC() << endl;
    
//    Image img(64,64);
//    Sphere sphere(Vector(0,0,3), 1, Vector(0), Vector(0));
//    for(int i=0; i<64; i++){
//        for(int j=0; j<64; j++){
//            double u = double(i)/64;
//            double v = double(j)/64;
////            img.setPixel(i, j, Vector(u, v, 1));
//            u = u*2-1;
//            v = v*2-1;
//            Vector o = Vector(0);
//            Vector d = Vector(u, v, 1) - o;
//            d = d.norm();
//            Ray r = Ray(o, d);
//            double t = sphere.intersects(r);
////            img.setPixel(i, j, Vector(t));
//            Vector hit = o + d * t;
//            Vector n = Vector(0);
//            if(t!=0){
//                n = sphere.getNormal(hit).norm();
//                n = (n+Vector(1))/2;
//            }
//            img.setPixel(i, j, n);
//        }
//    }
//    img.save("victor");
    
    /*child1 c;
    Vector v = c.child_virtual1();
    cout << v.print();*/
    
//    Vector v0;
//    cout << "v0: " << v0.print();
//    Vector v1(1,2,3);
//    cout << "v1: " << v1.print();
//    cout << (v0-v1).print() <<endl;
//    Vector v2 = v1;
//    Vector v3(v1);
//    cout << "v1: " << v1.print();
//    cout << "v2: " << v2.print();
//    cout << "v3: " << v3.print();

    return 1;
}
