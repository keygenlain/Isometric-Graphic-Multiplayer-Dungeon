#include "EntityManager.hpp"
#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>

namespace IsometricMUD {

EntityManager::EntityManager() : nextId(1) {
}

EntityManager::~EntityManager() {
}

int EntityManager::addEntity(const Entity& entity) {
    Entity newEntity = entity;
    newEntity.id = nextId++;
    entities.push_back(newEntity);
    return newEntity.id;
}

void EntityManager::removeEntity(int entityId) {
    entities.erase(
        std::remove_if(entities.begin(), entities.end(),
            [entityId](const Entity& e) { return e.id == entityId; }),
        entities.end()
    );
}

Entity* EntityManager::getEntity(int entityId) {
    for (auto& entity : entities) {
        if (entity.id == entityId) {
            return &entity;
        }
    }
    return nullptr;
}

Entity* EntityManager::getEntityAtPosition(const Vector3D& position, float tolerance) {
    for (auto& entity : entities) {
        float dx = entity.position.x - position.x;
        float dy = entity.position.y - position.y;
        float dz = entity.position.z - position.z;
        float distance = std::sqrt(dx*dx + dy*dy + dz*dz);
        
        if (distance <= tolerance) {
            return &entity;
        }
    }
    return nullptr;
}

std::vector<Entity*> EntityManager::getEntitiesByType(EntityType type) {
    std::vector<Entity*> result;
    for (auto& entity : entities) {
        if (entity.type == type) {
            result.push_back(&entity);
        }
    }
    return result;
}

void EntityManager::clear() {
    entities.clear();
    nextId = 1;
}

bool EntityManager::saveEntities(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to save entities to " << filename << std::endl;
        return false;
    }
    
    // Write entity count
    size_t count = entities.size();
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    
    // Write each entity
    for (const auto& entity : entities) {
        file.write(reinterpret_cast<const char*>(&entity.id), sizeof(entity.id));
        
        // Write name
        size_t nameLen = entity.name.length();
        file.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
        file.write(entity.name.c_str(), nameLen);
        
        // Write type
        file.write(reinterpret_cast<const char*>(&entity.type), sizeof(entity.type));
        
        // Write position
        file.write(reinterpret_cast<const char*>(&entity.position.x), sizeof(entity.position.x));
        file.write(reinterpret_cast<const char*>(&entity.position.y), sizeof(entity.position.y));
        file.write(reinterpret_cast<const char*>(&entity.position.z), sizeof(entity.position.z));
        
        // Write rotation and scale
        file.write(reinterpret_cast<const char*>(&entity.rotation), sizeof(entity.rotation));
        file.write(reinterpret_cast<const char*>(&entity.scale), sizeof(entity.scale));
        
        // Write script name
        size_t scriptLen = entity.scriptName.length();
        file.write(reinterpret_cast<const char*>(&scriptLen), sizeof(scriptLen));
        file.write(entity.scriptName.c_str(), scriptLen);
        
        // Write multiplayer sync flag
        file.write(reinterpret_cast<const char*>(&entity.isMultiplayerSync), sizeof(entity.isMultiplayerSync));
        
        // Write property count
        size_t propCount = entity.properties.size();
        file.write(reinterpret_cast<const char*>(&propCount), sizeof(propCount));
        
        // Write properties
        for (const auto& prop : entity.properties) {
            // Write property name
            size_t propNameLen = prop.first.length();
            file.write(reinterpret_cast<const char*>(&propNameLen), sizeof(propNameLen));
            file.write(prop.first.c_str(), propNameLen);
            
            // Write property value type
            file.write(reinterpret_cast<const char*>(&prop.second.type), sizeof(prop.second.type));
            
            // Write property value
            switch (prop.second.type) {
                case PropertyValue::Type::INT:
                    file.write(reinterpret_cast<const char*>(&prop.second.intValue), sizeof(prop.second.intValue));
                    break;
                case PropertyValue::Type::FLOAT:
                    file.write(reinterpret_cast<const char*>(&prop.second.floatValue), sizeof(prop.second.floatValue));
                    break;
                case PropertyValue::Type::BOOL:
                    file.write(reinterpret_cast<const char*>(&prop.second.boolValue), sizeof(prop.second.boolValue));
                    break;
                case PropertyValue::Type::STRING:
                    size_t strLen = prop.second.stringValue.length();
                    file.write(reinterpret_cast<const char*>(&strLen), sizeof(strLen));
                    file.write(prop.second.stringValue.c_str(), strLen);
                    break;
            }
        }
    }
    
