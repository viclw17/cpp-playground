/*
    Harnessing polymorphism

    Pointing to classes
    Three cornerstones of Object Oriented Programming (OPP) are encapsulation, inheritance, polymorphism.
    Overloaded operators can be described as polymorphism. Class methods can also be polymorphic - a pointer to a base class can be assigned the memory address of a derived class.
*/

#include <iostream>
using namespace std;

class Base
{
public:
    void Identify(int adr) const
    {
        cout << "Base class called by 0x" << hex << adr << endl; // hex is an output manipulator
    }
};

class SubA : public Base {};
class SubB : public Base {};

/*
    Calling a virtual method
    A base class pointer that is bound to a derived class can be used to
    call derived class methods that have been inherited from the base class;
    call a method in the base class using :: explicitly.
    Methods that are unique to the derived class must be called via an instance object.
    An inherited method in a derived class can override that in the base class when the base method has been declared as virtual.
*/
class Parent
{
public:
    void Common() const
    {cout << "I am part of this family, ";}
    virtual void Identify() const
    {cout << "I am the parent" << endl;}
};

class Child : public Parent
{
public:
    void Identify() const
    {cout << "I am the child" << endl;} // override
};

class Grandchild : public Child
{
public:
    void Identify() const
    {cout << "I am the grandchild" << endl;}
    void Relate() const
    {cout << "Grandchild has parent and grandparent" << endl;}
};

/*
    Directing method calls
*/
// class Bird
// {
// public:
//     virtual void Talk() const
//     {cout << "A bird talks... " << endl;}
//     virtual void Fly() const
//     {cout << "A bird flies... " << endl;}
// };
//
// class Pigeon : public Bird
// {
// public:
//     void Talk() const
//     {cout << "Coo!" << endl;}
//     void Fly() const
//     {cout << "A pigeon flies away... " << endl;}
// };
//
// class Chicken : public Bird
// {
// public:
//     void Talk() const
//     {cout << "Cluck!" << endl;}
//     void Fly() const
//     {cout << "I\'m just a chicken - I can\'t fly!" << endl;}
// };

/*
    Providing capability classes
    Classes whose sole purpose is to allow other classes to be derived from them are known as ~
    They provides capabilities to the derived classes. Contain no data but declare virtual methods that can be overriden in their derived classes.

    ... Its methods no longer contain output statements but return a -1(error) value if they are called explicitly. Return type is changed from void to int.
*/
class Bird
{
public:
    virtual int Talk() const {return -1;}
    virtual int Fly() const {return -1;}
};

class Pigeon : public Bird
{
public:
    int Talk() const
    {cout << "Coo!" << endl; return 0;}
    int Fly() const
    {cout << "A pigeon flies away... " << endl; return 0;}
};

class Chicken : public Bird
{
public:
    int Talk() const
    {cout << "Cluck!" << endl; return 0;}
    int Fly() const
    {cout << "I\'m just a chicken - I can\'t fly!" << endl; return 0;}
};

//////////
int main()
{
    Base* ptrA = new SubA;
    Base* ptrB = new SubB;
    // error: cast from pointer to smaller type 'int' loses information
    // change int cast to unsigned long cast
    ptrA -> Identify((unsigned long) &ptrA); // -> is used to call class methods
    ptrB -> Identify((unsigned long) &ptrB);

    Child son;
    Grandchild grandson;
    Parent* ptrChild = &son;
    Parent* ptrGrandchild = &grandson;
    ptrChild -> Common(); // inherited
    ptrChild -> Identify(); // overriding
    ptrGrandchild -> Common(); // inherited
    ptrGrandchild -> Identify(); // overriding
    ptrChild -> Parent::Common(); // Explicit
    ptrChild -> Parent::Identify(); // Explicit
    grandson.Relate(); // via instance

    Bird* pPigeon = new Pigeon;
    Bird* pChicken = new Chicken;
    // pPigeon -> Talk();
    // pPigeon -> Fly();
    // pChicken -> Talk();
    // pChicken -> Fly();
    // pPigeon -> Bird::Talk();
    // pChicken -> Bird::Fly(); // inappropriated call

    pPigeon -> Talk();
    pChicken -> Talk();
    pPigeon -> Bird::Talk();
    if(-1){cout << "Error! - Program ended." << endl; return 0;}
    pPigeon -> Fly(); // Call will not be made.
    pChicken -> Fly(); // Call will not be made.

    return 0;
}
