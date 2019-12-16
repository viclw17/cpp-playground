//
//  main.cpp
//  Leetcode
//
//  Created by Wei Li on 2019-12-14.
//  Copyright © 2019 Victor Li. All rights reserved.
//

#include <iostream>
#include "Class.hpp"
#include "vector.h"
using namespace std;

int main()
{
    // Default constructor called automatically
    // when the object is created
//    Class1 c;
//    cout << "a: " << c.a << endl
//         << "b: " << c.b << endl;
    
    Vector v1(11);
    cout << "v1.x: " << v1.x << endl;
    Vector v2(v1);
    v2.x = 12;
    cout << "v1.x: " << v2.x << endl;
    cout << "v1+v2: " << (v1+v2).x << endl;
    return 1;
}
