#include "EditorApp.hpp"
#include <iostream>
#include <cmath>

namespace IsometricMUD {

EditorApp::EditorApp() 
    : running(false), currentMode(EditorMode::TILE), currentTileType(0), 
      currentLayer(0), cursorPosition(0, 0, 0), selectedEntity(nullptr) {
}

EditorApp::~EditorApp() {
}

bool EditorApp::initialize() {
    window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode(1600, 900),
        "Isometric MUD Construction Set"
    );
    window->setFramerateLimit(60);
    
    engine = std::make_unique<IsometricEngine>();
    engine->initialize(1600, 900);
    
    tileEditor = std::make_unique<TileEditor>();
    scriptEngine = std::make_unique<ScriptEngine>();
    entityManager = std::make_unique<EntityManager>();
    
    // Initialize UI panels
    toolbar = std::make_unique<ToolbarPanel>(0, 0, 1600, 60);
    objectBrowser = std::make_unique<ObjectBrowserPanel>(0, 60, 250, 840);
    propertyEditor = std::make_unique<PropertyEditorPanel>(1350, 60, 250, 840);
    scriptEditor = std::make_unique<ScriptEditorPanel>(400, 200, 800, 500);
    scriptEditor->setVisible(false); // Hidden by default
    
    // Set up callbacks
    toolbar->setOnModeChanged([this](EditorMode mode) {
        currentMode = mode;
        objectBrowser->setVisible(mode == EditorMode::ENTITY);
        scriptEditor->setVisible(mode == EditorMode::SCRIPT);
        std::cout << "Editor mode changed to: " << static_cast<int>(mode) << std::endl;
    });
    
    objectBrowser->setOnSelectionChanged([this](EntityType type) {
        std::cout << "Selected entity type for placement" << std::endl;
    });
    
    std::cout << "Construction Set initialized successfully" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  Mode Buttons: Click toolbar to switch between Tile/Entity/Script/Landscape modes" << std::endl;
    std::cout << "  Tile Mode: 1-5 to select tile type, Click to place, Right-click to remove" << std::endl;
    std::cout << "  Entity Mode: Select from browser, Click to place, Right-click to select" << std::endl;
    std::cout << "  Page Up/Down: Change layer (Z-level)" << std::endl;
    std::cout << "  Ctrl+S: Save level, Ctrl+L: Load level, Ctrl+N: New level" << std::endl;
    std::cout << "  Ctrl+E: Save entities, Ctrl+R: Load entities" << std::endl;
    std::cout << "  Delete: Remove selected entity" << std::endl;
    std::cout << "  ESC: Exit" << std::endl;
    return true;
}

void EditorApp::run() {
    running = true;
    
    while (running && window->isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void EditorApp::handleEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            running = false;
            window->close();
        }
        
        // Handle UI panel clicks first
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mouseClickPos(
                static_cast<float>(event.mouseButton.x),
                static_cast<float>(event.mouseButton.y)
            );
            
            toolbar->handleClick(mouseClickPos);
            if (objectBrowser->isVisible()) {
                objectBrowser->handleClick(mouseClickPos);
            }
            if (propertyEditor->isVisible()) {
                propertyEditor->handleClick(mouseClickPos);
            }
            if (scriptEditor->isVisible()) {
                scriptEditor->handleClick(mouseClickPos);
            }
        }
        
        // Handle mode-specific events
        switch (currentMode) {
            case EditorMode::TILE:
                handleTileMode(event);
                break;
            case EditorMode::ENTITY:
                handleEntityMode(event);
                break;
            case EditorMode::SCRIPT:
                handleScriptMode(event);
                break;
            case EditorMode::LANDSCAPE:
                // Landscape mode handling (future expansion)
                break;
        }
        
        // Global hotkeys
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Escape:
                    running = false;
                    break;
                case sf::Keyboard::PageUp:
                    currentLayer++;
                    cursorPosition.z = currentLayer;
                    std::cout << "Layer: " << currentLayer << std::endl;
                    break;
                case sf::Keyboard::PageDown:
                    currentLayer--;
                    cursorPosition.z = currentLayer;
                    std::cout << "Layer: " << currentLayer << std::endl;
                    break;
                case sf::Keyboard::S:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                        tileEditor->saveLevel("level.dat");
                        std::cout << "Level saved" << std::endl;
                    }
                    break;
                case sf::Keyboard::L:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                        tileEditor->loadLevel("level.dat");
                        std::cout << "Level loaded" << std::endl;
                    }
                    break;
                case sf::Keyboard::N:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                        tileEditor->clear();
                        entityManager->clear();
                        selectedEntity = nullptr;
                        propertyEditor->setEntity(nullptr);
                        std::cout << "New level created" << std::endl;
                    }
                    break;
                case sf::Keyboard::E:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                        entityManager->saveEntities("entities.dat");
                        std::cout << "Entities saved" << std::endl;
                    }
                    break;
                case sf::Keyboard::R:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                        entityManager->loadEntities("entities.dat");
                        std::cout << "Entities loaded" << std::endl;
                    }
                    break;
                case sf::Keyboard::Delete:
                    if (selectedEntity) {
                        entityManager->removeEntity(selectedEntity->id);
                        selectedEntity = nullptr;
                        propertyEditor->setEntity(nullptr);
                        std::cout << "Entity deleted" << std::endl;
                    }
                    break;
                default:
                    break;
            }
        }
        
        if (event.type == sf::Event::MouseMoved) {
            mousePos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
        }
    }
}

void EditorApp::update() {
    // Convert mouse position to world coordinates
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    Vector3D worldPos = engine->screenToWorld(mousePosF, currentLayer);
    
    // Snap to grid
    cursorPosition.x = std::round(worldPos.x);
    cursorPosition.y = std::round(worldPos.y);
    cursorPosition.z = currentLayer;
}

