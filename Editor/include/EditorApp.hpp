#pragma once

#include <SFML/Graphics.hpp>
#include "IsometricEngine.hpp"
#include "TileEditor.hpp"
#include "ScriptEngine.hpp"
#include <memory>

namespace IsometricMUD {

/**
 * @brief Main editor application
 */
class EditorApp {
public:
    EditorApp();
    ~EditorApp();

    /**
     * @brief Initialize the editor
     */
    bool initialize();

    /**
     * @brief Run the editor
     */
    void run();

private:
    void handleEvents();
    void update();
    void render();
    void renderUI();
    
    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<IsometricEngine> engine;
    std::unique_ptr<TileEditor> tileEditor;
    std::unique_ptr<ScriptEngine> scriptEngine;
    
    bool running;
    int currentTileType;
    int currentLayer;
    sf::Vector2i mousePos;
    Vector3D cursorPosition;
};

} // namespace IsometricMUD
