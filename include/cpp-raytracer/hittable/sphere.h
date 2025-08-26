#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
    point3 center;
    double radius;

  public:
    sphere(const point3 &center, double radius) : center{center}, radius{std::fmax(0.0, radius)} {} 

    bool hit(const ray &r, interval ray_t, hit_record &rec) const {
        vec3 oc = center - r.origin();

        auto a = dot(r.direction(), r.direction());
        auto h = dot(r.direction(), oc);
        auto c = dot(oc, oc) - radius * radius;
        
        auto discriminant = h * h - a * c;
        
        if (discriminant < 0)
            return false;
        
        auto sqrtd = std::sqrt(discriminant);
        
        auto root = (h - sqrtd) / a;
        if (!ray_t.surrounds(root)){
            root = (h + sqrtd) / a;
            if (!ray_t.surrounds(root)){
                return false;
            }
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 normal = (rec.p - center) / radius;
        rec.set_face_normal(r, normal);

        return true;
    }
};

#endif
