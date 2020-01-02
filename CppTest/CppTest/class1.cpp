//
//  Class.cpp
//  CppTest
//
//  Created by Wei Li on 2019-12-16.
//  Copyright © 2019 Victor Li. All rights reserved.
//

#include "class1.hpp"
#include <iostream>
using namespace std;

// Default Constructor
class1::class1(){
    a = 10;
    b = 20;
}

class1::~class1(){
    cout << "class1 is destroyed!" << endl;
}
