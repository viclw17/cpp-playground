//
//  main.cpp
//  CppTest
//
//  Created by Wei Li on 2019-08-18.
//  Copyright © 2019 Victor Li. All rights reserved.
//

#include <iostream>
#include <cstdlib>
// containers
#include <vector>
#include <unordered_map>
using namespace std;

// the Node of a linked list
struct Node{
    int data;
    Node *next;
};

// the real linked list class
class LinkedList{
private:
    Node *head, *tail;
public:
    // constructor
    LinkedList(){
        head = NULL;
        tail = NULL;
    }
    
    Node* getHead(){
        return head;
    }
    
    Node* getTail(){
        return tail;
    }
    
    void append(int n){
        Node *tmp = new Node; // return a pointer to the newly allocated storage space
        tmp->data = n;
        tmp->next = NULL;
        if(head == NULL){
            head = tmp;
            tail = tmp;
        }else{
            tail->next = tmp;
            tail = tail->next;
        }
    }
    
    void traversal(){
        Node *tmp;
        tmp = head;
        while(tmp!=NULL){
            cout << tmp->data << endl;
            tmp = tmp->next;
        }
    }
    
    
};

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* initLinkedList(int x){
    ListNode* dummyRoot = new ListNode(0);
    ListNode* head = dummyRoot;
    for(int i=0; i<x+1; i++){
        head->next = new ListNode(i);
        head = head->next;
    }
    head = dummyRoot->next; // reset ptr back to the beginning of the list, but skip dummy root!
    delete dummyRoot; // deallocate
    return head;
}

ListNode* reverseLinkedList(ListNode* head) {
    ListNode *prev = NULL; // pointing to previous node
    ListNode *cur = head;
    ListNode *tmp;
    while(cur){
        tmp = cur->next;
        cur->next = prev; // set current node pointing to previous node
        prev = cur;
        cur = tmp;
    }
    return prev;
}


void printNiceLinkedList(ListNode* head){
    cout << "HEAD -> ";
    while(head!=NULL){
        cout << head->val;
        head = head->next;
        if(head!=NULL)
            cout << " -> ";
        else
            cout << " -> NULL " << endl;
    }
}

void printArrayPerLoop(vector<int>& arr, int i){
    cout << "After loop " << i << ": ";
    for (vector<int>::iterator it = arr.begin(); it!=arr.end(); ++it){
        cout << " " << *it;
    }
    cout << endl;
}

void printArrayFull(vector<int>& arr){
    cout << "Print full loop: ";
    for (int i : arr){
        cout << " " << i;
    }
    cout << endl;
}

//----------------------------------------
string reverseString(string s) {
    int i = 0, j = int(s.size()) - 1;
    while(i < j){
        swap(s[i++], s[j--]);
    }
    
    return s;
}

// Move Zeroes Solution 1: Staightforward
void moveZeroesS1(vector<int>& nums){
    int n = int(nums.size());
    int numZeroes = 0;
    for (int i=0; i<n; i++) {
        numZeroes+=(nums[i]==0);
    }
    vector<int> ans;
    for (int i=0; i<n; i++) {
        if (nums[i]!=0) {
            ans.push_back(nums[i]);
        }
        printArrayPerLoop(ans,i);
    }
    while (numZeroes--) {
        ans.push_back(0);
    }
    for (int i=0; i<n; i++) {
        nums[i]=ans[i];
    }
    printArrayFull(nums);
}
// Move Zeroes Solution 2: 2 pointers
void moveZeroesS2(vector<int>& nums){
    if (nums.empty()) return;
    int j = 0;
    for (int i = 0; i < nums.size(); i++){
        if (nums[i] != 0){
            nums[j] = nums[i]; // nums[j++] = nums[i];
            j = j+1;
        }
        printArrayPerLoop(nums,i);
    }
    for (int i = j; i < nums.size(); i++){
        nums[i] = 0;
        printArrayPerLoop(nums,i);
    }
}
// Move Zeroes Solution 3: swap
void moveZeroesS3(vector<int>& nums) {
    for (int lastNonZeroFoundAt = 0, cur = 0; cur < nums.size(); cur++) {
        if (nums[cur] != 0) {
            swap(nums[lastNonZeroFoundAt++], nums[cur]);
        }
        printArrayPerLoop(nums,cur);
    }
}

