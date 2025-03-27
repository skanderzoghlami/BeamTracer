#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class material
{
public:
    virtual ~material() = default;
    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const
    {
        return false;
    }
};

class lambertian : public material
{
public:
    lambertian(const color &a) : albedo(a) {};
    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override
    {
        auto scatter_direction = rec.normal + random_unit_vector();
        if (scatter_direction.non_zero())
            scatter_direction = random_unit_vector();
        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    };

private:
    color albedo;
};

class metal : public material
{
public:
    metal(const color &albedo , double fuzz) : albedo(albedo) , fuzz(fuzz < 1 ? fuzz : 1) {}

    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered)
        const override
    {
        vec3 reflected = reflect(r_in.get_direction(), rec.normal);
        reflected = unit_vector(reflected)  + (fuzz * random_unit_vector());
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return (dot(scattered.get_direction(), rec.normal) > 0);
    }

private:
    color albedo;
    double fuzz;
};


class dielectric : public material {

public: 
    dielectric(double refraction_index) : refraction_index(refraction_index) {}
    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override
    {
        // In case of a refracted ray being redirected to another medium
        double ri = rec.front_face ? (1.0/ refraction_index) : refraction_index;
        attenuation = color(1.0,1.0,1.0);

        vec3 unit_direction = unit_vector(r_in.get_direction());
        vec3 refracted = refract(unit_direction, rec.normal, ri);
        scattered = ray(rec.p , refracted) ; 
        return true;
    }

private : 
    double refraction_index;
};


#endif // MATERIAL_H