#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"
#include "ray.h"

class sphere: public hittable{
    public:
    sphere(const point3& c , double r) : center(c) , radius(std::fmax(0,r)) {}
    bool hit(const ray&r , double t_min , double t_max , hit_record& rec) const override{
        vec3 oc = center - r.get_origin();
        auto h = dot(r.get_direction(),oc);
        auto a = dot(r.get_direction(),r.get_direction());
        auto c = dot(oc,oc) - radius * radius ;
    
        auto discriminant = h*h - a*c;
        if(discriminant < 0 )
            return false ;
        auto root = h - sqrt(discriminant)/ ( a);
        if (root < t_min || root > t_max)
            {
                root = h + sqrt(discriminant)/a ;
                if (root < t_min || root > t_max)
                    return false ;
            }
            rec.t = root ;
            rec.p = r.at(root);
            vec3 outward_normal = rec.p - center;
            /* Convention, normals are always opposite to ray direction */
            rec.set_front_face(r,outward_normal);
            return true ;
    }
    private:
    point3 center ;
    double radius ;
};
#endif // SPHERE_H