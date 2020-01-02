//
//  triangle.h
//  montelightTest
//
//  Created by Wei Li on 2020-01-01.
//  Copyright © 2020 Victor Li. All rights reserved.
//

#ifndef triangle_h
#define triangle_h
#include "shape.h"

double kEpsilon =0.0001;
struct Triangle : Shape{
    Vector v0;
    Vector v1;
    Vector v2;
    
    Triangle(const Vector v0_, const Vector v1_, const Vector v2_,
             const Vector color_, const Vector emit_, const Material m_ = DIFF)
    : Shape(color_, emit_, m_), v0(v0_), v1(v1_), v2(v2_){}
    
    double intersects(const Ray& r) const;
//    Vector randomPoint() const;
    Vector getNormal(const Vector& p) const;
    
};

Vector Triangle::getNormal(const Vector &p) const {
    // compute plane's normal
    Vector v0v1 = v1 - v0;
    Vector v0v2 = v2 - v0;
    // no need to normalize
    Vector N = v0v1.cross(v0v2); // N
    return N;
}

// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/why-are-triangles-useful
double Triangle::intersects(const Ray& r) const
{
    Vector orig = r.origin;
    Vector dir = r.direction;
    
    // compute plane's normal
    Vector v0v1 = v1 - v0;
    Vector v0v2 = v2 - v0;
    // no need to normalize
    Vector N = v0v1.cross(v0v2); // N
    double area2 = N.length();
 
    // Step 1: finding P
 
    // check if ray and plane are parallel ?
    double NdotRayDirection = N.dot(dir);
    if (fabs(NdotRayDirection) < kEpsilon) // almost 0
        return false; // they are parallel so they don't intersect !
 
    // compute d parameter using equation 2
    double d = N.dot(v0);
 
    // compute t (equation 3)
    double t = (N.dot(orig) + d) / NdotRayDirection;
    // check if the triangle is in behind the ray
    if (t < 0) return false; // the triangle is behind
 
    // compute the intersection point using equation 1
    Vector P = orig + dir *t;
 
    // Step 2: inside-outside test
    Vector C; // vector perpendicular to triangle's plane
 
    // edge 0
    Vector edge0 = v1 - v0;
    Vector vp0 = P - v0;
    C = edge0.cross(vp0);
    if (N.dot(C) < 0) return false; // P is on the right side
 
    // edge 1
    Vector edge1 = v2 - v1;
    Vector vp1 = P - v1;
    C = edge1.cross(vp1);
    if (N.dot(C) < 0)  return false; // P is on the right side
 
    // edge 2
    Vector edge2 = v0 - v2;
    Vector vp2 = P - v2;
    C = edge2.cross(vp2);
    if (N.dot(C) < 0) return false; // P is on the right side;
 
    //return true; // this ray hits the triangle
    return t;
}


#endif /* triangle_h */