    file.close();
    std::cout << "Saved " << count << " entities to " << filename << std::endl;
    return true;
}

bool EntityManager::loadEntities(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to load entities from " << filename << std::endl;
        return false;
    }
    
    clear();
    
    // Read entity count
    size_t count;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));
    
    // Read each entity
    for (size_t i = 0; i < count; ++i) {
        Entity entity;
        
        file.read(reinterpret_cast<char*>(&entity.id), sizeof(entity.id));
        
        // Read name
        size_t nameLen;
        file.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
        entity.name.resize(nameLen);
        file.read(&entity.name[0], nameLen);
        
        // Read type
        file.read(reinterpret_cast<char*>(&entity.type), sizeof(entity.type));
        
        // Read position
        file.read(reinterpret_cast<char*>(&entity.position.x), sizeof(entity.position.x));
        file.read(reinterpret_cast<char*>(&entity.position.y), sizeof(entity.position.y));
        file.read(reinterpret_cast<char*>(&entity.position.z), sizeof(entity.position.z));
        
        // Read rotation and scale
        file.read(reinterpret_cast<char*>(&entity.rotation), sizeof(entity.rotation));
        file.read(reinterpret_cast<char*>(&entity.scale), sizeof(entity.scale));
        
        // Read script name
        size_t scriptLen;
        file.read(reinterpret_cast<char*>(&scriptLen), sizeof(scriptLen));
        entity.scriptName.resize(scriptLen);
        file.read(&entity.scriptName[0], scriptLen);
        
        // Read multiplayer sync flag
        file.read(reinterpret_cast<char*>(&entity.isMultiplayerSync), sizeof(entity.isMultiplayerSync));
        
        // Read property count
        size_t propCount;
        file.read(reinterpret_cast<char*>(&propCount), sizeof(propCount));
        
        // Read properties
        for (size_t j = 0; j < propCount; ++j) {
            // Read property name
            size_t propNameLen;
            file.read(reinterpret_cast<char*>(&propNameLen), sizeof(propNameLen));
            std::string propName;
            propName.resize(propNameLen);
            file.read(&propName[0], propNameLen);
            
            // Read property value type
            PropertyValue::Type propType;
            file.read(reinterpret_cast<char*>(&propType), sizeof(propType));
            
            PropertyValue propValue;
            propValue.type = propType;
            
            // Read property value
            switch (propType) {
                case PropertyValue::Type::INT:
                    file.read(reinterpret_cast<char*>(&propValue.intValue), sizeof(propValue.intValue));
                    break;
                case PropertyValue::Type::FLOAT:
                    file.read(reinterpret_cast<char*>(&propValue.floatValue), sizeof(propValue.floatValue));
                    break;
                case PropertyValue::Type::BOOL:
                    file.read(reinterpret_cast<char*>(&propValue.boolValue), sizeof(propValue.boolValue));
                    break;
                case PropertyValue::Type::STRING:
                    size_t strLen;
                    file.read(reinterpret_cast<char*>(&strLen), sizeof(strLen));
                    propValue.stringValue.resize(strLen);
                    file.read(&propValue.stringValue[0], strLen);
                    break;
            }
            
            entity.properties[propName] = propValue;
        }
        
        entities.push_back(entity);
        if (entity.id >= nextId) {
            nextId = entity.id + 1;
        }
    }
    
    file.close();
    std::cout << "Loaded " << count << " entities from " << filename << std::endl;
    return true;
}

} // namespace IsometricMUD
