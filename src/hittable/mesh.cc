

#include <array>

#include "cpp-raytracer/common.h"

#include "cpp-raytracer/hittable/mesh.h"

static bool intersect_triangle(const triangle &t, const ray &r, interval ray_t, hit_record &rec){

}

bool mesh::hit(const ray &r, interval ray_t, hit_record &rec) const {
    for(const triangle &t : triangles){
        if(intersect_triangle(t, r, ray_t, rec)) return true;
    }

    return false;
}


static inline void add_quad_face(
    std::vector<triangle> &triangles, 
    const point3 &a, 
    const point3 &b, 
    const point3 &c, 
    const point3 &d){
    triangles.emplace_back(a, b, c);
    triangles.emplace_back(b, c, d);
}


std::vector<triangle> cube::generate_mesh(point3 origin, vec3 side_lengths){
    std::array<vec3, 8> points;

    for(int i = 0; i < 8; ++i){
        int x = (i     ) & 1;
        int y = (i >> 1) & 1;
        int z = (i >> 2) & 1;
        points[i] = point3{
            origin.x() + x * side_lengths.x(),
            origin.y() + y * side_lengths.y(),
            origin.z() + z * side_lengths.z()
        };
    }

    std::vector<triangle> out;
    add_quad_face(out, points[0], points[1], points[2], points[3]);
    add_quad_face(out, points[2], points[3], points[6], points[7]);
    add_quad_face(out, points[4], points[0], points[6], points[2]);
    add_quad_face(out, points[1], points[5], points[3], points[7]);
    add_quad_face(out, points[5], points[4], points[7], points[6]);
    add_quad_face(out, points[1], points[0], points[5], points[4]);

    return std::move(out);
}
