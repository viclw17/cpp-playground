//
//  Class.hpp
//  CppTest
//
//  Created by Wei Li on 2019-12-16.
//  Copyright © 2019 Victor Li. All rights reserved.
//

#ifndef class_hpp
#define class_hpp

#include <stdio.h>
#include <iostream>
using namespace std;
  
class class1 {
public:
    int a, b;
  
    // Default Constructor
    class1();

    //The idea of const functions is NOT to allow them to modify the object on which they are called. It is recommended the practice to make as many functions const as possible so that accidental changes to objects are avoided.
    int getA() const { 
        //a = 1; // 'a' cannot be modified because it is being accessed through a const object
        return a; 
    }
};

#endif /* class_hpp */

