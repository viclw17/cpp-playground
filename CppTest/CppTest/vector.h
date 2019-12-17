//
//  vector.h
//  CppTest
//
//  Created by Wei Li on 2019-12-16.
//  Copyright © 2019 Victor Li. All rights reserved.
//

#ifndef vector_h
#define vector_h
#include "stdio.h"
#include <string>
using namespace std;

// struct is a public class
struct Vector { 
    //double x, y, z; // this is bad!
    double x;
    double y;
    double z;
    //
    // default ctor
    // use member initializer list
    /*Vector() : x(0), y(0), z(0) {
        printf("call default ctor \n");
    }*/
    // use assignment
    /*Vector(){
        x = 0; y = 0; z = 0;
        printf("call default ctor \n");
    }*/

    // copy ctor
    // it should not affect the COPIED vector
    Vector(const Vector& o) : x(o.x), y(o.y), z(o.z) { 
        printf("call copy ctor \n"); 
    }

    // 'x' cannot be modified because it is being accessed through a const object
    //Vector(Vector& o) : x(o.x), y(o.y), z(o.z) {
    //    o.x = 4; // modified!!!
    //    printf("call copy ctor \n");
    //}

    // construct with elements
    Vector(double x_=0, double y_=0, double z_=0) : x(x_), y(y_), z(z_) { 
        printf("call assign ctor \n");
    }

    // instead of modifying either, return the sum as a new vector
    inline Vector operator+(const Vector &o) const {
        printf("call vector add... \n");
        return Vector(x + o.x, y + o.y, z + o.z);
    }
    // now we DO want to modify the object itself!
    inline Vector& operator+=(const Vector& rhs) {
        x += rhs.x; y += rhs.y; z += rhs.z;
        return *this;
    }

    string print() {
        return
            to_string(x) + " " + 
            to_string(y) + " " + 
            to_string(z) + "\n";
    }
    
};
#endif /* vector_h */
