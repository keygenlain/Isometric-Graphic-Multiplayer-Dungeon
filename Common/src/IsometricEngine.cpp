#include "IsometricEngine.hpp"
#include <cmath>

namespace IsometricMUD {

IsometricEngine::IsometricEngine() 
    : cameraPosition(0, 0, 0), windowWidth(800), windowHeight(600) {
}

IsometricEngine::~IsometricEngine() {
}

bool IsometricEngine::initialize(int width, int height) {
    windowWidth = width;
    windowHeight = height;
    offset = sf::Vector2f(width / 2.0f, height / 2.0f);
    return true;
}

void IsometricEngine::renderTile(sf::RenderWindow& window, const Vector3D& position, const sf::Color& color) {
    // Calculate relative position from camera
    Vector3D relativePos = position - cameraPosition;
    
    // Convert to screen coordinates
    sf::Vector2f screenPos = worldToScreen(relativePos);
    
    // Create a diamond shape for the tile
    sf::ConvexShape tile(4);
    const float tileWidth = 64.0f;
    const float tileHeight = 32.0f;
    
    // Diamond shape vertices
    tile.setPoint(0, sf::Vector2f(screenPos.x, screenPos.y - tileHeight / 2));  // Top
    tile.setPoint(1, sf::Vector2f(screenPos.x + tileWidth / 2, screenPos.y));   // Right
    tile.setPoint(2, sf::Vector2f(screenPos.x, screenPos.y + tileHeight / 2));  // Bottom
    tile.setPoint(3, sf::Vector2f(screenPos.x - tileWidth / 2, screenPos.y));   // Left
    
    tile.setFillColor(color);
    tile.setOutlineColor(sf::Color::Black);
    tile.setOutlineThickness(1.0f);
    
    window.draw(tile);
}

void IsometricEngine::setCameraPosition(const Vector3D& position) {
    cameraPosition = position;
}

Vector3D IsometricEngine::getCameraPosition() const {
    return cameraPosition;
}

sf::Vector2f IsometricEngine::worldToScreen(const Vector3D& worldPos) const {
    float screenX, screenY;
    worldPos.toIsometric(screenX, screenY);
    return sf::Vector2f(screenX + offset.x, screenY + offset.y);
}

Vector3D IsometricEngine::screenToWorld(const sf::Vector2f& screenPos, float z) const {
    // Inverse isometric projection
    float adjustedX = screenPos.x - offset.x;
    float adjustedY = screenPos.y - offset.y + z * 24.0f;
    
    float worldX = (adjustedX / 32.0f + adjustedY / 16.0f) / 2.0f;
    float worldY = (adjustedY / 16.0f - adjustedX / 32.0f) / 2.0f;
    
    return Vector3D(worldX, worldY, z);
}

} // namespace IsometricMUD
