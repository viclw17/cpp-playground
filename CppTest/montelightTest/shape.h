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
#define _USE_MATH_DEFINES
#include <math.h>

#define EPSILON 0.001f

#ifdef __APPLE__
#else
#define drand48() ((double)rand()/RAND_MAX)
//#define M_PI 3.14159265358979323846
//#define M_1_PI 0.318309886183790671538
#endif



enum Material { DIFF, REFL, REFR, LIGHT};  // material types, used in radiance()



struct Shape {
    Vector color;
    Vector emit;
    Material material;

    Shape(const Vector color_, const Vector emit_, const Material material_) :
        color(color_), emit(emit_), material(material_){}

    virtual double intersects(const Ray &r) const { return 0; }
    // pbrt
    //virtual bool Intersect(const Ray &ray, float *tHit, SurfaceInteraction *isect) const = 0;
    virtual Vector getNormal(const Vector &p) const { return Vector(); }
    virtual Vector randomPoint() const { return Vector(); }
};




struct Sphere : Shape {
    // sphere
    Vector center;
    double radius;
    
    Sphere(const Vector center_, double radius_, const Vector color_, const Vector emit_, const Material material_ = DIFF) :
        Shape(color_, emit_, material_), center(center_), radius(radius_) {}

    double intersects(const Ray& r) const;
    Vector randomPoint() const;
    Vector getNormal(const Vector& p) const;
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
//    return 1;
    // The smallest positive root is the closest intersection point
    double t = -b - sqrt(discriminant);
    if (t > EPSILON) {
        return t / (2*a);
    }
    t = -b + sqrt(discriminant);
    if (t > EPSILON) {
        return t / (2*a);
    }
    return 0;
}



Vector Sphere::getNormal(const Vector &p) const {
    // Point must have collided with surface of sphere which is at radius
    // Normalize the normal by using radius instead of a sqrt call
    return (p - center) / radius;
}



Vector Sphere::randomPoint() const {
    // TODO: Improved methods of random point generation as this is not 100% even
    // See: https://www.jasondavies.com/maps/random-points/
    //
    // Get random spherical coordinates on light
    double theta = drand48() * M_PI;
    double phi = drand48() * 2 * M_PI;
    // Convert to Cartesian and scale by radius
    double dxr = radius * sin(theta) * cos(phi);
    double dyr = radius * sin(theta) * sin(phi);
    double dzr = radius * cos(theta);
    return Vector(center.x + dxr, center.y + dyr, center.z + dzr);
}



#endif /* shape_h */
