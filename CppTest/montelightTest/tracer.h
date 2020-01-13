//
//  tracer.h
//  CppTest
//
//  Created by Wei Li on 2019-12-18.
//  Copyright © 2019 Victor Li. All rights reserved.
//



#ifndef tracer_h
#define tracer_h
#include "ray.h"
#include "shape.h"
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

#ifdef __APPLE__
#else
#define drand48() ((double)rand()/RAND_MAX)
//#define M_PI 3.14159265358979323846
//#define M_1_PI 0.318309886183790671538
#endif

class Tracer {
public:
    std::vector<Shape *> scene;
    
    Tracer(const std::vector<Shape *> &scene_) : scene(scene_){}
    std::pair<Shape *, double> getIntersection(const Ray &r) const;
    Vector getRadiance(const Ray &r, int depth);
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



#define MAX_DEPTH 3
bool SAMPLING_LIGHT = true;
Vector Tracer::getRadiance(const Ray &r, int depth) {
    if (depth > MAX_DEPTH) return Vector();
    
    auto result = getIntersection(r);
    // hit object
    Shape *hitObj = result.first;
    // distance to intersection
    double t = result.second;
    // hit point
    Vector hitPos = r.origin + r.direction * t;
    // if miss, return black
    if (hitObj == nullptr) {return Vector();}

    Vector norm = hitObj->getNormal(hitPos);
    // orienting normal, for glass surface
    if (norm.dot(r.direction) > 0) norm = norm * -1;
    
    // TODO: R.R.
    
    // Work out the contribution from directly sampling the emitters
    if (hitObj->material == LIGHT)
        return hitObj->color;
    
    Vector lightSampling = Vector(0);
    if (SAMPLING_LIGHT && hitObj->material == DIFF) {
        
        // sample ALL lights
        for (Shape *light : scene) {
            // Skip any objects that don't emit light
            if (light->emit.max() == 0) continue;
            // sampling area light
            Vector lightSamplePos = light->randomPoint();//Vector lightPos;
            Vector lightDirection = (lightSamplePos - hitPos).norm();
            Ray rayToLight = Ray(hitPos, lightDirection);
            
            auto lightHit = getIntersection(rayToLight);
            
            // Check for occlusion with shadow ray
            if (light == lightHit.first) {
                double wi = lightDirection.dot(norm);
                if (wi > 0) {
                    double radius = .1 ; // vip!
                    double sin_a_max = radius / (lightSamplePos-hitPos).length();
                    double cos_a_max = sqrt(1 - sin_a_max*sin_a_max);
                    // https://schuttejoe.github.io/post/arealightsampling/
                    double omega = 2*M_PI*(1-cos_a_max); // solid angle
                    double brdf = M_1_PI;
                    lightSampling += light->emit * wi * omega * brdf;
                }
            }
//            else{ //there are objects in the way, AKA it's in the shadow
//                return Vector(1,0,0);
//            }
        }
    }
    
    // Work out contribution from reflected light
    // Diffuse reflection condition:
    // Create orthogonal coordinate system defined by (x=u, y=v, z=norm)
    double angle = 2 * M_PI * drand48(); // [0,2PI]
    double dist_cen = sqrt(drand48());
    Vector w = norm;
    Vector u = (fabs(w.x) > 0.1 ? Vector(0, 1, 0) : Vector(1, 0, 0)).cross(w).norm(); // u perpendicular to w
    Vector v = w.cross(u); // v perpendicular to u and w
    
    // d is random reflection ray
    Vector d = Vector();
    
    if(hitObj->material == DIFF)
        d = (u * cos(angle) * dist_cen + v * sin(angle) * dist_cen + w * sqrt(1 - dist_cen * dist_cen)).norm();
    if(hitObj->material == REFL)
        // reflection
        d = r.direction - norm * 2 * norm.dot(r.direction);
    
    // recursive call for bouncing light
    Vector reflected = getRadiance(Ray(hitPos, d), depth + 1);
    
    if (!SAMPLING_LIGHT || depth == 0) {
        // only count emit light at the first depth!
        return hitObj->color * (lightSampling + reflected) + hitObj->emit;
    }

    return hitObj->color * (lightSampling + reflected);// + hitObj->emit;

    
    
//            return hitObj->emit; // just light
//            return hitObj->emit + hitObj->color;
//            return lightSampling;
//            return lightSampling + reflected;
//            return lightSampling + reflected + hitObj->emit;
//            return (lightSampling + reflected) * hitObj->color + hitObj->emit;
}
#endif /* tracer_h */
