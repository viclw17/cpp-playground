#include <string>
#include "test.h"
using namespace std;

void person::set_name(string n){
    name = n;
}

string person::get_name(){
    return name;
}

string person::get_address(){
    return address;
}

int person::get_age(){
    return age;
}