/*
    Harnessing polymorphism
*/
#include <iostream>
using namespace std;

/*
    Pointing to classes
    Three cornerstones of Object Oriented Programming (OPP) are encapsulation, inheritance, polymorphism.
    Overloaded operators can be described as polymorphism. Class methods can also be polymorphic - a pointer to a base class can be assigned the memory address of a derived class.
*/
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
    Call methods of the same name and got directed to the approprite overriding method.
    Base class may contain only virtual methods but can still be called explicitly using :: scope resolution operator.
    This can allow inconsistencies.
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
    Classes whose sole purpose is to allow other classes to be derived from them are known as capability classes
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

/*
    Abstract Data Type ADT
    represents a concept, always the base to other classes.
    Initializing one or more of its methods with zero, known as "pure virtual methods" and must be overriden in derived classes.
    It is illegal to create an instance object of an ADT!
*/
class Shape // ADT
{
public:
    virtual int getArea() = 0; // pure virtual methods
    virtual int getEdge() = 0;
    virtual void Draw() = 0;
};

class Rect : public Shape
{
private:
    int height, width;
public: // public constructor and destructor
    Rect(int initWidth, int initHeight)
    {
        height = initHeight;
        width = initWidth;
    }
    ~Rect();

    int getArea() {return height * width;}
    int getEdge() {return (2*height)+(2*width);}

    void Draw()
    {
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){cout << "x ";}
        cout << endl;}
    }
};

/*
    Building complex hierarchies
    Derive ADT from ADT, to construct a complex hierarchy of classes.
*/
class Boat
{
protected:
    int length;
public:
    int getLength() {return length;}
    virtual void Model() = 0;
};

class Sailboat : public Boat
{
protected:
    int mast;
public:
    int getMast() {return mast;}
    virtual void Boom() = 0;
};

class Laser : public Sailboat
{
public:
    Laser() {mast = 19; length = 35;}
    ~Laser();
    void Model() {cout << "Laser Classic" << endl;} // implement virtual function from Boat
    void Boom() {cout << "Boom: 14ft" << endl;} // implement virtual function from Sailboat
};

int main()
{
    cout << endl << "*Pointing to classes*" << endl;
    Base* ptrA = new SubA;
    Base* ptrB = new SubB;
    // error: cast from pointer to smaller type 'int' loses information
    // change int cast to unsigned long cast
    ptrA -> Identify((unsigned long) &ptrA); // -> is used to call class methods
    ptrB -> Identify((unsigned long) &ptrB);

    cout << endl << "*Calling a virtual method*" << endl;
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

    cout << endl << "*Directing method calls*" << endl;
    Bird* pPigeon = new Pigeon;
    Bird* pChicken = new Chicken;
    // pPigeon -> Talk();
    // pPigeon -> Fly();
    // pChicken -> Talk();
    // pChicken -> Fly();
    // pPigeon -> Bird::Talk();
    // pChicken -> Bird::Fly(); // it's working, but inappropriated

    cout << endl << "*Providing capability classes*" << endl;
    pPigeon -> Talk();
    pChicken -> Talk();
    // pPigeon -> Bird::Talk(); // cannot call the base class method explicitly, becasue the method is defined as virtual
    // if(-1){cout << "Error! - Program ended." << endl; return 0;}
    // pPigeon -> Fly(); // Call will not be made.
    // pChicken -> Fly(); // Call will not be made.

    cout << endl << "*Abstract Data Type ADT*" << endl;
    Shape* pQuad = new Rect(7,3);
    Shape* pSquare = new Rect(5,5);
    pQuad -> Draw();
    cout << "Area is " << pQuad -> getArea() << endl;
    cout << "Perimeter is " << pQuad -> getEdge() << endl;
    pSquare -> Draw();
    cout << "Area is " << pSquare -> getArea() << endl;
    cout << "Perimeter is " << pSquare -> getEdge() << endl;

    cout << endl << "*Building complex hierarchies*" << endl;
    Laser* pLaser = new Laser;
    pLaser -> Model();
    cout << "Length: " << pLaser -> getLength() << "ft" << endl; // call base class methods
    cout << "Height: " << pLaser -> getMast() << "ft" << endl; // call base class methods
    pLaser -> Boom();

    return 0;
}
