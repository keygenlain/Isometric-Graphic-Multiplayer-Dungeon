#pragma once

#include "Vector3D.hpp"
#include <string>
#include <map>

namespace IsometricMUD {

/**
 * @brief Entity types for the editor
 */
enum class EntityType {
    NPC,
    ITEM,
    CONTAINER,
    LIGHT,
    SPAWN_POINT,
    TRIGGER,
    DOOR,
    WEAPON,
    ARMOR,
    POTION,
    BOOK,
    FURNITURE,
    DECORATION
};

/**
 * @brief Property value for entities
 */
struct PropertyValue {
    enum class Type { INT, FLOAT, STRING, BOOL };
    Type type;
    union {
        int intValue;
        float floatValue;
        bool boolValue;
    };
    std::string stringValue;
    
    PropertyValue() : type(Type::INT), intValue(0) {}
    explicit PropertyValue(int val) : type(Type::INT), intValue(val) {}
    explicit PropertyValue(float val) : type(Type::FLOAT), floatValue(val) {}
    explicit PropertyValue(bool val) : type(Type::BOOL), boolValue(val) {}
    explicit PropertyValue(const std::string& val) : type(Type::STRING), stringValue(val) {}
};

/**
 * @brief Entity data for the construction set
 */
struct Entity {
    int id;
    std::string name;
    EntityType type;
    Vector3D position;
    float rotation;
    float scale;
    std::string scriptName;
    std::map<std::string, PropertyValue> properties;
    bool isMultiplayerSync; // Whether this entity should sync across network
    
    Entity() 
        : id(0), name("Unnamed"), type(EntityType::DECORATION), 
          position(0, 0, 0), rotation(0.0f), scale(1.0f), 
          scriptName(""), isMultiplayerSync(false) {}
    
    // Get entity type as string
    std::string getTypeName() const {
        switch (type) {
            case EntityType::NPC: return "NPC";
            case EntityType::ITEM: return "Item";
            case EntityType::CONTAINER: return "Container";
            case EntityType::LIGHT: return "Light";
            case EntityType::SPAWN_POINT: return "Spawn Point";
            case EntityType::TRIGGER: return "Trigger";
            case EntityType::DOOR: return "Door";
            case EntityType::WEAPON: return "Weapon";
            case EntityType::ARMOR: return "Armor";
            case EntityType::POTION: return "Potion";
            case EntityType::BOOK: return "Book";
            case EntityType::FURNITURE: return "Furniture";
            case EntityType::DECORATION: return "Decoration";
            default: return "Unknown";
        }
    }
};

} // namespace IsometricMUD
