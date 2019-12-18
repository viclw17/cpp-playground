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
using namespace std;

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
//    for(int i=0; i<64; i++){
//        for(int j=0; j<64; j++){
//            float u = float(i)/64;
//            float v = float(j)/64;
//            img.setPixel(i, j, Vector(u,v,0));
//        }
//    }
//    img.save("victor");
    
    child1 c;
    Vector v = c.child_virtual1();
    cout << v.print();
    
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
