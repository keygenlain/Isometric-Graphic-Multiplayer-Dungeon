#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include <string>
#include <vector>
#include <functional>

namespace IsometricMUD {

/**
 * @brief Editor modes
 */
enum class EditorMode {
    TILE,
    ENTITY,
    SCRIPT,
    LANDSCAPE
};

/**
 * @brief UI Panel for the construction set
 */
class UIPanel {
public:
    UIPanel(float x, float y, float width, float height);
    virtual ~UIPanel();
    
    virtual void render(sf::RenderWindow& window) = 0;
    virtual void handleClick(const sf::Vector2f& mousePos) = 0;
    
    bool contains(const sf::Vector2f& point) const;
    void setPosition(float x, float y);
    void setSize(float width, float height);
    
    bool isVisible() const { return visible; }
    void setVisible(bool vis) { visible = vis; }

protected:
    sf::RectangleShape background;
    sf::Vector2f position;
    sf::Vector2f size;
    bool visible;
};

/**
 * @brief Object browser panel
 */
class ObjectBrowserPanel : public UIPanel {
public:
    ObjectBrowserPanel(float x, float y, float width, float height);
    
    void render(sf::RenderWindow& window) override;
    void handleClick(const sf::Vector2f& mousePos) override;
    
    void setEntityTypes(const std::vector<EntityType>& types);
    EntityType getSelectedType() const { return selectedType; }
    void setOnSelectionChanged(std::function<void(EntityType)> callback);

private:
    std::vector<EntityType> entityTypes;
    EntityType selectedType;
    int scrollOffset;
    std::function<void(EntityType)> onSelectionChanged;
    sf::Font font;
};

/**
 * @brief Property editor panel
 */
class PropertyEditorPanel : public UIPanel {
public:
    PropertyEditorPanel(float x, float y, float width, float height);
    
    void render(sf::RenderWindow& window) override;
    void handleClick(const sf::Vector2f& mousePos) override;
    
    void setEntity(Entity* entity);
    Entity* getEntity() const { return currentEntity; }
    
    void updateProperty(const std::string& key, const PropertyValue& value);

private:
    Entity* currentEntity;
    sf::Font font;
    std::map<std::string, sf::RectangleShape> propertyFields;
};

/**
 * @brief Toolbar panel
 */
class ToolbarPanel : public UIPanel {
public:
    ToolbarPanel(float x, float y, float width, float height);
    
    void render(sf::RenderWindow& window) override;
    void handleClick(const sf::Vector2f& mousePos) override;
    
    EditorMode getCurrentMode() const { return currentMode; }
    void setOnModeChanged(std::function<void(EditorMode)> callback);

private:
    EditorMode currentMode;
    std::vector<sf::RectangleShape> modeButtons;
    std::function<void(EditorMode)> onModeChanged;
    sf::Font font;
};

/**
 * @brief Script editor panel
 */
class ScriptEditorPanel : public UIPanel {
public:
    ScriptEditorPanel(float x, float y, float width, float height);
    
    void render(sf::RenderWindow& window) override;
    void handleClick(const sf::Vector2f& mousePos) override;
    
    void setScriptName(const std::string& name);
    std::string getScriptName() const { return scriptName; }
    
    void setScriptContent(const std::string& content);
    std::string getScriptContent() const { return scriptContent; }

private:
    std::string scriptName;
    std::string scriptContent;
    sf::Font font;
    int scrollOffset;
};

} // namespace IsometricMUD
