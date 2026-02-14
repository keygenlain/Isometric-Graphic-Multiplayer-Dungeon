#include "Movement.hpp"

namespace IsometricMUD {

Vector3D Movement::getDirectionVector(Direction dir) {
    switch (dir) {
        case Direction::NORTH:
            return Vector3D(0, 1, 0);
        case Direction::SOUTH:
            return Vector3D(0, -1, 0);
        case Direction::EAST:
            return Vector3D(1, 0, 0);
        case Direction::WEST:
            return Vector3D(-1, 0, 0);
        case Direction::UP:
            return Vector3D(0, 0, 1);
        case Direction::DOWN:
            return Vector3D(0, 0, -1);
        default:
            return Vector3D(0, 0, 0);
    }
}

Vector3D Movement::applyMovement(const Vector3D& position, Direction dir, float distance) {
    Vector3D dirVector = getDirectionVector(dir);
    return position + (dirVector * distance);
}

bool Movement::isValidMovement(const Vector3D& from, const Vector3D& to) {
    // Basic validation - can be extended with terrain checking
    // For now, just check that the movement isn't too large
    float dist = from.distance(to);
    return dist > 0 && dist <= 10.0f; // Max movement per step
}

} // namespace IsometricMUD
