#include "UIPanel.hpp"
#include <iostream>

namespace IsometricMUD {

// UIPanel base class
UIPanel::UIPanel(float x, float y, float width, float height)
    : position(x, y), size(width, height), visible(true) {
    background.setPosition(x, y);
    background.setSize(sf::Vector2f(width, height));
    background.setFillColor(sf::Color(40, 40, 40, 230));
    background.setOutlineColor(sf::Color(80, 80, 80));
    background.setOutlineThickness(2.0f);
}

UIPanel::~UIPanel() {
}

bool UIPanel::contains(const sf::Vector2f& point) const {
    return point.x >= position.x && point.x <= position.x + size.x &&
           point.y >= position.y && point.y <= position.y + size.y;
}

void UIPanel::setPosition(float x, float y) {
    position = sf::Vector2f(x, y);
    background.setPosition(x, y);
}

void UIPanel::setSize(float width, float height) {
    size = sf::Vector2f(width, height);
    background.setSize(sf::Vector2f(width, height));
}

// ObjectBrowserPanel
ObjectBrowserPanel::ObjectBrowserPanel(float x, float y, float width, float height)
    : UIPanel(x, y, width, height), selectedType(EntityType::DECORATION), scrollOffset(0) {
    // Initialize with all entity types
    entityTypes = {
        EntityType::NPC,
        EntityType::ITEM,
        EntityType::CONTAINER,
        EntityType::LIGHT,
        EntityType::SPAWN_POINT,
        EntityType::TRIGGER,
        EntityType::DOOR,
        EntityType::WEAPON,
        EntityType::ARMOR,
        EntityType::POTION,
        EntityType::BOOK,
        EntityType::FURNITURE,
        EntityType::DECORATION
    };
}

void ObjectBrowserPanel::render(sf::RenderWindow& window) {
    if (!visible) return;
    
    window.draw(background);
    
    // Draw title (without font for now - using simple rectangle)
    sf::RectangleShape titleBar(sf::Vector2f(size.x - 4, 30));
    titleBar.setPosition(position.x + 2, position.y + 2);
    titleBar.setFillColor(sf::Color(60, 60, 60));
    window.draw(titleBar);
    
    // Draw entity type list
    float yOffset = position.y + 40;
    for (size_t i = scrollOffset; i < entityTypes.size() && yOffset < position.y + size.y - 10; ++i) {
        sf::RectangleShape itemBox(sf::Vector2f(size.x - 20, 30));
        itemBox.setPosition(position.x + 10, yOffset);
        
        if (entityTypes[i] == selectedType) {
            itemBox.setFillColor(sf::Color(100, 150, 200));
        } else {
            itemBox.setFillColor(sf::Color(60, 60, 60));
        }
        
        window.draw(itemBox);
        yOffset += 35;
    }
}

void ObjectBrowserPanel::handleClick(const sf::Vector2f& mousePos) {
    if (!visible || !contains(mousePos)) return;
    
    // Check which item was clicked
    float yOffset = position.y + 40;
    for (size_t i = scrollOffset; i < entityTypes.size() && yOffset < position.y + size.y - 10; ++i) {
        if (mousePos.y >= yOffset && mousePos.y <= yOffset + 30) {
            selectedType = entityTypes[i];
            if (onSelectionChanged) {
                onSelectionChanged(selectedType);
            }
            std::cout << "Selected entity type: " << static_cast<int>(selectedType) << std::endl;
            break;
        }
        yOffset += 35;
    }
}

void ObjectBrowserPanel::setEntityTypes(const std::vector<EntityType>& types) {
    entityTypes = types;
}

void ObjectBrowserPanel::setOnSelectionChanged(std::function<void(EntityType)> callback) {
    onSelectionChanged = callback;
}

// PropertyEditorPanel
PropertyEditorPanel::PropertyEditorPanel(float x, float y, float width, float height)
    : UIPanel(x, y, width, height), currentEntity(nullptr) {
}

void PropertyEditorPanel::render(sf::RenderWindow& window) {
    if (!visible) return;
    
    window.draw(background);
    
    // Draw title bar
    sf::RectangleShape titleBar(sf::Vector2f(size.x - 4, 30));
    titleBar.setPosition(position.x + 2, position.y + 2);
    titleBar.setFillColor(sf::Color(60, 60, 60));
    window.draw(titleBar);
    
    if (!currentEntity) {
        // No entity selected message
        sf::RectangleShape messageBox(sf::Vector2f(size.x - 20, 40));
        messageBox.setPosition(position.x + 10, position.y + 50);
        messageBox.setFillColor(sf::Color(50, 50, 50));
        window.draw(messageBox);
        return;
    }
    
    // Draw entity properties
    float yOffset = position.y + 40;
    
    // Name field
    sf::RectangleShape nameField(sf::Vector2f(size.x - 20, 30));
    nameField.setPosition(position.x + 10, yOffset);
    nameField.setFillColor(sf::Color(70, 70, 70));
    window.draw(nameField);
    yOffset += 35;
    
    // Position fields
    for (int i = 0; i < 3; ++i) {
        sf::RectangleShape posField(sf::Vector2f(size.x - 20, 25));
        posField.setPosition(position.x + 10, yOffset);
        posField.setFillColor(sf::Color(70, 70, 70));
        window.draw(posField);
        yOffset += 30;
    }
}

void PropertyEditorPanel::handleClick(const sf::Vector2f& mousePos) {
    if (!visible || !contains(mousePos) || !currentEntity) return;
    
    // Handle property field clicks (text input would go here)
    std::cout << "Property editor clicked" << std::endl;
}

void PropertyEditorPanel::setEntity(Entity* entity) {
    currentEntity = entity;
}

void PropertyEditorPanel::updateProperty(const std::string& key, const PropertyValue& value) {
    if (currentEntity) {
        currentEntity->properties[key] = value;
    }
}

// ToolbarPanel
ToolbarPanel::ToolbarPanel(float x, float y, float width, float height)
    : UIPanel(x, y, width, height), currentMode(EditorMode::TILE) {
    
    background.setFillColor(sf::Color(50, 50, 50, 230));
    
    // Create mode buttons
    float buttonWidth = (width - 50) / 4.0f;
    for (int i = 0; i < 4; ++i) {
        sf::RectangleShape button(sf::Vector2f(buttonWidth, height - 10));
        button.setPosition(x + 10 + i * (buttonWidth + 10), y + 5);
        button.setFillColor(sf::Color(80, 80, 80));
        modeButtons.push_back(button);
    }
    
    modeButtons[0].setFillColor(sf::Color(120, 150, 180)); // Tile mode active by default
}

void ToolbarPanel::render(sf::RenderWindow& window) {
    if (!visible) return;
    
    window.draw(background);
    
    for (size_t i = 0; i < modeButtons.size(); ++i) {
        window.draw(modeButtons[i]);
    }
}

void ToolbarPanel::handleClick(const sf::Vector2f& mousePos) {
    if (!visible || !contains(mousePos)) return;
    
    // Check which button was clicked
    for (size_t i = 0; i < modeButtons.size(); ++i) {
        sf::FloatRect bounds = modeButtons[i].getGlobalBounds();
        if (bounds.contains(mousePos)) {
            // Reset all buttons
            for (auto& button : modeButtons) {
                button.setFillColor(sf::Color(80, 80, 80));
            }
            
            // Highlight clicked button
            modeButtons[i].setFillColor(sf::Color(120, 150, 180));
            
            // Set mode
            currentMode = static_cast<EditorMode>(i);
            
            if (onModeChanged) {
                onModeChanged(currentMode);
            }
            
            std::cout << "Mode changed to: " << static_cast<int>(currentMode) << std::endl;
            break;
        }
    }
}

void ToolbarPanel::setOnModeChanged(std::function<void(EditorMode)> callback) {
    onModeChanged = callback;
}

// ScriptEditorPanel
ScriptEditorPanel::ScriptEditorPanel(float x, float y, float width, float height)
    : UIPanel(x, y, width, height), scrollOffset(0) {
}

void ScriptEditorPanel::render(sf::RenderWindow& window) {
    if (!visible) return;
    
    window.draw(background);
    
    // Draw title bar
    sf::RectangleShape titleBar(sf::Vector2f(size.x - 4, 30));
    titleBar.setPosition(position.x + 2, position.y + 2);
    titleBar.setFillColor(sf::Color(60, 60, 60));
    window.draw(titleBar);
    
    // Draw script content area
    sf::RectangleShape contentArea(sf::Vector2f(size.x - 20, size.y - 50));
    contentArea.setPosition(position.x + 10, position.y + 40);
    contentArea.setFillColor(sf::Color(30, 30, 30));
    window.draw(contentArea);
}

void ScriptEditorPanel::handleClick(const sf::Vector2f& mousePos) {
    if (!visible || !contains(mousePos)) return;
    
    std::cout << "Script editor clicked" << std::endl;
}

void ScriptEditorPanel::setScriptName(const std::string& name) {
    scriptName = name;
}

void ScriptEditorPanel::setScriptContent(const std::string& content) {
    scriptContent = content;
}

} // namespace IsometricMUD
