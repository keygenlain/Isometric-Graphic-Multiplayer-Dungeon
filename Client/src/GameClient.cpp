#include "GameClient.hpp"
#include "NetworkProtocol.hpp"
#include <iostream>

namespace IsometricMUD {

GameClient::GameClient() 
    : connected(false), running(false), playerPosition(0, 0, 0), 
      playerId(0), cameraOffset(0, 0) {
}

GameClient::~GameClient() {
    disconnect();
}

bool GameClient::connect(const std::string& serverAddress, unsigned short port) {
    socket.setBlocking(false);
    
    if (socket.connect(serverAddress, port) != sf::Socket::Done) {
        std::cerr << "Could not connect to server" << std::endl;
        return false;
    }
    
    connected = true;
    std::cout << "Connected to server at " << serverAddress << ":" << port << std::endl;
    return true;
}

void GameClient::disconnect() {
    if (connected) {
        socket.disconnect();
        connected = false;
    }
}

bool GameClient::initialize() {
    window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode(1024, 768), 
        "Isometric MUD Client"
    );
    window->setFramerateLimit(60);
    
    engine = std::make_unique<IsometricEngine>();
    engine->initialize(1024, 768);
    
    return true;
}

void GameClient::run() {
    running = true;
    
    while (running && window->isOpen()) {
        handleInput();
        handleNetworkMessages();
        update();
        render();
    }
}

void GameClient::handleInput() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            running = false;
            window->close();
        }
        
        // Handle keyboard input for 6-directional movement
        if (event.type == sf::Event::KeyPressed) {
            Direction moveDir;
            bool shouldMove = true;
            
            switch (event.key.code) {
                case sf::Keyboard::W:
                case sf::Keyboard::Up:
                    moveDir = Direction::NORTH;
                    break;
                case sf::Keyboard::S:
                case sf::Keyboard::Down:
                    moveDir = Direction::SOUTH;
                    break;
                case sf::Keyboard::D:
                case sf::Keyboard::Right:
                    moveDir = Direction::EAST;
                    break;
                case sf::Keyboard::A:
                case sf::Keyboard::Left:
                    moveDir = Direction::WEST;
                    break;
                case sf::Keyboard::Q:
                case sf::Keyboard::PageUp:
                    moveDir = Direction::UP;
                    break;
                case sf::Keyboard::E:
                case sf::Keyboard::PageDown:
                    moveDir = Direction::DOWN;
                    break;
                default:
                    shouldMove = false;
                    break;
            }
            
            if (shouldMove && connected) {
                // Send movement packet to server
                sf::Packet packet = NetworkProtocol::createMovePacket(playerId, moveDir);
                socket.send(packet);
                
                // Update local position immediately for responsiveness
                playerPosition = Movement::applyMovement(playerPosition, moveDir);
            }
        }
    }
}

void GameClient::update() {
    // Update camera to follow player
    engine->setCameraPosition(playerPosition);
}

void GameClient::render() {
    window->clear(sf::Color(50, 50, 50));
    
    // Render the world grid
    for (int x = -5; x <= 5; x++) {
        for (int y = -5; y <= 5; y++) {
            for (int z = 0; z <= 2; z++) {
                Vector3D tilePos(x, y, z);
                sf::Color tileColor;
                
                if (z == 0) {
                    tileColor = sf::Color(100, 150, 100); // Ground
                } else {
                    tileColor = sf::Color(150, 150, 200, 100); // Upper levels, semi-transparent
                }
                
                engine->renderTile(*window, tilePos, tileColor);
            }
        }
    }
    
    // Render player
    engine->renderTile(*window, playerPosition, sf::Color::Yellow);
    
    window->display();
}

void GameClient::handleNetworkMessages() {
    if (!connected) return;
    
    sf::Packet packet;
    sf::Socket::Status status = socket.receive(packet);
    
    if (status == sf::Socket::Done) {
        PacketType type = NetworkProtocol::getPacketType(packet);
        
        switch (type) {
            case PacketType::UPDATE_POSITION: {
                sf::Uint32 entityId;
                Vector3D position;
                if (NetworkProtocol::parsePositionPacket(packet, entityId, position)) {
                    // Update entity position (for multiplayer)
                    std::cout << "Entity " << entityId << " moved to (" 
                              << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;
                }
                break;
            }
            default:
                break;
        }
    }
}

} // namespace IsometricMUD
