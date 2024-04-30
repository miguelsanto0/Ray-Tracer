// Material.h
#ifndef MATERIAL_H
#define MATERIAL_H

#include "Vector3.h"

class Material {
public:
    float ka; 
    float kd; 
    float ks; 
    float kgls;
    Vector3 od; 
    Vector3 os; 

    Material(float ka, float kd, float ks, float kgls, const Vector3& od, const Vector3& os)
        : ka(ka), kd(kd), ks(ks), kgls(kgls), od(od), os(os) {}
};

#endif
