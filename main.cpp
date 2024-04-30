#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include "Vector3.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"
#include "DirectionalLight.h"
#include "Ray.h"

Vector3 color(const Ray& r, const std::vector<Sphere>& spheres, const DirectionalLight& light, const Vector3& ambientLight) {
    float t_min = 0.001f;
    float t_max = std::numeric_limits<float>::max();
    Vector3 hitColor(0.2, 0.2, 0.2); 
    for (const auto& sphere : spheres) {
        float t_hit = std::numeric_limits<float>::max();
        if (sphere.intersect(r, t_min, t_hit, t_max)) {
            Vector3 N = (r.pointAtParameter(t_hit) - sphere.center).normalize();
            Vector3 L = light.direction.normalize();

            // This will the ambient method
            Vector3 ambient = ambientLight * sphere.material.ka;

            // This will be the diffuse method
            float diff = std::max(N.dot(L), 0.0f);
            Vector3 diffuse = sphere.material.od * (sphere.material.kd * diff);

            // This will be the Specular method
            Vector3 V = (r.origin - sphere.center).normalize();
            Vector3 R = (2 * N * (N.dot(L)) - L).normalize();
            float spec = std::pow(std::max(R.dot(V), 0.0f), sphere.material.kgls);
            Vector3 specular = sphere.material.os * (sphere.material.ks * spec);

            hitColor = ambient + diffuse + specular;
            return hitColor;
        }
    }

    return hitColor;
}

int main() {
    const int imageWidth = 400;
    const int imageHeight = 200;
    std::ofstream out("scene2.ppm");
    out << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    Vector3 lookfrom(0, 0, 1);
    Vector3 lookat(0, 0, 0);
    Vector3 vup(0, 1, 0);
    Camera cam(lookfrom, lookat, vup, 90, float(imageWidth) / imageHeight, 0.0, (lookfrom-lookat).length());

    DirectionalLight light(Vector3(1.0, 1.0, 1.0).normalize(), Vector3(1.0, 1.0, 1.0));
    Vector3 ambientLight(0.1, 0.1, 0.1);

    std::vector<Sphere> spheres;
    spheres.push_back(Sphere(Vector3(0.45, 0.0, -0.15), 0.15, Material(0.3, 0.8, 0.1, 4.0, Vector3(1.0, 1.0, 1.0), Vector3(1.0, 1.0, 1.0))));
    spheres.push_back(Sphere(Vector3(0.0, 0.0, -0.1), 0.2, Material(0.1, 0.6, 0.3, 32.0, Vector3(1.0, 0.0, 0.0), Vector3(1.0, 1.0, 1.0))));
    spheres.push_back(Sphere(Vector3(-0.6, 0.0, 0.0), 0.3, Material(0.1, 0.7, 0.2, 64.0, Vector3(0.0, 1.0, 0.0), Vector3(0.5, 1.0, 0.5))));
    spheres.push_back(Sphere(Vector3(0.0, -10000.5, 0.0), 10000.0, Material(0.1, 0.9, 0.0, 16.0, Vector3(0.0, 0.0, 1.0), Vector3(1.0, 1.0, 1.0)))); // Ground

    for (int j = imageHeight - 1; j >= 0; --j) {
        for (int i = 0; i < imageWidth; ++i) {
            float u = float(i) / (imageWidth - 1);
            float v = float(j) / (imageHeight - 1);
            Ray r = cam.getRay(u, v);
            Vector3 col = color(r, spheres, light, ambientLight);
            int ir = static_cast<int>(255.99 * col.x);
            int ig = static_cast<int>(255.99 * col.y);
            int ib = static_cast<int>(255.99 * col.z);
            out << ir << ' ' << ig << ' ' << ib << "\n";
        }
    }

    out.close();
    std::cout << "Scene render complete." << std::endl;
    return 0;
}
