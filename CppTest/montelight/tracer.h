//
//  tracer.h
//  montelight
//
//  Created by Wei Li on 2019-12-14.
//  Copyright © 2019 Victor Li. All rights reserved.
//

#ifndef tracer_h
#define tracer_h
#include "ray.h"
#include "shape.h"

#include <vector>



struct Tracer {
    std::vector<Shape *> scene;
    //
    Tracer(const std::vector<Shape *> &scene_) : scene(scene_){}
    std::pair<Shape *, double> getIntersection(const Ray &r) const;
    Vector getRadiance(const Ray &r, int depth);
};

#endif /* tracer_h */
