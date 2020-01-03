#pragma once
#include <iostream>
#include <thread>
using namespace std;

/*
Multi-processing
Interprocess communication
Multi-threading
Shared memory
Pros: fast to start / low overhead
Cons: difficult to implement / cannot wun on distributed system
*/


class concurrent {
public:
	void main();
};


void function_1() {
	cout << "function 1" << endl;
}

void concurrent::main() {
	thread t1(function_1);
	//t1.join(); // main thread waits for t1 to finish
	//t1.detach(); // t1 will freely on its own -- daemon process
	//if (t1.joinable())
	//	t1.join();

	// using RAII (resource acquisition is initialization)
	// Wrapper w(t1);
	// the destructor of Wrapper will call t1.join()

	/*try{
		for (int i = 0; i < 100; i++)
			cout << "from main: " << i << endl;
	}
	catch () {
		t1.join();
		throw;
	}*/

}