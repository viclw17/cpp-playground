//
//  child.h
//  CppTest
//
//  Created by Wei Li on 2019-12-18.
//  Copyright © 2019 Victor Li. All rights reserved.
//

#ifndef child_h
#define child_h
#include <iostream>
#include "class.hpp"
using namespace std;
class child1 : class1 {
    int a=30;
    int b=40;
public:
    Vector child_virtual1(){
        cout << "child virtual override!" << endl;
        return Vector(42);
    }
};

#endif /* child_h */
