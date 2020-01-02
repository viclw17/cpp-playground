#pragma once
#include <iostream>
using namespace std;

//Pass by value
void f1(int n) {
    n = n + 10;
}
//Output: 3. 
//Disadvantage : When parameter x pass through f function then compiler creates a copy in memory in of x.So wastage of memory.

//Pass by reference
void f2(int& n) {
    n = n + 10;
}
//Output: 13. It eliminate pass by value disadvantage, but if programmer do not want to ch ange the value then use constant reference

//Constant reference
//void f3(const int& n) {
//    n = n + 10; // Error: assignment of read-only reference  ‘n’
//}
//Output: Throw error at n = n + 10 because when we pass const reference parameter argument then it is read - only parameter, you cannot change value of n.

class argu_test{
public:
    void test(){
        cout << "***Run argu_test" << endl;
        int x = 3;
        f1(x);
        cout << "by val: " << x << endl;
        f2(x);
        cout << "by ref: " << x << endl;
    }
};
