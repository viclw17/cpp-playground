#include "test.h"
#include <iostream>
using namespace std;

int main(){
    person p;
    cout << "Age: " << p.get_age() << endl;
    cout << "Name: " << p.get_name() << endl;
    p.set_name("tom");
    cout << "New name: " << p.get_name() << endl;
    cout << p.publicVar << endl; 
    cout << p.get_address() << endl;
    return 0;
}