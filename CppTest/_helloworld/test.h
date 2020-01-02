#include <string>
using namespace std;

class person{
public:
    person(){
        name = "person";
        address = "coquitlam";
        age = 11;

        publicVar = 42;
    }

    void set_name(string n);
    string get_name();

    string get_address();

    void set_age();
    int get_age();
    
    int publicVar;

private:
    string name;
    // Inside your class, you have to explicitly specify the array size
    // char address[] = "coquitlam"; // BUG

    // char* address;
    // char * address = "coquitlam";
    // const char * address = "coquitlam";
    string address;
    int age;
};

// clang++ -c -std=c++11 main.cpp test.cpp
// clang++ main.o test.o -o test

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