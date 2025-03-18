#include <rtutils.h>
#include <fstream>
#include <vector>

#include <hittable.h>
#include <sphere.h>
#include <hittable_list.h>


using namespace std;

double hit_sphere(const point3& center , const double& radius , const ray& r ){
    vec3 oc = center - r.get_origin();
    auto h = dot(r.get_direction(),oc);
    auto a = dot(r.get_direction(),r.get_direction());
    auto c = dot(oc,oc) - radius * radius ;

    auto discriminant = h*h - a*c;
    if(discriminant < 0 )
        return -1.0 ;
    return (h - sqrt(discriminant))/ ( a);
}




color ray_color(const ray& r , const hittable& world ){

    hit_record rec;
    if(world.hit(r,0,infinity,rec)){
        return 0.5 * (rec.normal + color(1,1,1));
    }
    vec3 unit_direction = unit_vector(r.get_direction());
    double alpha= 0.5*(unit_direction.y() + 1.0);
    return (1.0 - alpha) * color(1.0,1.0,1.0) + alpha * color(0.5,0.7,1.0);
}

void makeImage(){

    // World related stuff
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));


    // Output Image related stuff
    int image_width; 
    cout << "Give The Desired Image Width" << endl ;
    cin >> image_width ;
    auto aspect_ratio = 16.0 / 9.0;
    int image_height = int(image_width / aspect_ratio);
    image_height = image_height > 1 ? image_height : 1;
    cout << "Calculated Image Height from Aspect ratio = 16:9 is " << image_height << endl;
    cout << "Your Image will be of size " << image_width << "x" << image_height << endl;
    // Camera and Virtual Screen related stuff
    auto viewport_height= 2.0; 
    double viewport_width = viewport_height * (double(image_width) / image_height);
    double focal_length = 1.0;
    point3 camera_center(0,0,0);
    cout << "Finished Preparing the Camera and Virtual Screen, your viewport is :" << viewport_width << "x" << viewport_height << endl;
    cout << "Focal Length is " << focal_length << endl;
    cout << "Camera Center is at " << camera_center << endl;
    // Viewport Navigation Stuff
    vec3 viewport_u = vec3(viewport_width,0,0);
    vec3 viewport_v = vec3(0,-viewport_height,0);
    vec3 pixel_delta_u = viewport_u/ image_width ;
    vec3 pixel_delta_v = viewport_v / image_height;
    point3 upper_left_corner = camera_center - vec3(0,0,focal_length) - viewport_u / 2  - viewport_v /2 ;
    point3 first_pixel = upper_left_corner + 0.5* (pixel_delta_u + pixel_delta_v );
    cout << "Creating the Image" << endl;
    ofstream image ;
    image.open("image.ppm");
    image << "P3\n" << image_width << " " << image_height << "\n255\n";
    for(int j = 0 ; j< image_height ; ++j)
        for(int i=0 ; i< image_width ; ++i)
            {
                point3 pixel_center = first_pixel + (i * pixel_delta_u) + (j * pixel_delta_v);
                vec3 ray_direction = pixel_center - camera_center;
                ray r(camera_center,ray_direction);
                color p_color = ray_color(r,world);
                write_color(image,p_color);
            }
    image.close();
    cout << "Finished Creating the Image" << endl;
}


int main(int, char**){
   makeImage();
   return 0;
}
