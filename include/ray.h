#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include "color.h"


class ray{

    public: 
        
        ray() {}
        ray(const point3& origin, const point3& direction) : orig(origin), dir(direction) {}

        point3 get_origin() const {return orig;}
        vec3 get_direction() const {return dir;}

        point3 at(double t) const{
            return orig + t*dir;
        }
    private:
        point3 orig ;
        vec3 dir;
};



#endif