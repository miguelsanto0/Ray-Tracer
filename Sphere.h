// Sphere.h
#ifndef SPHERE_H
#define SPHERE_H

#include "Vector3.h"
#include "Material.h"
#include "Ray.h"

class Sphere {
public:
    Vector3 center; 
    float radius;   
    Material material;
    
    // Constructors
    Sphere(const Vector3& center, float radius, const Material& material)
        : center(center), radius(radius), material(material) {}
    
    bool intersect(const Ray& ray, float t_min, float& t_hit, float t_max) const {
        Vector3 oc = ray.origin - center;
        float a = ray.direction.dot(ray.direction);
        float half_b = oc.dot(ray.direction);
        float c = oc.dot(oc) - radius * radius;
        float discriminant = half_b * half_b - a * c;

        if (discriminant > 0) {
            float sqrtD = sqrt(discriminant);

            float root = (-half_b - sqrtD) / a;
            if (root < t_min || root > t_max) {
                root = (-half_b + sqrtD) / a;
                if (root < t_min || root > t_max)
                    return false;
            }

            t_hit = root;
            return true;
        }

        return false; 
    }

};

#endif // SPHERE_H
