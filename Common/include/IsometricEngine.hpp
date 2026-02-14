#pragma once

#include <SFML/Graphics.hpp>
#include "Vector3D.hpp"
#include <memory>
#include <vector>

namespace IsometricMUD {

/**
 * @brief Core isometric rendering engine
 */
class IsometricEngine {
public:
    IsometricEngine();
    ~IsometricEngine();

    /**
     * @brief Initialize the engine with window dimensions
     */
    bool initialize(int windowWidth, int windowHeight);

    /**
     * @brief Render a tile at a given 3D position
     */
    void renderTile(sf::RenderWindow& window, const Vector3D& position, const sf::Color& color);

    /**
     * @brief Set camera position for viewing
     */
    void setCameraPosition(const Vector3D& position);

    /**
     * @brief Get camera position
     */
    Vector3D getCameraPosition() const;

    /**
     * @brief Convert world coordinates to screen coordinates
     */
    sf::Vector2f worldToScreen(const Vector3D& worldPos) const;

    /**
     * @brief Convert screen coordinates to approximate world coordinates
     */
    Vector3D screenToWorld(const sf::Vector2f& screenPos, float z = 0.0f) const;

private:
    Vector3D cameraPosition;
    int windowWidth;
    int windowHeight;
    sf::Vector2f offset; // Screen offset for centering
};

} // namespace IsometricMUD
