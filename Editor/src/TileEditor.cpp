#include "TileEditor.hpp"
#include <fstream>
#include <iostream>

namespace IsometricMUD {

TileEditor::TileEditor() {
}

TileEditor::~TileEditor() {
}

void TileEditor::placeTile(const Vector3D& position, int tileType) {
    // Check if tile already exists at position
    for (auto& tile : tiles) {
        if (tile.position == position) {
            tile.tileType = tileType;
            return;
        }
    }
    
    // Add new tile
    TileData tile;
    tile.position = position;
    tile.tileType = tileType;
    tiles.push_back(tile);
}

void TileEditor::removeTile(const Vector3D& position) {
    tiles.erase(
        std::remove_if(tiles.begin(), tiles.end(),
            [&position](const TileData& tile) {
                return tile.position == position;
            }),
        tiles.end()
    );
}

TileData* TileEditor::getTile(const Vector3D& position) {
    for (auto& tile : tiles) {
        if (tile.position == position) {
            return &tile;
        }
    }
    return nullptr;
}

bool TileEditor::saveLevel(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to save level: " << filename << std::endl;
        return false;
    }
    
    // Write number of tiles
    size_t numTiles = tiles.size();
    file.write(reinterpret_cast<const char*>(&numTiles), sizeof(numTiles));
    
    // Write each tile
    for (const auto& tile : tiles) {
        file.write(reinterpret_cast<const char*>(&tile.position.x), sizeof(float));
        file.write(reinterpret_cast<const char*>(&tile.position.y), sizeof(float));
        file.write(reinterpret_cast<const char*>(&tile.position.z), sizeof(float));
        file.write(reinterpret_cast<const char*>(&tile.tileType), sizeof(int));
        
        size_t nameLen = tile.scriptName.length();
        file.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
        file.write(tile.scriptName.c_str(), nameLen);
    }
    
    file.close();
    std::cout << "Level saved: " << filename << " (" << numTiles << " tiles)" << std::endl;
    return true;
}

bool TileEditor::loadLevel(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to load level: " << filename << std::endl;
        return false;
    }
    
    clear();
    
    // Read number of tiles
    size_t numTiles;
    file.read(reinterpret_cast<char*>(&numTiles), sizeof(numTiles));
    
    // Read each tile
    for (size_t i = 0; i < numTiles; i++) {
        TileData tile;
        file.read(reinterpret_cast<char*>(&tile.position.x), sizeof(float));
        file.read(reinterpret_cast<char*>(&tile.position.y), sizeof(float));
        file.read(reinterpret_cast<char*>(&tile.position.z), sizeof(float));
        file.read(reinterpret_cast<char*>(&tile.tileType), sizeof(int));
        
        size_t nameLen;
        file.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
        tile.scriptName.resize(nameLen);
        file.read(&tile.scriptName[0], nameLen);
        
        tiles.push_back(tile);
    }
    
    file.close();
    std::cout << "Level loaded: " << filename << " (" << numTiles << " tiles)" << std::endl;
    return true;
}

void TileEditor::clear() {
    tiles.clear();
}

} // namespace IsometricMUD
