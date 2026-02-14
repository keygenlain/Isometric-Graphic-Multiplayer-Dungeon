#pragma once

#include <SFML/Graphics.hpp>
#include "IsometricEngine.hpp"
#include "TileEditor.hpp"
#include "ScriptEngine.hpp"
#include "EntityManager.hpp"
#include "UIPanel.hpp"
#include <memory>

namespace IsometricMUD {

/**
 * @brief Main editor application - Construction Set
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
    void handleTileMode(sf::Event& event);
    void handleEntityMode(sf::Event& event);
    void handleScriptMode(sf::Event& event);
    
    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<IsometricEngine> engine;
    std::unique_ptr<TileEditor> tileEditor;
    std::unique_ptr<ScriptEngine> scriptEngine;
    std::unique_ptr<EntityManager> entityManager;
    
    // UI Panels
    std::unique_ptr<ToolbarPanel> toolbar;
    std::unique_ptr<ObjectBrowserPanel> objectBrowser;
    std::unique_ptr<PropertyEditorPanel> propertyEditor;
    std::unique_ptr<ScriptEditorPanel> scriptEditor;
    
    bool running;
    EditorMode currentMode;
    int currentTileType;
    int currentLayer;
    sf::Vector2i mousePos;
    Vector3D cursorPosition;
    Entity* selectedEntity;
};

} // namespace IsometricMUD
