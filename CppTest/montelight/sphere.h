//
//  sphere.h
//  montelight
//
//  Created by Wei Li on 2019-12-14.
//  Copyright © 2019 Victor Li. All rights reserved.
//

#ifndef sphere_h
#define sphere_h

#include "vector.h"
#include "shape.h"
#include "ray.h"

struct Sphere : Shape {
    Vector center;
    double radius;
    //
    Sphere(const Vector center_, double radius_, const Vector color_, const Vector emit_) :
    Shape(color_, emit_), center(center_), radius(radius_) {}

    double intersects(const Ray &r) const;
    Vector randomPoint() const;
    Vector getNormal(const Vector &p) const;
};

#endif /* sphere_h */
