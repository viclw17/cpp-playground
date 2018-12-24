#include <cstdlib> // random
#include <ctime> // time
#include <iostream>
using namespace std;

int main() {
	int i, j, k, nums[50];
	srand((int)time(0)); // Seed the random number generator with the current time
	//-858993460 == 0xcccccccc in hex.
	//This bit pattern is often used by microsoft compilers to detect buffer overruns and such.
	for (i = 1; i < 50; i++) 
		nums[i] = i;
	//Randomize the values in array elements 1-49
	for (i = 1; i < 50; i++) {
		j = (rand() % 49) + 1;
		k = nums[i];
		nums[i] = nums[j];
		nums[j] = k;
	}
	cout << "Your six lucky numbers are : ";
	for (i = 1; i < 7; i++) cout << nums[i] << " ";
	return 0;
}