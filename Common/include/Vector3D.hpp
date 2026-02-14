#pragma once

namespace IsometricMUD {

/**
 * @brief 3D Vector class for representing positions in the game world
 * Supports 6 degrees of movement: North, South, East, West, Up, Down
 */
class Vector3D {
public:
    float x, y, z;

    Vector3D();
    Vector3D(float x, float y, float z);

    // Movement operations
    Vector3D operator+(const Vector3D& other) const;
    Vector3D operator-(const Vector3D& other) const;
    Vector3D operator*(float scalar) const;
    bool operator==(const Vector3D& other) const;

    // Convert to isometric screen coordinates
    void toIsometric(float& screenX, float& screenY) const;
    
    // Distance calculation
    float distance(const Vector3D& other) const;
};

} // namespace IsometricMUD
