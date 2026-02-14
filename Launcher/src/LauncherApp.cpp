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
    
    // Note: Text rendering requires a font file
    // For a complete implementation, load a font with:
    // if (font.loadFromFile("font.ttf")) {
    //     sf::Text title("Isometric MUD Launcher", font, 30);
    //     title.setFillColor(sf::Color::White);
    //     title.setPosition(150, 50);
    //     window->draw(title);
    // }
    
    // For now, draw simple colored rectangles as placeholder UI
    sf::RectangleShape titleBar(sf::Vector2f(500, 60));
    titleBar.setPosition(50, 40);
    titleBar.setFillColor(sf::Color(50, 50, 60));
    window->draw(titleBar);
    
    sf::RectangleShape button1(sf::Vector2f(200, 40));
    button1.setPosition(200, 150);
    button1.setFillColor(sf::Color(70, 130, 70));
    window->draw(button1);
    
    sf::RectangleShape button2(sf::Vector2f(200, 40));
    button2.setPosition(200, 210);
    button2.setFillColor(sf::Color(70, 70, 130));
    window->draw(button2);
    
    sf::RectangleShape button3(sf::Vector2f(200, 40));
    button3.setPosition(200, 270);
    button3.setFillColor(sf::Color(130, 70, 70));
    window->draw(button3);
    
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
