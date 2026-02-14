#include "EditorApp.hpp"
#include <iostream>
#include <cmath>

namespace IsometricMUD {

EditorApp::EditorApp() 
    : running(false), currentTileType(0), currentLayer(0), cursorPosition(0, 0, 0) {
}

EditorApp::~EditorApp() {
}

bool EditorApp::initialize() {
    window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode(1280, 720),
        "Isometric MUD Editor"
    );
    window->setFramerateLimit(60);
    
    engine = std::make_unique<IsometricEngine>();
    engine->initialize(1280, 720);
    
    tileEditor = std::make_unique<TileEditor>();
    scriptEngine = std::make_unique<ScriptEngine>();
    
    std::cout << "Editor initialized successfully" << std::endl;
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
        
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Escape:
                    running = false;
                    break;
                case sf::Keyboard::Num1:
                case sf::Keyboard::Num2:
                case sf::Keyboard::Num3:
                case sf::Keyboard::Num4:
                case sf::Keyboard::Num5:
                    currentTileType = event.key.code - sf::Keyboard::Num1;
                    std::cout << "Selected tile type: " << currentTileType << std::endl;
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
                    }
                    break;
                case sf::Keyboard::L:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                        tileEditor->loadLevel("level.dat");
                    }
                    break;
                case sf::Keyboard::N:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                        tileEditor->clear();
                        std::cout << "New level created" << std::endl;
                    }
                    break;
                default:
                    break;
            }
        }
        
        if (event.type == sf::Event::MouseButtonPressed) {
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
    
    // Render cursor
    engine->renderTile(*window, cursorPosition, sf::Color(255, 255, 0, 128));
    
    renderUI();
    
    window->display();
}

void EditorApp::renderUI() {
    // Draw simple UI text indicators
    // In a real implementation, would use proper UI with fonts
}

} // namespace IsometricMUD
