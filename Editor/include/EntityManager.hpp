#pragma once

#include "Entity.hpp"
#include "Vector3D.hpp"
#include <vector>
#include <memory>
#include <string>

namespace IsometricMUD {

/**
 * @brief Manages entities in the construction set
 */
class EntityManager {
public:
    EntityManager();
    ~EntityManager();
    
    /**
     * @brief Add a new entity
     * @return The ID of the added entity
     */
    int addEntity(const Entity& entity);
    
    /**
     * @brief Remove entity by ID
     */
    void removeEntity(int entityId);
    
    /**
     * @brief Get entity by ID
     */
    Entity* getEntity(int entityId);
    
    /**
     * @brief Get entity at position (within tolerance)
     */
    Entity* getEntityAtPosition(const Vector3D& position, float tolerance = 0.5f);
    
    /**
     * @brief Get all entities
     */
    const std::vector<Entity>& getEntities() const { return entities; }
    
    /**
     * @brief Get entities by type
     */
    std::vector<Entity*> getEntitiesByType(EntityType type);
    
    /**
     * @brief Clear all entities
     */
    void clear();
    
    /**
     * @brief Get next available entity ID
     */
    int getNextId() const { return nextId; }
    
    /**
     * @brief Save entities to file
     */
    bool saveEntities(const std::string& filename);
    
    /**
     * @brief Load entities from file
     */
    bool loadEntities(const std::string& filename);

private:
    std::vector<Entity> entities;
    int nextId;
};

} // namespace IsometricMUD
