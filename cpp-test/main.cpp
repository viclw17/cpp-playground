#include<iostream>
#include "operator_overload.h"

using namespace std;

struct movies_t {
	string title;
	int year;
};

movies_t Titanic;
movies_t* pTitanic;

/*
Algo to create a Fibonacci sequence of N numbers without recursion:

	Create 2 variables that will store the value of last and second last number.
	Initialize both the variables with 0.
	Now start a loop till N and for every i-th index,
		Print Sum of last and second last i.e SUM = LAST + SECOND_LAST
		Assign last to second last i.e. SECOND_LAST = LAST
		Assign Sum to last i.e. LAST = SUM
*/
void fibonacci(int n) {
	int last = 0;
	int secondLast = 0;
	for (int i = 0; i < n; i++) {
		int sum = last + secondLast;
		cout << sum << ", ";
		if (!sum)
			last = 1;
		secondLast = last;
		last = sum;
	}
}

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {};
};

ListNode addTwoNumbers(ListNode l1, ListNode l2) {
	ListNode dummyHead = new ListNode(0);
	ListNode p = l1, q = l2, curr = dummyHead;
	int carry = 0;
	while (p.next != NULL || q.next != NULL) {
		int x = (p.next != NULL) ? p.val : 0;
		int y = (q.next != NULL) ? q.val : 0;
		int sum = carry + x + y;
		carry = sum / 10;
		curr.next = new ListNode(sum % 10);
		curr = *curr.next;
		if (p.next != NULL) p = *p.next;
		if (q.next != NULL) q = *q.next;
	}
	if (carry > 0) {
		curr.next = new ListNode(carry);
	}
	return *dummyHead.next;
}



int main(){
	Person p1(10);
	Person p2(20);
	if(p1==p2)
		cout << "the age is equal!" << endl;
    else
        cout << "the age is different" << endl;

	// struct
	Titanic.title = "Titanic";
	Titanic.year = 1999;
	pTitanic = &Titanic;
	cout << pTitanic->title << endl;
	cout << (*pTitanic).year << endl;
	//cout << *pTitanic->title; // wrong

	// fibonacci
	fibonacci(20);

	ListNode l1, l2;
	ListNode curr = new ListNode(2);
	l1 = curr;
	curr = new ListNode(4);
	*(l1.next) = curr;
	curr = new ListNode(3);
	*(l1.next + 1) = curr;
	curr = new ListNode(5);
	l2 = curr;
	curr = new ListNode(6);
	*(l2.next) = curr;
	curr = new ListNode(4);
	*(l2.next + 1) = curr;
	ListNode result = addTwoNumbers(l1, l2);


	return 0;
}
