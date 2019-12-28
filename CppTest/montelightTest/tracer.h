//
//  tracer.h
//  CppTest
//
//  Created by Wei Li on 2019-12-18.
//  Copyright © 2019 Victor Li. All rights reserved.
//

#ifndef tracer_h
#define tracer_h
#include <vector>
struct Tracer {
    std::vector<Shape *> scene;
    //
    Tracer(const std::vector<Shape *> &scene_) : scene(scene_){}
    std::pair<Shape *, double> getIntersection(const Ray &r) const;
//    Vector getRadiance(const Ray &r, int depth);
};

std::pair<Shape *, double> Tracer::getIntersection(const Ray &r) const {
    Shape *hitObj = NULL;
    double closest = 1e20f;
    for (Shape *obj : scene) {
    double distToHit = obj->intersects(r);
        if (distToHit > 0 && distToHit < closest) {
            hitObj = obj;
            closest = distToHit;
            }
        }
    return std::make_pair(hitObj, closest);
}


#endif /* tracer_h */
