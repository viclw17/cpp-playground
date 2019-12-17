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
#include "val_ref.h"
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
    class1 c;
    cout << "a: " << c.a << endl
         << "b: " << c.b << endl;
    
    Vector v0;
    cout << "v0: " << v0.print();
    Vector v1(1,1,1);
    cout << "v1: " << v1.print();
    Vector v2 = v1;
    Vector v3(v1);    
    cout << "v1: " << v1.print();
    cout << "v2: " << v2.print();
    cout << "v3: " << v3.print();

    return 1;
}
