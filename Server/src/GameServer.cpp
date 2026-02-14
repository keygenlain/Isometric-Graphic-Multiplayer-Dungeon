#include "GameServer.hpp"
#include "Movement.hpp"
#include <iostream>

namespace IsometricMUD {

GameServer::GameServer() : running(false), nextClientId(1) {
}

GameServer::~GameServer() {
    stop();
}

bool GameServer::start(unsigned short port) {
    if (listener.listen(port) != sf::Socket::Done) {
        std::cerr << "Error: Could not bind to port " << port << std::endl;
        return false;
    }
    
    std::cout << "Server started on port " << port << std::endl;
    running = true;
    return true;
}

void GameServer::stop() {
    running = false;
    listener.close();
    
    // Close all client connections
    for (auto& client : clients) {
        if (client.second->socket) {
            client.second->socket->disconnect();
        }
    }
    clients.clear();
    
    if (acceptThread.joinable()) {
        acceptThread.join();
    }
}

void GameServer::run() {
    // Start accepting clients in a separate thread
    acceptThread = std::thread(&GameServer::acceptClients, this);
    
    // Main server loop
    while (running) {
        sf::sleep(sf::milliseconds(16)); // ~60 FPS
        
        // Process client messages
        for (auto& clientPair : clients) {
            sf::Packet packet;
            sf::Socket::Status status = clientPair.second->socket->receive(packet);
            
            if (status == sf::Socket::Done) {
                PacketType type = NetworkProtocol::getPacketType(packet);
                
                switch (type) {
                    case PacketType::MOVE: {
                        sf::Uint32 entityId;
                        Direction dir;
                        if (NetworkProtocol::parseMovePacket(packet, entityId, dir)) {
                            // Update position
                            clientPair.second->position = Movement::applyMovement(
                                clientPair.second->position, dir);
                            
                            // Broadcast new position to all clients
                            sf::Packet updatePacket = NetworkProtocol::createPositionPacket(
                                clientPair.first, clientPair.second->position);
                            broadcastPacket(updatePacket);
                        }
                        break;
                    }
                    case PacketType::CHAT: {
                        // Broadcast chat message
                        broadcastPacket(packet);
                        break;
                    }
                    default:
                        break;
                }
            } else if (status == sf::Socket::Disconnected) {
                std::cout << "Client " << clientPair.first << " disconnected" << std::endl;
                clientPair.second->socket->disconnect();
            }
        }
    }
}

void GameServer::acceptClients() {
    while (running) {
        auto socket = std::make_unique<sf::TcpSocket>();
        if (listener.accept(*socket) == sf::Socket::Done) {
            sf::Uint32 clientId = nextClientId++;
            
            auto client = std::make_unique<ClientInfo>();
            client->id = clientId;
            client->socket = std::move(socket);
            client->position = Vector3D(0, 0, 0);
            
            clients[clientId] = std::move(client);
            
            std::cout << "New client connected: " << clientId << std::endl;
            
            // Send spawn packet to all other clients
            sf::Packet spawnPacket = NetworkProtocol::createPositionPacket(
                clientId, Vector3D(0, 0, 0));
            broadcastPacket(spawnPacket, clientId);
        }
    }
}

void GameServer::handleClient(sf::Uint32 clientId) {
    // Client handling is done in the main loop
}

void GameServer::broadcastPacket(const sf::Packet& packet, sf::Uint32 excludeClient) {
    for (auto& client : clients) {
        if (client.first != excludeClient && client.second->socket) {
            sf::Packet packetCopy = packet;
            client.second->socket->send(packetCopy);
        }
    }
}

} // namespace IsometricMUD
