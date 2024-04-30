// Camera.h
#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Ray.h"
#include <random>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Camera {
public:
    Vector3 origin;      
    Vector3 lowerLeftCorner; 
    Vector3 horizontal;  
    Vector3 vertical;    
    Vector3 u, v, w;     
    float lensRadius;

    Camera(Vector3 lookfrom, Vector3 lookat, Vector3 vup, float vfov, float aspect, float aperture = 0.0, float focusDist = 1.0) {
        lensRadius = aperture / 2;
        float theta = vfov * M_PI / 180;
        float halfHeight = tan(theta / 2);
        float halfWidth = aspect * halfHeight;
        origin = lookfrom;

        w = (lookfrom - lookat).normalize();
        u = vup.cross(w).normalize();
        v = w.cross(u);

        lowerLeftCorner = origin - halfWidth * focusDist * u - halfHeight * focusDist * v - focusDist * w;
        horizontal = 2 * halfWidth * focusDist * u;
        vertical = 2 * halfHeight * focusDist * v;
    }

    float randomFloat() {
        static std::uniform_real_distribution<float> distribution(0.0, 1.0);
        static std::mt19937 generator;
        return distribution(generator);
    }

    
    Ray getRay(float s, float t) {
        Vector3 rd = lensRadius * randomInUnitDisk();
        Vector3 offset = u * rd.x + v * rd.y;
        return Ray(origin + offset, lowerLeftCorner + s * horizontal + t * vertical - origin - offset);
    }

private:
    Vector3 randomInUnitDisk() {
        Vector3 p;
        do {
            p = 2.0 * Vector3(randomFloat(), randomFloat(), 0) - Vector3(1, 1, 0);
        } while (p.dot(p) >= 1.0);
        return p;
    }
};

#endif // CAMERA_H
