//
//  shape.h
//  CppTest
//
//  Created by Wei Li on 2019-12-18.
//  Copyright © 2019 Victor Li. All rights reserved.
//

#ifndef shape_h
#define shape_h
#include "vector.h"
#include "ray.h"

#define EPSILON 0.001f

struct Shape {
    Vector color;
    Vector emit;
    //
    Shape(const Vector color_, const Vector emit_) : 
        color(color_), emit(emit_){}

    virtual double intersects(const Ray &r) const { return 0; }
    virtual Vector randomPoint() const { return Vector(); }
    virtual Vector getNormal(const Vector &p) const { return Vector(); }
};

struct Sphere : Shape {
    Vector center;
    double radius;
    //
    Sphere(const Vector center_, double radius_, const Vector color_, const Vector emit_) :
        Shape(color_, emit_), center(center_), radius(radius_) {}

    double intersects(const Ray& r) const;
    //Vector randomPoint() const;
    //Vector getNormal(const Vector& p) const;
};

double Sphere::intersects(const Ray& r) const {
    // Find if, and at what distance, the ray intersects with this object
    // Equation follows from solving quadratic equation of (r - c) ^ 2
    // http://wiki.cgsociety.org/index.php/Ray_Sphere_Intersection
    Vector offset = r.origin - center;
    double a = r.direction.dot(r.direction);
    double b = 2 * offset.dot(r.direction);
    double c = offset.dot(offset) - radius * radius;
    // Find discriminant for use in quadratic equation (b^2 - 4ac)
    double discriminant = b * b - 4 * a * c;
    // If the discriminant is negative, there are no real roots
    // (ray misses sphere)
    if (discriminant < 0) {
        return 0;
    }
    return 1;
    // The smallest positive root is the closest intersection point
    /*discriminant = sqrt(discriminant);
    double t = -b - discriminant;
    if (t > EPSILON) {
        return t / 2;
    }
    t = -b + discriminant;
    if (t > EPSILON) {
        return t / 2;
    }
    return 0;*/
}

#endif /* shape_h */
