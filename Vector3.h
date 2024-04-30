// Vector3.h
#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
class Vector3 {
public:
    float x, y, z;

    // Constructors
    Vector3() : x(0), y(0), z(0) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vector3 operator+(const Vector3& v) const {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }

    // This is the vector subtraction method
    Vector3 operator-(const Vector3& v) const {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }

    // This is the scalar multiplication method
    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    // This is the scalar division method
    Vector3 operator/(float scalar) const {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    // This is the dot product method
    float dot(const Vector3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    // This is the cross product
    Vector3 cross(const Vector3& v) const {
        return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }

    // This is the normalize method
    Vector3 normalize() const {
        float length = sqrt(x * x + y * y + z * z);
        if (length > 0) {
            float invLen = 1.0f / length;
            return Vector3(x * invLen, y * invLen, z * invLen);
        }
        return *this; 
    }

    float length() const {
        return sqrt(x * x + y * y + z * z);
    }

    float lengthSquared() const {
        return x * x + y * y + z * z;
    }
};

inline Vector3 operator*(float scalar, const Vector3& v) {
    return Vector3(scalar * v.x, scalar * v.y, scalar * v.z);
}

#endif // VECTOR3_H
