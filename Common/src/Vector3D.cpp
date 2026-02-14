#include "Vector3D.hpp"
#include <cmath>

namespace IsometricMUD {

Vector3D::Vector3D() : x(0), y(0), z(0) {}

Vector3D::Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3D Vector3D::operator+(const Vector3D& other) const {
    return Vector3D(x + other.x, y + other.y, z + other.z);
}

Vector3D Vector3D::operator-(const Vector3D& other) const {
    return Vector3D(x - other.x, y - other.y, z - other.z);
}

Vector3D Vector3D::operator*(float scalar) const {
    return Vector3D(x * scalar, y * scalar, z * scalar);
}

bool Vector3D::operator==(const Vector3D& other) const {
    const float epsilon = 0.0001f;
    return std::abs(x - other.x) < epsilon &&
           std::abs(y - other.y) < epsilon &&
           std::abs(z - other.z) < epsilon;
}

void Vector3D::toIsometric(float& screenX, float& screenY) const {
    // Standard isometric projection formulas
    // x and y determine the tile position, z determines height
    screenX = (x - y) * 32.0f;  // 32 is tile width/2
    screenY = (x + y) * 16.0f - z * 24.0f;  // 16 is tile height/2, z affects vertical position
}

float Vector3D::distance(const Vector3D& other) const {
    float dx = x - other.x;
    float dy = y - other.y;
    float dz = z - other.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

} // namespace IsometricMUD