// Majority Element S1: Brute Force
int majorityElementS1(vector<int>& nums) {
    int majorityCount = int(nums.size()/2);
    int count = 0;
    for(int i=0; i<nums.size(); i++){
        count = 0; // reset counter!
        for(int j=0; j<nums.size(); j++){
            if(nums[i] == nums[j])
                count+=1;
        }
        if(count>majorityCount)
            return nums[i];
    }
    cout << "No majority element." << endl;
    return false;
}
// Majority Element S2: Hash Table
int majorityElementS2(vector<int>& nums) {
    unordered_map<int,int> counts;
    int n = int(nums.size());
    for(int i=0; i<n; i++){
        if(++counts[nums[i]]>n/2)
            return nums[i];
    }
    return false;
}

bool isAnagram(string s, string t) {
    if (s.length() != t.length()) {
        cout << "is NOT Anagram" << endl;
        return false;
    }
    int length = int(s.length());
    char* str1 = new char[length+1];
    char* str2 = new char[length+1];
    strcpy(str1, s.c_str());
    strcpy(str2, t.c_str());
    sort(str1, str1+length);
    sort(str2, str2+length);
    for (int i=0; i<length; i++) {
        if(str1[i] != str2[i]){
            cout << "is NOT Anagram" << endl;
            return false;
        }
    }
    cout << "is Anagram" << endl;
    return true;
}

bool isAnagramS2(string s, string t) {
    if (s.length() != t.length()) return false;
    int n = int(s.length());
    unordered_map<char, int> counts;
    for (int i = 0; i < n; i++) {
        counts[s[i]]++;
        counts[t[i]]--;
    }
    for (auto count : counts)
        if (count.second){
            cout << "is NOT Anagram" << endl;
            return false;
        }
    cout << "is Anagram" << endl;
    return true;
}

bool isAnagramS3(string s, string t) {
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());
    return s == t;
}

//bool containsDuplicate(vector<int>& nums) {
//    for (int i = 0; i < nums.size(); ++i) {
//        for (int j = 0; j < i; ++j) {
//            if (nums[j] == nums[i]) return true;
//        }
//    }
//    return false;
//}

void insertionSort(vector<int>& input){
    for (int j=0; j<input.size(); j++) {
        int key = input[j];
        int i = j-1;
        while (i>=0 && input[i]>key) {
            input[i+1]=input[i];
            i=i-1;
        }
        input[i+1]=key;
    }
    printArrayFull(input);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
//    LinkedList l1;
//    l1.append(3);
//    l1.append(4);
//    l1.append(2);
//    l1.traversal();
    
//    ListNode* head = NULL;
//    head = initLinkedList(5);
//    printNiceLinkedList(head);
//    head = reverseLinkedList(head);
//    printNiceLinkedList(head);
    
    

//    vector<int> nums = {2,1,4,3,12};
//    string s = "victorl";
//    cout << reverseString(s) << endl;
//    char* c = new char[s.size()];
//    strcpy(c, s.c_str());
//    cout << s.c_str() << endl;


//    cout << "----------" << endl;
//    cout << "Move Zeroes: " << endl;
//    vector<int> numsMZ = {0,1,0,3,12};
//    moveZeroesS1(numsMZ);
//    moveZeroesS2(numsMZ);
//    moveZeroesS3(numsMZ);
    
//    cout << "----------" << endl;
//    cout << "Majority Element: " << endl;
//    vector<int> numsME = {2,2,1,1,1,2,2};
//    cout << majorityElementS1(numsME)<< endl;
//    cout << majorityElementS2(numsME)<< endl;

//    cout << "----------" << endl;
//    cout << "Valid Anagram: " << endl;
//    string s = "art", t = "rat";
//    isAnagram(s,t);
//    isAnagramS2(s, t);
    
    vector<int> nums = {5,2,4,6,1,3};
    printArrayFull(nums);
    insertionSort(nums);
    
    
    // PLAY!!!
    // std::vector::push_back
//    vector<int> myvector;
//    for(int i=1; i<=5; i++)
//        myvector.push_back(i);
//    cout<<"myvector contains: ";
//    for (vector<int>::iterator it = myvector.begin(); it!=myvector.end(); ++it) {
//        cout << " " << *it;
//    }
//    cout << endl;
  
    return 0;
}
