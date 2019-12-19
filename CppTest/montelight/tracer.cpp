//
//  tracer.cpp
//  montelight
//
//  Created by Wei Li on 2019-12-14.
//  Copyright © 2019 Victor Li. All rights reserved.
//

//#include <stdio.h>
#include "tracer.h"
#include <random>

// Globals
bool EMITTER_SAMPLING = true;
//bool EMITTER_SAMPLING = false;

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


Vector Tracer::getRadiance(const Ray &r, int depth) {
  // Work out what (if anything) was hit
  auto result = getIntersection(r);
  Shape *hitObj = result.first;
    
  // Russian Roulette sampling based on reflectance of material
//  double U = drand48();
//  if (depth > 4 && (depth > 20 || U > hitObj->color.max())) {
//    return Vector();
//  }
    if (depth > 5) {
        return Vector();
    }
    
  Vector hitPos = r.origin + r.direction * result.second;
  Vector norm = hitObj->getNormal(hitPos);
    
    
    
  // Orient the normal according to how the ray struck the object
  if (norm.dot(r.direction) > 0) {
    norm = norm * -1;
  }
    
    
    
  // Work out the contribution from directly sampling the emitters
  Vector lightSampling;
  if (EMITTER_SAMPLING) {
    for (Shape *light : scene) {
      // Skip any objects that don't emit light
      if (light->emit.max() == 0) continue;
      Vector lightPos = light->randomPoint();
      Vector lightDirection = (lightPos - hitPos).norm();
      Ray rayToLight = Ray(hitPos, lightDirection);
      auto lightHit = getIntersection(rayToLight);
      if (light == lightHit.first) {
        double wi = lightDirection.dot(norm);
        if (wi > 0) {
          double srad = 1.5;
          //double srad = 600;
          double cos_a_max = sqrt(1-srad*srad/(hitPos - lightPos).dot(hitPos - lightPos));
          double omega = 2*M_PI*(1-cos_a_max);
          lightSampling += light->emit * wi * omega * M_1_PI;
        }
      }
    }
  }
    
  // Work out contribution from reflected light
  // Diffuse reflection condition:
  // Create orthogonal coordinate system defined by (x=u, y=v, z=norm)
  double angle = 2 * M_PI * drand48();
  double dist_cen = sqrt(drand48());
  Vector u;
  if (fabs(norm.x) > 0.1) {
    u = Vector(0, 1, 0);
  } else {
    u = Vector(1, 0, 0);
  }
  u = u.cross(norm).norm();
  Vector v = norm.cross(u);
    
  // Direction of reflection
  Vector d = (u * cos(angle) * dist_cen + v * sin(angle) * dist_cen + norm * sqrt(1 - dist_cen * dist_cen)).norm();

  // Recurse
  Vector reflected = getRadiance(Ray(hitPos, d), depth + 1);
  
    
//  if (!EMITTER_SAMPLING || depth == 0) {
//    return hitObj->color * lightSampling + hitObj->color * reflected +  hitObj->emit;
//  }
//  return hitObj->color * lightSampling + hitObj->color * reflected;

    
    
    
    
    
    
    
//    return hitObj->emit; // just light
//    return hitObj->emit + hitObj->color;
//    return lightSampling;
//    return lightSampling + reflected;
//    return lightSampling + reflected + hitObj->emit;
    return (lightSampling + reflected) * hitObj->color + hitObj->emit;
//    return reflected; // not working
}
