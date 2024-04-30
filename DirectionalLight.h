// DirectionalLight.h
#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "Vector3.h"

class DirectionalLight {
public:
    Vector3 direction;
    Vector3 color;

    DirectionalLight(const Vector3& direction, const Vector3& color)
        : direction(direction.normalize()), color(color) {}
};

#endif // DIRECTIONAL_LIGHT_H
