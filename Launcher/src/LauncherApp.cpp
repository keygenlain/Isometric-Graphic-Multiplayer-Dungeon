#include "LauncherApp.hpp"
#include <iostream>

namespace IsometricMUD {

LauncherApp::LauncherApp() : running(false) {
}

LauncherApp::~LauncherApp() {
}

bool LauncherApp::initialize() {
    window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode(600, 400),
        "Isometric MUD Launcher"
    );
    window->setFramerateLimit(60);
    
    updater = std::make_unique<Updater>();
    
    // Check for updates
    updater->checkForUpdates("http://update.server.com");
    
    return true;
}

void LauncherApp::run() {
    running = true;
    
    while (running && window->isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void LauncherApp::handleEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            running = false;
            window->close();
        }
        
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Num1:
                    launchClient();
                    break;
                case sf::Keyboard::Num2:
                    launchServer();
                    break;
                case sf::Keyboard::Num3:
                    launchEditor();
                    break;
                case sf::Keyboard::Escape:
                    running = false;
                    break;
                default:
                    break;
            }
        }
    }
}

void LauncherApp::update() {
    // Update logic
}

void LauncherApp::render() {
    window->clear(sf::Color(30, 30, 40));
    
    // Draw title and options
    sf::Text title;
    title.setString("Isometric MUD Launcher");
    title.setCharacterSize(30);
    title.setFillColor(sf::Color::White);
    title.setPosition(150, 50);
    
    // Create menu text without using font (will appear as rectangles, but structure is there)
    // In a real implementation, you would load a font file
    
    window->display();
}

void LauncherApp::launchClient() {
    std::cout << "Launching client..." << std::endl;
    // In a real implementation, would launch the Client executable
    #ifdef _WIN32
    system("start Client.exe");
    #else
    system("./Client &");
    #endif
}

void LauncherApp::launchServer() {
    std::cout << "Launching server..." << std::endl;
    #ifdef _WIN32
    system("start Server.exe");
    #else
    system("./Server &");
    #endif
}

void LauncherApp::launchEditor() {
    std::cout << "Launching editor..." << std::endl;
    #ifdef _WIN32
    system("start Editor.exe");
    #else
    system("./Editor &");
    #endif
}

} // namespace IsometricMUD
