#include "NetworkProtocol.hpp"

namespace IsometricMUD {

sf::Packet NetworkProtocol::createMovePacket(sf::Uint32 entityId, Direction dir) {
    sf::Packet packet;
    packet << static_cast<sf::Uint8>(PacketType::MOVE);
    packet << entityId;
    packet << static_cast<sf::Uint8>(dir);
    return packet;
}

sf::Packet NetworkProtocol::createPositionPacket(sf::Uint32 entityId, const Vector3D& position) {
    sf::Packet packet;
    packet << static_cast<sf::Uint8>(PacketType::UPDATE_POSITION);
    packet << entityId;
    packet << position.x << position.y << position.z;
    return packet;
}

sf::Packet NetworkProtocol::createChatPacket(const std::string& message) {
    sf::Packet packet;
    packet << static_cast<sf::Uint8>(PacketType::CHAT);
    packet << message;
    return packet;
}

PacketType NetworkProtocol::getPacketType(sf::Packet& packet) {
    sf::Uint8 type;
    packet >> type;
    return static_cast<PacketType>(type);
}

bool NetworkProtocol::parseMovePacket(sf::Packet& packet, sf::Uint32& entityId, Direction& dir) {
    sf::Uint8 dirValue;
    if (packet >> entityId >> dirValue) {
        dir = static_cast<Direction>(dirValue);
        return true;
    }
    return false;
}

bool NetworkProtocol::parsePositionPacket(sf::Packet& packet, sf::Uint32& entityId, Vector3D& position) {
    return (packet >> entityId >> position.x >> position.y >> position.z);
}

} // namespace IsometricMUD
