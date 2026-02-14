#pragma once

#include <SFML/Graphics.hpp>
#include "Updater.hpp"
#include <memory>

namespace IsometricMUD {

/**
 * @brief Main launcher application
 */
class LauncherApp {
public:
    LauncherApp();
    ~LauncherApp();

    /**
     * @brief Initialize the launcher
     */
    bool initialize();

    /**
     * @brief Run the launcher
     */
    void run();

private:
    void handleEvents();
    void update();
    void render();
    void launchClient();
    void launchServer();
    void launchEditor();
    
    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<Updater> updater;
    sf::Font font;
    bool running;
};

} // namespace IsometricMUD
