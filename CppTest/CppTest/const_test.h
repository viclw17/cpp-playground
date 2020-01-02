//
//  const.h
//  CppTest
//
//  Created by Wei Li on 2019-12-31.
//  Copyright © 2019 Victor Li. All rights reserved.
//

#ifndef const_h
#define const_h
#include <iostream>
#include <string>

// https://www.youtube.com/playlist?list=PLE28375D4AC946CC3
class const_test{
public:
    void test(){
        std::cout << "*** Run const_test" << std::endl;
        
        // const - A compile time constraint that an object can not be modified.
        // 1. data is const
        const int i = 9;
        //i = 9; // Cannot assign to variable 'i' with const-qualified type 'const int'
        // 2. data is const, pointer is not
        const int *p1 = &i;
        //*p1 = 5; // Read-only variable is not assignable
        p1++;
        // 3. pointer is const, data is not
        int* const p2 = nullptr;
        // 4. data and pointer are both const
        const int* const p3 = nullptr;

        int const *p4 = &i;
        const int *p5 = &i;
        // if const is on the left of *, data is const
        // if const is on the right of *, pointer is const

        const int j = 6;
        const_cast<int&>(j) = 6; // cast away const
        int k;
        static_cast<const int&>(k); // cast into const

        /*
            Why use const:
            1. Guards against inadvertent write to the variable;
            2. Self documenting;
            3. Enables compiler to do more optimization, making code tighter;
            4. const means the variable can be put in ROM.
        */
    }
};



// const used with functions
// https://www.youtube.com/watch?v=RC7uE_wl1Uc&list=PLE28375D4AC946CC3&index=2
class Dog{
    int age;
    std::string name;
public:
    Dog() {age = 3; name = "dummy";}
    
    // const parameters
    // pass by reference
    void setAge(const int& a) {age = a; /*a++;*/} // "a" cannot be modified!
    // overloaded with non-const version
    void setAge(int& a) {age = a; a++;} // "a" got modified!
    // pass by value
    //void setAge(int a) {age = a;}
    //void setAge(const int a) {age = a;} // cannot redeclared, treated as same function
    
    // const return value
    // return a const string reference
    const std::string& getName1() {name = "dummmyyyy";
        std::cout << "old addr: "<< &name << std::endl; return name;}
    // return a regular reference
    std::string&       getName2() {name = "dummmyyyy";
        std::cout << "old addr: "<< &name << std::endl; return name;}
    // value reture introduces a copy!
    std::string        getName3() {name = "dummmyyyy";
        std::cout << "old addr: "<< &name << std::endl; return name;}
    
    // const function
    void printDogName() const {std::cout << name << "const" << std::endl; /*age++;*/}
    // can only call other const function
    //void printDogName() const {std::cout << getName1() << "const" << std::endl;}
    // overloaded with non-const version
    void printDogName() {std::cout << name << "non-const" << std::endl;}
    
};
#endif /* const_h */
