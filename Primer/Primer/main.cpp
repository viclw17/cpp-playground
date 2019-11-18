#include <iostream>
#include <cstdlib> //c-std-lib
#include <ctime>

using namespace std;

void shuffle(int[], int);
void printArray(int[], int);

int main() {
	// simple sum of 1-10
	/*int sum = 0, var = 1;
	while (var <= 10) {
		cout << var << endl;
		sum += var;
		var++;
	}
	cout << sum;*/
	
	// about random
	/*time_t t = time(0);
	srand((int)t);
	int r1 = 0;
	int r2 = 0;
	int i = 10;
	while (i-- > 0) { // interesting about --i and i--, prefix and postfix
		cout << &i << " " << i << " ";
		r1 = rand(); // 0-32767
		r2 = r1 % 10; // 0-9
		cout << r2 << endl;
	}*/
	
	// about prefix postfix
	// https://stackoverflow.com/a/7031409/4097480
	/*int i = 10;   // (1)
	cout << "i=" << i << endl;
	int j = ++i;  // (2)
	cout << "j=" << j << endl;
	int k = i++;  // (3)
	cout << "k=" << k << endl;
	cout << "now, i=" << i << endl;*/
	
	// Fisher–Yates shuffle
	// https://www.geeksforgeeks.org/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm/
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	int n = sizeof(arr) / sizeof(arr[0]);
	int i = 10;
	while (i-- > 0) {
		shuffle(arr, n);
		printArray(arr, n);
	}

	/*// understand c++ mod and mathematic modulo
	int a = (-1) % 256; // % is different from modulo!
	// -1 MOD 256 = 255, is according to Euclidean Division
	// if -1 / 256, then quotient q is -1 and remainder r is 255,
	// since -1 = 256 * -1 + 255
	cout << "a = " << a << endl;
	unsigned char b;
	cout << "unsigned char is " << sizeof(b) << " byte" << endl;
	b = -1;
	cout << (int)b << endl;*/

	////////// Compound types
	// Pointers
	/*int *ip1, *ip2;
	double dp, *dp2;
	// btw, right now all junks! Didn't initialize!
	int ival = 42;
	int *p = &ival;*/
	
	// Taking the Address of an Object
	/*double dval; // btw, junk! didn't initialize!
	double *pd = &dval; // ok, initialize with address
	double *pd2 = pd; // ok, initialize with another same type pointer
	//int *pi = pd; // error: initialize int pointer with double pointer
	//pi = &dval; // error: assigning the address of a double to an int pointer*/
	
	// Using a Pointer to Access an Object
	/*int ival = 42; // ival is an object
	int *p = &ival; // dereference to access the object!
	cout << p  << endl; // print address
	cout << *p << endl; // print content aka 42
	
	int *p1 = nullptr;
	int *p2 = 0;
	//int p2 = 0; // error
	int *p3 = NULL; // #include <cstdlib> //c-std-lib

	int i = 42;
	int *pi = 0; // initialized but point to no object
	int *pi2 = &i;
	int *pi3;
	pi3 = pi2; // pointing to the same address now
	pi2 = 0;
	pi = &ival;
	cout << "ival: " << ival << endl;
	*pi = 0; // empty the pointer
	cout << "now ival: " << *pi << endl;*/
	
	// Understanding Compound Type Declarations
	/*int i = 1024, *p = &i, &r = i;
	// about contents:
	int *p2; // if un-initialize, 0xcccccccc{???}
	int *p3 = 0;      // initialized with 0,      0x00000000{???}
	int *p4 = nullptr;// initialized with nullptr,0x00000000{???}
	// declaration convention
	int* p1, p2; // pi is int pointer, p2 is just int!
	// 1.
	int *p1, *p2; // both are int pointers
	// 2.
	int* p1;
	int* p2;*/
	
	// pointer to pointer
	/*int ival = 1024;
	int *pi = &ival;
	int **ppi = &pi;
	
	cout << "The value of ival\n"
		<< "direct value: " << ival << "\n"
		<< "indirect value: " << *pi << "\n"
		<< "doubly indirect value: " << **ppi
		<< endl;*/
	
	// reference to pointer
	/*int i = 42;
	int *p;
	int *&r = p;
	r = &i;
	*r = 0;*/

	// const
	// to do...
	

	return 0;
}

void shuffle(int arr[], int n) {
	srand(time(NULL));
	for (int i = n - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		swap(arr[i], arr[j]); // pass by reference
	}
}
void printArray(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}