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
struct Vector { // struct is a public class
    double x, y, z;
    //
    Vector(const Vector &o) : x(o.x), y(o.y), z(o.z) {printf("call constructor 1 \n");}
    Vector(double x_=0, double y_=0, double z_=0) : x(x_), y(y_), z(z_) { printf("call constructor 2 \n");}
    
    inline Vector operator+(const Vector &o) const {
        printf("call vector add... \n");
        return Vector(x + o.x, y + o.y, z + o.z);
    }
    
};
#endif /* vector_h */
