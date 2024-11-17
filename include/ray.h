#ifndef RAY_H
#define RAY_H
#include "vec3.h"

class ray
{
public:
    ray() {}
    ray(
        const point3 &origin,
        const vec3 &direction) : origin(origin),
                                 direction(direction) {}
    point3 get_point(double t) const { return origin + t * direction; }
    const point3 &get_origin() const { return origin; }
    const vec3 &get_direction() const { return direction; }

private:
    point3 origin;
    vec3 direction;
};

#endif