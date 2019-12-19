#ifndef ray_h
#define ray_h
#include "vector.h"
class Ray {
    /*
        +-->
        o--d
    */
public:
    Vector origin;
    Vector direction;
    Ray(const Vector& o_, const Vector& d_) : origin(o_), direction(d_) {}
};

#endif /* ray_h */