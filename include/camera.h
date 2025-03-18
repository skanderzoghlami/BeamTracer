#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include <fstream>
class camera {

public:
double aspect_ratio = 1.0;  // Ratio of image width over height
int    image_width  = 100;  // Rendered image width in pixel count
void render(const hittable& world){
    initialize();
    std::ofstream image ;
    image.open("image.ppm");
    image << "P3\n" << image_width << " " << image_height << "\n255\n";
    for(int j = 0 ; j< image_height ; ++j)
        for(int i=0 ; i< image_width ; ++i)
            {
                point3 pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                vec3 ray_direction = pixel_center - center;
                ray r(center,ray_direction);
                color p_color = ray_color(r,world);
                write_color(image,p_color);
            }
    image.close();
    }
private :
int    image_height;   // Rendered image height
point3 center;         // Camera center
point3 pixel00_loc;    // Location of pixel 0, 0
vec3   pixel_delta_u;  // Offset to pixel to the right
vec3   pixel_delta_v;  // Offset to pixel below

void initialize() {
    image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    center = point3(0, 0, 0);

    // Determine viewport dimensions.
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left =
        center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}
color ray_color(const ray& r , const hittable& world ){

    hit_record rec;
    if(world.hit(r,interval(0,infinity),rec)){
        return 0.5 * (rec.normal + color(1,1,1));
    }
    vec3 unit_direction = unit_vector(r.get_direction());
    double alpha= 0.5*(unit_direction.y() + 1.0);
    return (1.0 - alpha) * color(1.0,1.0,1.0) + alpha * color(0.5,0.7,1.0);
}

};






#endif // CAMERA_H