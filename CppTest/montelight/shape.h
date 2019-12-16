//
//  shape.h
//  montelight
//
//  Created by Wei Li on 2019-12-14.
//  Copyright © 2019 Victor Li. All rights reserved.
//

#ifndef shape_h
#define shape_h

#include "vector.h"
#include "ray.h"

struct Shape {
    Vector color, emit;
    //
    Shape(const Vector color_, const Vector emit_) : color(color_), emit(emit_){}

    virtual double intersects(const Ray &r) const { return 0; }
    virtual Vector randomPoint() const { return Vector(); }
    virtual Vector getNormal(const Vector &p) const { return Vector(); }
};

#endif /* shape_h */
