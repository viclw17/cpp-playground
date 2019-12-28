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


//val_ref.h
//int main() {
//    int x = 3;
//    f1(x);
//    cout << "by val: " << x << endl;
//    f2(x);
//    cout << "by ref: " << x << endl;
//    return 1;
//}

#ifdef PBRT_FLOAT_AS_DOUBLE
  typedef double Float;
#else
  typedef float Float;
#endif  // PBRT_FLOAT_AS_DOUBLE

inline bool Quadratic(float a, float b, float c, float *t0, float *t1) {
    // Find quadratic discriminant
    double discrim = (double)b * (double)b - 4 * (double)a * (double)c;
    if (discrim < 0) return false;
    double rootDiscrim = std::sqrt(discrim);

    // Compute quadratic _t_ values
    double q;
    if (b < 0)
        q = -.5 * (b - rootDiscrim);
    else
        q = -.5 * (b + rootDiscrim);
    *t0 = q / a;
    *t1 = c / q;
    if (*t0 > *t1) std::swap(*t0, *t1);
    return true;
}

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
    
    child1 c;
    Vector v = c.child_virtual1();
    cout << v.print();
    
    float t0 = 1
    
    
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
