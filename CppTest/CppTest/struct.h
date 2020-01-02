//
//  struct.h
//  CppTest
//
//  Created by Wei Li on 2020-01-01.
//  Copyright © 2020 Victor Li. All rights reserved.
//

#ifndef struct_h
#define struct_h

// small passive objects that carry public data and have no or few  basic member functions
// data container
struct Person_t{
    string name; // public
    unsigned age;
};

//bigger active objects that carry private data, interfaced through public member functions
// complex data structure
class Person{
    // add "_"!
    // TODO: Convention: m_age(member), _age(for global variable)
    string name_; // private
    unsigned age_;
public:
    // we dont want to change age_
    unsigned age() const {return age_;} // getter/accessor
    void set_age(unsigned a) {age_ = a;} // setter/mutator
};

/*
int main(){
    Person_t PT;
    cout << PT.age;
    
    Person P;
    cout << P.age();
    P.set_age(4);
}
*/

#endif /* struct_h */
