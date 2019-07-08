#include <iostream>
#include <cstdlib> //c-std-lib
#include <ctime>

using namespace std;

void shuffle(int[], int);
void printArray(int[], int);
void swap(int *x, int *y);

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
    while (i-- > 0) {  interesting about --i and i--, prefix and postfix
        cout << &i << " " << i << " ";
        r1 = rand();  0-32767
        r2 = r1 % 10;  0-9
        cout << r2 << endl;
    }*/
    
    // about prefix postfix
    // https://stackoverflow.com/a/7031409/4097480
    /*int i = 10;    (1)
    cout << "i=" << i << endl;
    int j = ++i;   (2)
    cout << "j=" << j << endl;
    int k = i++;   (3)
    cout << "k=" << k << endl;
    cout << "now, i=" << i << endl;*/
    
    // Fisher–Yates shuffle
    // https://www.geeksforgeeks.org/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm/
    /*int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int i = 10;
    while (i-- > 0) {
        shuffle(arr, n);
        printArray(arr, n);
    }*/

    /* understant c++ mod and mathematic modulo
    int a = (-1) % 256;  % is different from modulo!
     -1 MOD 256 = 255, is according to Euclidean Division
     if -1 / 256, then quotient q is -1 and remainder r is 255,
     since -1 = 256 * -1 + 255
    cout << "a = " << a << endl;
    unsigned char b;
    cout << "unsigned char is " << sizeof(b) << " byte" << endl;
    b = -1;
    cout << (int)b << endl;*/
    
    // local variable declaration:
    int a = 100;
    int b = 200;
    
    cout << "Before swap, value of a :" << a << endl;
    cout << "Before swap, value of b :" << b << endl;
    
    /* calling a function to swap the values.
     * &a indicates pointer to a ie. address of variable a and
     * &b indicates pointer to b ie. address of variable b.
     */
    swap(&a, &b);
    
    cout << "After swap, value of a :" << a << endl;
    cout << "After swap, value of b :" << b << endl;
    
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

// function definition to swap the values.
void swap(int *x, int *y) {
    int temp;
    temp = *x; /* save the value at address x */
    *x = *y; /* put y into x */
    *y = temp; /* put x into y */
    
    return;
}
