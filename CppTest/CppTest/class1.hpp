//
//  Class.hpp
//  CppTest
//
//  Created by Wei Li on 2019-12-16.
//  Copyright © 2019 Victor Li. All rights reserved.
//

#ifndef class_hpp
#define class_hpp

#include <iostream>
#include "vector.h"
  
class class1 {
private:
    int c = 1;
public:
    int a, b;
    // ctor
    class1();
    //class1(int _a, int _b, int _c){a=_a;b=_b;c=_c;}
    class1(int _a, int _b, int _c):a(_a),b(_b),c(_c){}
    // dtor
    ~class1();

    //The idea of const functions is NOT to allow them to modify the object on which they are called. It is recommended the practice to make as many functions const as possible so that accidental changes to objects are avoided.
    int getC() const {
        //a = 1; // 'a' cannot be modified because it is being accessed through a const object
        return c;
    }
    void setC(int x) {c = x;}
    
    virtual Vector virtual1(const Vector &v) const { return Vector(); }
};

class child1 : class1 {
private:
    int a=30;
    int b=40;
public:
    Vector virtual1(){
        cout << "child virtual override!" << endl;
        return Vector(42);
    }
};
#endif /* class_hpp */

