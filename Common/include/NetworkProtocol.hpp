#pragma once

#include <SFML/Network.hpp>
#include "Vector3D.hpp"
#include "Movement.hpp"
#include <string>

namespace IsometricMUD {

/**
 * @brief Network packet types for client-server communication
 */
enum class PacketType : sf::Uint8 {
    CONNECT,
    DISCONNECT,
    MOVE,
    CHAT,
    UPDATE_POSITION,
    SPAWN_ENTITY,
    REMOVE_ENTITY,
    SCRIPT_EVENT
};

/**
 * @brief Network protocol handler
 */
class NetworkProtocol {
public:
    /**
     * @brief Create a movement packet
     */
    static sf::Packet createMovePacket(sf::Uint32 entityId, Direction dir);

    /**
     * @brief Create a position update packet
     */
    static sf::Packet createPositionPacket(sf::Uint32 entityId, const Vector3D& position);

    /**
     * @brief Create a chat message packet
     */
    static sf::Packet createChatPacket(const std::string& message);

    /**
     * @brief Parse packet type from a received packet
     */
    static PacketType getPacketType(sf::Packet& packet);

    /**
     * @brief Extract movement data from packet
     */
    static bool parseMovePacket(sf::Packet& packet, sf::Uint32& entityId, Direction& dir);

    /**
     * @brief Extract position data from packet
     */
    static bool parsePositionPacket(sf::Packet& packet, sf::Uint32& entityId, Vector3D& position);
};

} // namespace IsometricMUD
