#include "cpp-raytracer/common.h"

#include "cpp-raytracer/hittable.h"
#include "cpp-raytracer/hittable_list.h"
#include "cpp-raytracer/sphere.h"

color background_color(const ray &r){
    double y = r.direction().y();
    double a = 0.5 * (y + 1);
    return a * color(0.5, 0.7, 1.0) + (1 - a) * color(1.0, 1.0, 1.0);
}

color ray_color(const ray &r, const hittable &world){
    hit_record rec;
    if (!world.hit(r, interval(0, infinity), rec)) return background_color(r);

    return (rec.normal + vec3(1, 1, 1)) * 0.5;
}

int main() {

    // Image
    double aspect_ratio = 16.0 / 9.0;
    
    int image_width = 400;
    int image_height = int(image_width / aspect_ratio);
    
    if(image_height < 1) image_height = 1;
    
    // Camera
    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * (double(image_width) / image_height);

    point3 camera_origin(0, 0, 0);

    double pixel_size_x = viewport_width / image_width;
    double pixel_size_y = viewport_height / image_height;

    vec3 viewport_ux(pixel_size_x, 0, 0);
    vec3 viewport_uy(0, -pixel_size_y, 0); 

    point3 viewport_top_left = camera_origin - vec3(0, 0, focal_length) - viewport_ux * image_width / 2 - viewport_uy * image_height / 2;

    point3 pixel_00 = viewport_top_left + 0.5 * (viewport_ux + viewport_uy);

    // World

    hittable_list world;

    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int j = 0; j < image_height; ++j){
        std::clog << "\rScanlines Remaining: " << (image_height - j) << "   "<< std::flush;
        for(int i = 0; i < image_width; ++i){
            point3 pixel = pixel_00 + i * viewport_ux + j * viewport_uy;
            vec3 ray_dir = unit_vector(pixel - camera_origin);

            
            ray r(camera_origin, ray_dir); 
            
            color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }    
    }
    std::clog << "\rDone!                                      \n" << std::flush;
}