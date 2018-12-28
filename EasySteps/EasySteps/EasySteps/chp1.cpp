#include <vector> // Include vector support.
#include <iostream>
using namespace std;

#define TEST 2
// 0 vector array
// 1 constants


int main() {
#if TEST == 0
	vector <int> vec(3, 100);
	cout << "Vector size : " << vec.size() << endl;
	cout << "Is empty ? : " << vec.empty() << endl;
	cout << "First element : " << vec.at(0) << endl;
	vec.pop_back(); // Remove fnal element.
	cout << "Vector size : " << vec.size() << endl;
	cout << "Final element : " << vec.back() << endl;
	vec.clear(); // Remove all elements.
	cout << "Vector size : " << vec.size() << endl;
	vec.push_back(200); // Add an element.
	cout << "Vector size : " << vec.size() << endl;
	cout << "First element : " << vec.front() << endl;
#elif TEST == 1
	const double PI = 3.1415926536;
	cout << "6\" circle circumference : " << (PI * 6) << endl;
	enum
	{
		RED = 1, 
		YELLOW, 
		GREEN, 
		BROWN, 
		BLUE, 
		PINK, 
		BLACK
	};
	cout << "I shot a red worth : " << RED << endl;
	cout << "Then a blue worth : " << BLUE << endl;
	cout << "Total scored : " << (RED + BLUE) << endl;
	typedef enum { 
		NEGATIVE, 
		POSITIVE } charge;
	charge neutral = NEGATIVE, live = POSITIVE;
	cout << "Neutral wire : " << neutral << endl;
	cout << "Live wire : " << live << endl;
#elif TEST == 2
	int a = 8, b = 4;
	cout << "Addition result : " << (a + b) << endl;
	cout << "Subtraction result : " << (a - b) << endl;
	cout << "Multiplication result : " << (a * b) << endl;
	cout << "Division result : " << (a / b) << endl;
	cout << "Modulus result : " << (a % b) << endl;

	cout << "Postfx increment : " << a++ << endl;
	cout << "Postfx result : " << a << endl;
	cout << "Prefx increment : " << ++b << endl;
	cout << "Prefx result : " << b << endl;

	long int test;
	cout << sizeof test << endl;
#endif
	return 0;
}