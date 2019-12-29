//
//  vector.h
//  CppTest
//
//  Created by Wei Li on 2019-12-16.
//  Copyright © 2019 Victor Li. All rights reserved.
//

#ifndef vector_h
#define vector_h
#include "stdio.h"
#include <string>
#include <cmath>

using namespace std;

// struct is a public class
struct Vector { 
    //double x, y, z; // this is bad!
    double x;
    double y;
    double z;
    //
    // default ctor
    // use member initializer list
    Vector() : x(0), y(0), z(0) {}
    // use assignment
    /*Vector(){
        x = 0; y = 0; z = 0;
        printf("call default ctor \n");
    }*/

    // copy ctor
    // it should not affect the COPIED vector
    Vector(const Vector& o) : x(o.x), y(o.y), z(o.z) { 
//        printf("call copy ctor \n");
    }

    // 'x' cannot be modified because it is being accessed through a const object
    //Vector(Vector& o) : x(o.x), y(o.y), z(o.z) {
    //    o.x = 4; // modified!!!
    //    printf("call copy ctor \n");
    //}

    // construct with elements
//    Vector(double x_=0, double y_=0, double z_=0) : x(x_), y(y_), z(z_) {
//        printf("call assign ctor \n");
//    }
    Vector(double v_) : x(v_), y(v_), z(v_) {}
    Vector(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {
//        printf("call assign ctor \n");
    }

    // instead of modifying either, return the sum as a new vector
    inline Vector operator+(const Vector &o) const {
//        printf("call vector add... \n");
        return Vector(x + o.x, y + o.y, z + o.z);
    }
    inline Vector operator-(const Vector &o) const;
    inline Vector operator*(const Vector &o) const;
    inline Vector operator/(double o) const;
    inline Vector operator*(double o) const;
    // now we DO want to modify the object itself!
    // unary operation
    // return ref to itself
    inline Vector& operator+=(const Vector& rhs);
    inline Vector& norm();
    inline Vector& clamp();
    inline double dot(const Vector &o) const;
    inline Vector cross(Vector &o);
    inline Vector& abs();
    inline double min();
    inline double max();

    string print() {
        return
            to_string(x) + " " + 
            to_string(y) + " " + 
            to_string(z) + "\n";
    }
    
};
inline Vector Vector::operator-(const Vector &o) const {
 return Vector(x - o.x, y - o.y, z - o.z);
}
inline Vector Vector::operator*(const Vector &o) const {
 return Vector(x * o.x, y * o.y, z * o.z);
}
inline Vector Vector::operator/(double o) const {
 return Vector(x / o, y / o, z / o);
}
inline Vector Vector::operator*(double o) const {
 return Vector(x * o, y * o, z * o);
}
inline Vector& Vector::operator+=(const Vector& rhs) {
    x += rhs.x; y += rhs.y; z += rhs.z;
    return *this; // this?
}
inline Vector& Vector::norm(){
  return *this = *this * (1 / sqrt(x * x + y * y + z * z));
}
inline double Vector::dot(const Vector &o) const {
  return x * o.x + y * o.y + z * o.z;
}
inline Vector Vector::cross(Vector &o){
  return Vector(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);
}
inline Vector& Vector::abs() {
  x = fabs(x); y = fabs(y); z = fabs(z);
  return *this;
}
inline double Vector::min() {
  return fmin(x, fmin(y, z));
}
inline double Vector::max() {
  return fmax(x, fmax(y, z));
}
inline Vector& Vector::clamp() {
  // C++11 lambda function: http://en.cppreference.com/w/cpp/language/lambda
  auto clampDouble = [](double x) {
    if (x < 0) return 0.0;
    if (x > 1) return 1.0;
    return x;
  };
  x = clampDouble(x); y = clampDouble(y); z = clampDouble(z);
  return *this;
}

#endif /* vector_h */
