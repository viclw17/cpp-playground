//
//  sphere.cpp
//  montelight
//
//  Created by Wei Li on 2019-12-14.
//  Copyright © 2019 Victor Li. All rights reserved.
//
#include <cmath>
#include <random>
#include "sphere.h"

#define EPSILON 0.001f

double Sphere::intersects(const Ray &r) const {
    // Find if, and at what distance, the ray intersects with this object
    // Equation follows from solving quadratic equation of (r - c) ^ 2
    // http://wiki.cgsociety.org/index.php/Ray_Sphere_Intersection
    Vector offset = r.origin - center;
    double a = r.direction.dot(r.direction);
    double b = 2 * offset.dot(r.direction);
    double c = offset.dot(offset) - radius * radius;
    // Find discriminant for use in quadratic equation (b^2 - 4ac)
    double disc = b * b - 4 * a * c;
    // If the discriminant is negative, there are no real roots
    // (ray misses sphere)
    if (disc < 0) {
    return 0;
    }
    // The smallest positive root is the closest intersection point
    disc = sqrt(disc);
    double t = - b - disc;
    if (t > EPSILON) {
    return t / 2;
    }
    t = - b + disc;
    if (t > EPSILON) {
    return t / 2;
    }
    return 0;
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

Vector Sphere::getNormal(const Vector &p) const {
    // Point must have collided with surface of sphere which is at radius
    // Normalize the normal by using radius instead of a sqrt call
    return (p - center) / radius;
}
