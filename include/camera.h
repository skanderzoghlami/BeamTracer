#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "material.h"

#include <fstream>
class camera {

public:
double aspect_ratio = 1.0;  // Ratio of image width over height
int    image_width  = 100;  // Rendered image width in pixel count
int samples_per_pixel = 10;
int max_depth = 10;

double vfov = 90.0;
point3 lookfrom = point3(0,0,0) ;
point3 lookat =  point3(0,0,-1)  ;
vec3 vup = vec3(0,1,0); 

void render(const hittable& world){
    initialize();
    std::ofstream image ;
    image.open("image.ppm");
    image << "P3\n" << image_width << " " << image_height << "\n255\n";
    for(int j = 0 ; j< image_height ; ++j)
        for(int i=0 ; i< image_width ; ++i)
            {
                color pixel_color(0,0,0);
                for (int sample = 0 ;  sample < samples_per_pixel ; ++sample){
                    ray r = get_ray(i,j);
                    pixel_color += ray_color(r,max_depth,world);
                }
                write_color(image,pixel_color * pixel_sample_scale);
            }
    image.close();
    }
private :
int    image_height;   // Rendered image height
point3 center;         // Camera center
point3 pixel00_loc;    // Location of pixel 0, 0
vec3   pixel_delta_u;  // Offset to pixel to the right
vec3   pixel_delta_v;  // Offset to pixel below
double pixel_sample_scale ;
vec3 u , v , w ;

void initialize() {
    image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;
    pixel_sample_scale = 1.0 / samples_per_pixel;
    center = lookfrom;

    // Determine viewport dimensions.
    auto focal_length = (lookfrom - lookat).length();

    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup,w));
    v = cross(w,u);



    auto theta = degrees_to_radians(vfov);
    auto h = tan(theta/2 );
    auto viewport_height = 2.0 * h * focal_length;
    auto viewport_width = viewport_height * (double(image_width)/image_height);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = viewport_width *  u ;
    auto viewport_v = viewport_height * -v;

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left =
        center - focal_length * w - viewport_u/2 - viewport_v/2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}
color ray_color(const ray& r , int depth, const hittable& world ){

    hit_record rec;
    if(depth <= 0)
        return color(0,0,0);
    if(world.hit(r,interval(0.001,infinity),rec)){
        ray scattered;
        color attenuation;
        if (rec.mat->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, depth-1, world);
        return color(0,0,0);
    }
    vec3 unit_direction = unit_vector(r.get_direction());
    double alpha= 0.5*(unit_direction.y() + 1.0);
    return (1.0 - alpha) * color(1.0,1.0,1.0) + alpha * color(0.5,0.7,1.0);
}
ray get_ray(int i , int k) const {
    auto offset = sample_square();
    auto pixel_sample = pixel00_loc + (i + offset.x()) * pixel_delta_u + (k + offset.y()) * pixel_delta_v;
    return ray(center, pixel_sample - center);
}
vec3 sample_square() const {
    return vec3(random_double() - 0.5  , random_double() - 0.5 , 0);
}
};






#endif // CAMERA_H