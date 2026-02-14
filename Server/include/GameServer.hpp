#pragma once

#include <SFML/Network.hpp>
#include "Vector3D.hpp"
#include "NetworkProtocol.hpp"
#include <map>
#include <memory>
#include <thread>

namespace IsometricMUD {

/**
 * @brief Represents a connected client
 */
struct ClientInfo {
    sf::Uint32 id;
    std::unique_ptr<sf::TcpSocket> socket;
    Vector3D position;
    std::string name;
};

/**
 * @brief Main game server
 */
class GameServer {
public:
    GameServer();
    ~GameServer();

    /**
     * @brief Start the server on a given port
     */
    bool start(unsigned short port);

    /**
     * @brief Stop the server
     */
    void stop();

    /**
     * @brief Main server loop
     */
    void run();

private:
    void acceptClients();
    void handleClient(sf::Uint32 clientId);
    void broadcastPacket(const sf::Packet& packet, sf::Uint32 excludeClient = 0);
    
    bool running;
    sf::TcpListener listener;
    std::map<sf::Uint32, std::unique_ptr<ClientInfo>> clients;
    sf::Uint32 nextClientId;
    std::thread acceptThread;
};

} // namespace IsometricMUD
