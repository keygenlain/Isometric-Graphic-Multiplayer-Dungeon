#pragma once

#include "Vector3D.hpp"

namespace IsometricMUD {

/**
 * @brief Enumeration for the 6 degrees of movement
 */
enum class Direction {
    NORTH,      // +Y
    SOUTH,      // -Y
    EAST,       // +X
    WEST,       // -X
    UP,         // +Z
    DOWN        // -Z
};

/**
 * @brief Movement system for handling 6-directional movement
 */
class Movement {
public:
    /**
     * @brief Get the direction vector for a given direction
     * @param dir The direction to get the vector for
     * @return Vector3D representing unit movement in that direction
     */
    static Vector3D getDirectionVector(Direction dir);

    /**
     * @brief Apply movement in a direction to a position
     * @param position Current position
     * @param dir Direction to move
     * @param distance Distance to move (default 1.0)
     * @return New position after movement
     */
    static Vector3D applyMovement(const Vector3D& position, Direction dir, float distance = 1.0f);

    /**
     * @brief Check if movement is valid (e.g., not blocked by terrain)
     * @param from Starting position
     * @param to Ending position
     * @return True if movement is valid
     */
    static bool isValidMovement(const Vector3D& from, const Vector3D& to);
};

} // namespace IsometricMUD
