#pragma once

#include "IsometricEngine.hpp"
#include "Vector3D.hpp"
#include <vector>
#include <string>

namespace IsometricMUD {

/**
 * @brief Tile data for the editor
 */
struct TileData {
    Vector3D position;
    int tileType;
    std::string scriptName;
};

/**
 * @brief Tile editor for creating game levels
 */
class TileEditor {
public:
    TileEditor();
    ~TileEditor();

    /**
     * @brief Place a tile at position
     */
    void placeTile(const Vector3D& position, int tileType);

    /**
     * @brief Remove a tile at position
     */
    void removeTile(const Vector3D& position);

    /**
     * @brief Get tile at position
     */
    TileData* getTile(const Vector3D& position);

    /**
     * @brief Get all tiles
     */
    const std::vector<TileData>& getTiles() const { return tiles; }

    /**
     * @brief Save level to file
     */
    bool saveLevel(const std::string& filename);

    /**
     * @brief Load level from file
     */
    bool loadLevel(const std::string& filename);

    /**
     * @brief Clear all tiles
     */
    void clear();

private:
    std::vector<TileData> tiles;
};

} // namespace IsometricMUD
