//
//  main.cpp
//  Leetcode
//
//  Created by Wei Li on 2019-12-14.
//  Copyright © 2019 Victor Li. All rights reserved.
//

#include <iostream>

#include "const_test.h"
#include "class_test.h"
#include "argu_test.h"
#include "concurrent.h"
int main(){
//    argu_test argu_test;
//    argu_test.test();
        
//    class_test class_test;
//    class_test.test();
//    class_test.test_child();
    
    //const_test const_test;
    //const_test.test();
    //Dog d;
    //int i=9;
    //d.setAge(i); // we only want to set DOG's age with i, without modifiy i
    //cout << i << endl;
    
    //const string& n = d.getName1(); //n="modify";
//    string&       n = d.getName2(); n="modify";
//    string        n =  d.getName3();
    //cout << "new addr: " << &n << endl << n << endl;
    
    //Dog d1;
    //d1.printDogName();
    //const Dog d2;
    //d2.printDogName();

    concurrent concurrent;
    concurrent.main();

    
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
