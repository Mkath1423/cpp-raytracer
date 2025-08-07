#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    vec3 orig, dir;
  
  public:
    ray(vec3 origin, vec3 direction) : orig{origin}, dir{direction} {}
    
    const point3 &origin() const { return orig;}
    const vec3 &direction() const { return dir;}

    point3 at(double t) const { return orig + t * dir; };
    
};

#endif
