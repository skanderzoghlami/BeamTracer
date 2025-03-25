#ifndef HITTABLE_H
#define HITTABLE_H
#include "ray.h"
#include "vec3.h"
#include "color.h"
class material ;

class hit_record{
    public:
        point3 p;
        double t;
        vec3 normal;
        bool front_face;
        shared_ptr<material> mat ;
        void set_front_face(const ray& r, const vec3& outward_normal){
            front_face = dot(r.get_direction(),outward_normal) < 0 ;
            normal = front_face ? outward_normal : -outward_normal;
        }
};




class hittable{
    public:
    virtual bool hit(const ray&r , interval ray_t , hit_record& rec) const = 0 ;
    virtual ~hittable() = default;
};

#endif // HITTABLE_H