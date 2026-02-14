# Isometric MUD Construction Set - User Guide

## Overview

The Isometric MUD Construction Set is a comprehensive level editor inspired by the Morrowind Construction Set, designed specifically for creating multiplayer isometric dungeon games. It provides powerful tools for world building, entity placement, scripting, and multiplayer zone configuration.

## Features

### Multi-Mode Editor
The Construction Set operates in four distinct modes:
- **Tile Mode**: Place and edit terrain tiles
- **Entity Mode**: Add game objects (NPCs, items, containers, etc.)
- **Script Mode**: Create and edit game scripts
- **Landscape Mode**: Advanced terrain editing (future expansion)

### Entity System
Place and configure various game objects:
- **NPCs**: Non-player characters with AI scripts
- **Items**: Collectible objects (weapons, armor, potions, books)
- **Containers**: Chests, barrels, crates
- **Lights**: Dynamic lighting sources
- **Spawn Points**: Player and enemy spawn locations
- **Triggers**: Event triggers for scripting
- **Doors**: Entryways and portals
- **Furniture & Decorations**: World objects

### Multiplayer Support
- Network-synchronized entities (NPCs, spawn points)
- Multiplayer spawn point configuration
- Server-side entity persistence
- Client synchronization flags

### Property System
Each entity supports custom properties:
- Integer values (health, damage, count)
- Float values (speed, scale, rotation)
- String values (descriptions, dialog)
- Boolean flags (active, locked, visible)

## Getting Started

### Installation
Build the Construction Set from source:
```bash
mkdir build && cd build
cmake .. -DBUILD_EDITOR=ON
cmake --build .
./Editor/Editor
```

### First Steps
1. Launch the Construction Set
2. Click the **Tile** mode button to start with terrain
3. Press `1-5` to select tile types
4. Click in the viewport to place tiles
5. Use Page Up/Down to change layers

## Interface

### Toolbar (Top)
Four mode buttons:
- **Tile**: Terrain editing mode
- **Entity**: Object placement mode
- **Script**: Script editing mode
- **Landscape**: Advanced terrain (future)

### Object Browser (Left Panel)
- Lists all available entity types
- Click to select an entity for placement
- Scroll through categories
- Visible only in Entity mode

### Property Editor (Right Panel)
- Shows properties of selected entity
- Edit name, position, rotation, scale
- Modify custom properties
- Delete selected entity
- Always visible

### Script Editor (Center Overlay)
- Edit script content inline
- Appears when in Script mode
- Syntax highlighting (future)
- Script validation

### Viewport (Center)
- Isometric 3D view of your level
- Yellow cursor shows placement location
- Colored tiles and entities
- Layer-based rendering

## Controls

### Global Shortcuts
| Key | Action |
|-----|--------|
| ESC | Exit editor |
| Page Up | Move up one layer (Z+1) |
| Page Down | Move down one layer (Z-1) |
| Ctrl+S | Save level tiles |
| Ctrl+L | Load level tiles |
| Ctrl+E | Save entities |
| Ctrl+R | Load entities |
| Ctrl+N | New level (clear all) |

### Tile Mode
| Key/Action | Function |
|------------|----------|
| 1 | Select Grass tile |
| 2 | Select Stone tile |
| 3 | Select Wood tile |
| 4 | Select Water tile |
| 5 | Select Sand tile |
| Left Click | Place selected tile |
| Right Click | Remove tile |

### Entity Mode
| Action | Function |
|--------|----------|
| Select from Browser | Choose entity type to place |
| Left Click | Place selected entity |
| Right Click | Select entity for editing |
| Delete | Remove selected entity |

### Script Mode
| Action | Function |
|--------|----------|
| Edit Panel | Modify script content |
| Attach to Entity | Link script to selected entity |

## Workflow

### Creating a Basic Level

1. **Start with Terrain (Tile Mode)**
   ```
   - Switch to Tile mode
   - Press 1 for grass tiles
   - Click to create a base layer
   - Use Page Up to go to layer 1
   - Add elevated terrain
   ```

2. **Add Entities (Entity Mode)**
   ```
   - Switch to Entity mode
   - Select "Spawn Point" from browser
   - Click to place player start location
   - Select "NPC" and place enemies
   - Add containers and items
   ```

3. **Configure Properties**
   ```
   - Right-click entity to select
   - View properties in right panel
   - Modify name, position, scripts
   - Set multiplayer sync flag
   ```

4. **Save Your Work**
   ```
   - Ctrl+S to save tiles
   - Ctrl+E to save entities
   - Files: level.dat, entities.dat
   ```

### Creating a Multiplayer Level

1. **Place Spawn Points**
   ```
   - Use "Spawn Point" entity type
   - Place multiple spawn locations
   - Set isMultiplayerSync = true
   - Distribute evenly across map
   ```

2. **Add NPCs**
   ```
   - Place enemy NPCs
   - Enable multiplayer sync
   - Attach AI scripts
   - Configure health/damage properties
   ```

3. **Create Zones**
   ```
   - Use Trigger entities for zone boundaries
   - Attach zone scripts
   - Configure respawn areas
   - Set PvP/PvE flags (via properties)
   ```

### Scripting Entities