void EditorApp::render() {
    window->clear(sf::Color(40, 40, 50));
    
    // Render all tiles in the level
    for (const auto& tile : tileEditor->getTiles()) {
        sf::Color color;
        switch (tile.tileType) {
            case 0: color = sf::Color(100, 150, 100); break; // Grass
            case 1: color = sf::Color(150, 150, 150); break; // Stone
            case 2: color = sf::Color(139, 69, 19); break;   // Wood
            case 3: color = sf::Color(100, 100, 200); break; // Water
            case 4: color = sf::Color(200, 200, 100); break; // Sand
            default: color = sf::Color::White; break;
        }
        
        engine->renderTile(*window, tile.position, color);
    }
    
    // Render all entities
    for (const auto& entity : entityManager->getEntities()) {
        sf::Color entityColor;
        switch (entity.type) {
            case EntityType::NPC: entityColor = sf::Color(255, 100, 100); break;
            case EntityType::ITEM: entityColor = sf::Color(255, 255, 100); break;
            case EntityType::CONTAINER: entityColor = sf::Color(150, 100, 50); break;
            case EntityType::LIGHT: entityColor = sf::Color(255, 255, 200); break;
            case EntityType::SPAWN_POINT: entityColor = sf::Color(100, 255, 100); break;
            case EntityType::TRIGGER: entityColor = sf::Color(200, 100, 255); break;
            case EntityType::DOOR: entityColor = sf::Color(100, 150, 200); break;
            default: entityColor = sf::Color(180, 180, 180); break;
        }
        
        // Highlight selected entity
        if (selectedEntity && selectedEntity->id == entity.id) {
            entityColor = sf::Color(255, 255, 0);
        }
        
        engine->renderTile(*window, entity.position, entityColor);
    }
    
    // Render cursor based on mode
    if (currentMode == EditorMode::TILE || currentMode == EditorMode::ENTITY) {
        engine->renderTile(*window, cursorPosition, sf::Color(255, 255, 0, 128));
    }
    
    renderUI();
    
    window->display();
}

void EditorApp::renderUI() {
    // Render UI panels
    toolbar->render(*window);
    
    if (objectBrowser->isVisible()) {
        objectBrowser->render(*window);
    }
    
    if (propertyEditor->isVisible()) {
        propertyEditor->render(*window);
    }
    
    if (scriptEditor->isVisible()) {
        scriptEditor->render(*window);
    }
}

void EditorApp::handleTileMode(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Num1:
            case sf::Keyboard::Num2:
            case sf::Keyboard::Num3:
            case sf::Keyboard::Num4:
            case sf::Keyboard::Num5:
                currentTileType = event.key.code - sf::Keyboard::Num1;
                std::cout << "Selected tile type: " << currentTileType << std::endl;
                break;
            default:
                break;
        }
    }
    
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mouseClickPos(
            static_cast<float>(event.mouseButton.x),
            static_cast<float>(event.mouseButton.y)
        );
        
        // Check if click is in UI area
        if (toolbar->contains(mouseClickPos) || 
            (objectBrowser->isVisible() && objectBrowser->contains(mouseClickPos)) ||
            (propertyEditor->isVisible() && propertyEditor->contains(mouseClickPos))) {
            return; // Don't place tiles in UI area
        }
        
        if (event.mouseButton.button == sf::Mouse::Left) {
            // Place tile
            tileEditor->placeTile(cursorPosition, currentTileType);
            std::cout << "Placed tile at (" << cursorPosition.x << ", " 
                      << cursorPosition.y << ", " << cursorPosition.z << ")" << std::endl;
        } else if (event.mouseButton.button == sf::Mouse::Right) {
            // Remove tile
            tileEditor->removeTile(cursorPosition);
            std::cout << "Removed tile at (" << cursorPosition.x << ", " 
                      << cursorPosition.y << ", " << cursorPosition.z << ")" << std::endl;
        }
    }
}

void EditorApp::handleEntityMode(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mouseClickPos(
            static_cast<float>(event.mouseButton.x),
            static_cast<float>(event.mouseButton.y)
        );
        
        // Check if click is in UI area
        if (toolbar->contains(mouseClickPos) || 
            objectBrowser->contains(mouseClickPos) ||
            propertyEditor->contains(mouseClickPos)) {
            return;
        }
        
        if (event.mouseButton.button == sf::Mouse::Left) {
            // Place entity
            Entity newEntity;
            newEntity.type = objectBrowser->getSelectedType();
            newEntity.name = "New " + newEntity.getTypeName();
            newEntity.position = cursorPosition;
            newEntity.isMultiplayerSync = (newEntity.type == EntityType::NPC || 
                                           newEntity.type == EntityType::SPAWN_POINT);
            
            int entityId = entityManager->addEntity(newEntity);
            std::cout << "Placed entity " << entityId << " at (" 
                      << cursorPosition.x << ", " << cursorPosition.y << ", " 
                      << cursorPosition.z << ")" << std::endl;
        } else if (event.mouseButton.button == sf::Mouse::Right) {
            // Select entity
            Entity* entity = entityManager->getEntityAtPosition(cursorPosition);
            if (entity) {
                selectedEntity = entity;
                propertyEditor->setEntity(selectedEntity);
                std::cout << "Selected entity " << entity->id << " (" 
                          << entity->getTypeName() << ")" << std::endl;
            }
        }
    }
}

void EditorApp::handleScriptMode(sf::Event& event) {
    // Script mode is primarily handled through the script editor panel
    // Additional keyboard shortcuts or script-specific operations can be added here
}

} // namespace IsometricMUD
