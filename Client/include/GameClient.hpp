#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "IsometricEngine.hpp"
#include "Vector3D.hpp"
#include "Movement.hpp"
#include <memory>

namespace IsometricMUD {

/**
 * @brief Main game client
 */
class GameClient {
public:
    GameClient();
    ~GameClient();

    /**
     * @brief Connect to server
     */
    bool connect(const std::string& serverAddress, unsigned short port);

    /**
     * @brief Disconnect from server
     */
    void disconnect();

    /**
     * @brief Initialize the client window and graphics
     */
    bool initialize();

    /**
     * @brief Main client loop
     */
    void run();

private:
    void handleInput();
    void update();
    void render();
    void handleNetworkMessages();
    
    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<IsometricEngine> engine;
    sf::TcpSocket socket;
    bool connected;
    bool running;
    
    Vector3D playerPosition;
    sf::Uint32 playerId;
    
    // Camera control
    sf::Vector2f cameraOffset;
};

} // namespace IsometricMUD