1. **Attach Script to Entity**
   ```
   - Select entity (right-click)
   - Set scriptName property
   - Switch to Script mode
   - Write script content
   ```

2. **Example Script**
   ```papyrus
   ; Treasure chest script
   Event OnActivate()
       Print("You opened a treasure chest!")
       GiveItem(Player, "Gold", 100)
   EndEvent
   
   Function OnInit()
       SetLocked(true)
       RequireKey("TreasureKey")
   EndFunction
   ```

3. **Script Events**
   - OnInit: Called when entity spawns
   - OnActivate: Player interacts with entity
   - OnEnter: Player enters trigger zone
   - OnExit: Player leaves trigger zone
   - OnDeath: NPC dies

## Entity Types Reference

### NPC
- Enemies, allies, merchants
- Requires: AI script, health property
- Multiplayer: Enable sync for server-controlled

### Item
- Collectibles, quest objects
- Properties: value, weight, stackable
- Multiplayer: Sync for shared loot

### Container
- Storage objects (chests, barrels)
- Properties: capacity, locked, key
- Multiplayer: Sync for shared storage

### Light
- Illumination sources
- Properties: radius, color, intensity
- Multiplayer: Client-side only

### Spawn Point
- Player/NPC spawn locations
- Properties: respawn time, faction
- Multiplayer: **Must** enable sync

### Trigger
- Invisible event zones
- Requires: trigger script
- Properties: size, repeatable
- Multiplayer: Sync for shared events

### Door
- Entrances, exits, portals
- Properties: destination, locked
- Multiplayer: Sync for state

### Weapon/Armor/Potion
- Equippable items
- Properties: damage, defense, effect
- Multiplayer: Sync for inventory

### Book
- Readable text objects
- Properties: text content, skill bonus
- Multiplayer: Client-side

### Furniture/Decoration
- Static world objects
- No special properties needed
- Multiplayer: Client-side only

## Tips and Best Practices

### Level Design
- Start with a clear layout plan
- Use layers for elevation and depth
- Balance open spaces with corridors
- Place spawn points strategically

### Performance
- Limit entities per cell (< 100 recommended)
- Use decorations sparingly
- Consolidate scripts where possible
- Test with multiple clients

### Multiplayer
- Always test spawn point distribution
- Enable sync only for essential entities
- Use triggers for zone boundaries
- Balance PvE and PvP areas

### Scripting
- Keep scripts simple and focused
- Use descriptive names
- Test scripts thoroughly
- Handle edge cases

## File Formats

### Level File (level.dat)
Binary format containing:
- Tile count
- For each tile:
  - Position (x, y, z)
  - Tile type (0-4)
  - Script name

### Entity File (entities.dat)
Binary format containing:
- Entity count
- For each entity:
  - ID, name, type
  - Position, rotation, scale
  - Script name
  - Multiplayer sync flag
  - Property count and values

### Script Files (.script)
Text format (papyrus-like):
- Event definitions
- Function declarations
- Native function calls
- Comments with semicolons

## Troubleshooting

### Editor Won't Start
- Check SFML installation
- Verify build completed successfully
- Run from correct directory

### Can't Place Tiles/Entities
- Check correct mode is selected
- Ensure not clicking on UI panels
- Verify cursor is in viewport

### Entities Not Appearing
- Check layer (Page Up/Down)
- Verify entity was saved (Ctrl+E)
- Try reloading (Ctrl+R)

### Multiplayer Issues
- Verify spawn points have sync enabled
- Check server loads entities correctly
- Test with multiple clients

### Scripts Not Working
- Verify script file exists
- Check script name matches entity
- Look for syntax errors
- Test with simple Print() first

## Advanced Topics

### Custom Properties
Add properties to entities:
1. Select entity
2. Property editor will show existing properties
3. Properties saved automatically
4. Access in scripts via GetProperty()

### Multi-Layer Levels
Create complex 3D structures:
- Use layers for floors/ceilings
- Stairs span multiple layers
- Triggers can be layer-specific
- NPCs move between layers

### Zone Management
Organize large levels:
- Use triggers to define zones
- Separate PvP/PvE areas
- Configure respawn per zone
- Load zones dynamically (future)

## Integration with Game

### Server Setup
```cpp
// Load level on server
tileEditor->loadLevel("level.dat");
entityManager->loadEntities("entities.dat");

// Sync entities to clients
for (auto& entity : entityManager->getEntities()) {
    if (entity.isMultiplayerSync) {
        broadcastEntity(entity);
    }
}
```

### Client Setup
```cpp
// Receive level data from server
receiveLevel();
receiveEntities();

// Render in game
isometricEngine->render(tiles, entities);
```

## Future Features

Planned enhancements:
- Advanced landscape sculpting tools
- Texture and sprite support
- Visual script editor
- Prefab system
- Undo/redo functionality
- Copy/paste entities
- Search and filter tools
- Minimap view
- Lighting preview
- Multiplayer editing (collaborative)

## Support

For issues, questions, or contributions:
- Check IMPLEMENTATION.md for technical details
- Review BUILD.md for compilation issues
- See README.md for project overview
- Visit project repository for updates

---

**Isometric MUD Construction Set** - Build immersive multiplayer worlds with ease!
