//
//  class_test.h
//  CppTest
//
//  Created by Wei Li on 2019-12-31.
//  Copyright © 2019 Victor Li. All rights reserved.
//

#ifndef class_test_h
#define class_test_h
#include "class1.hpp"
#include <iostream>

class class_test{
public:
    void test(){
        cout << "***Run class_test" << endl;
        
        //Default constructor called automatically when the object is created
        class1 c; // default
        c = class1(1,2,3);
        class1* c_ptr = &c;
        cout << c_ptr << endl; // address
        cout << "get a thru ptr: " << c_ptr->a << endl;
        cout << "get a thru dot: " << c.a << endl;
        cout << "get b: " << c.b << endl;
        cout << "get c thru getter: " << c.getC() << endl;
        cout << "set c thru setter: "; c.setC(333);
        cout << c.getC() << endl;
    }
    
    void test_child(){
        child1 c;
        Vector v = c.virtual1();
        cout << v.print();
    }
};

#endif /* class_test_h */
