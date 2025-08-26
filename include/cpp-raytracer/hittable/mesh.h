#ifndef MESH_H
#define MESH_H

#include <vector>

#include "hittable.h"

using triangle = std::array<point3, 3>;

class mesh : public hittable {
    std::vector<triangle> triangles;

  public:

    mesh(std::vector<triangle> triangles) : triangles{std::move(triangles)} {}; 

    bool hit(const ray &r, interval ray_t, hit_record &rec) const;
};

class cube : public mesh {
    static std::vector<triangle> generate_mesh(point3 origin, vec3 side_lengths);
  public: 
    cube(point3 origin, vec3 side_lengths) : mesh{generate_mesh(origin, side_lengths)} {};
};

#endif
