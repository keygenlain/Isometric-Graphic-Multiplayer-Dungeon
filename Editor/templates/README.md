# Construction Set Script Templates

This directory contains example script templates for use with the Isometric MUD Construction Set. These templates demonstrate how to attach scripts to entities for common game behaviors.

**Note:** These are example templates showing intended script syntax. The actual ScriptEngine implementation may need to be extended to support all features shown. Use these as a guide for designing your game scripts.

## Available Templates

### npc_enemy.script
Basic enemy NPC behavior with:
- Health and damage properties
- Player detection
- Combat engagement
- Death handling
- Loot dropping

**Usage:** Attach to NPC entities that should act as enemies.

### chest.script
Treasure chest interaction with:
- Lock/unlock mechanics
- Key requirement system
- Item distribution
- Multiplayer synchronization
- Empty state tracking

**Usage:** Attach to Container entities for lootable chests.

### spawn_point.script
Player spawn management with:
- Faction-based spawning
- Respawn timing
- Spawn point capacity
- Starting equipment
- Death handling

**Usage:** Attach to Spawn Point entities in multiplayer levels. **Must** enable `isMultiplayerSync`.

### trigger_zone.script
Area-based event triggers with:
- Zone notifications
- Teleportation
- Damage zones (lava, poison)
- Quest triggers
- Enter/exit events

**Usage:** Attach to Trigger entities for invisible event zones.

### door.script
Interactive door behavior with:
- Lock/unlock system
- Key requirements
- Teleportation to cells
- Open/close states
- Multiplayer state sync

**Usage:** Attach to Door entities.

## How to Use Templates

1. **In Construction Set:**
   - Place an entity (e.g., NPC, Container)
   - Right-click to select the entity
   - In Property Editor, set `scriptName` field
   - Enter the script filename (e.g., "npc_enemy.script")

2. **Customize the Script:**
   - Copy template to your level directory
   - Modify properties and behavior as needed
   - Test in game

3. **Script Location:**
   - Place scripts in same directory as level files
   - Or use relative path in scriptName field
   - Scripts are loaded by ScriptEngine at runtime

## Property System

Scripts can get/set entity properties:

```papyrus
; Get property
var health = GetProperty("health")

; Set property
SetProperty("health", 50)

; Check property type
if health > 0
    ; Do something
endif
```

## Multiplayer Considerations

For multiplayer entities:
1. Set `isMultiplayerSync = true` in Construction Set
2. Use `SyncProperty()` to sync changes across clients
3. Check `IsMultiplayer()` before syncing

```papyrus
if IsMultiplayer()
    SyncProperty("opened", true)
endif
```

## Built-in Functions

Common functions available in scripts:

### Player Functions
- `GiveItem(player, itemName, quantity)`
- `RemoveItem(player, itemName, quantity)`
- `PlayerHasItem(player, itemName)`
- `DealDamage(player, amount)`
- `HealPlayer(player, amount)`
- `TeleportPlayer(player, x, y, z)`
- `TeleportToCell(player, cellName)`

### Entity Functions
- `GetPosition()` - Returns entity position
- `SetPosition(x, y, z)` - Move entity
- `GetProperty(name)` - Get entity property
- `SetProperty(name, value)` - Set entity property
- `SyncProperty(name, value)` - Sync property to clients

### World Functions
- `SpawnItem(itemName, quantity, position)`
- `SpawnEntity(entityType, position)`
- `Despawn(delay)` - Remove entity after delay
- `PlaySound(soundName)`
- `PlayAmbience(ambienceName)`

### Utility Functions
- `Print(message)` - Console output
- `ShowMessage(player, message, duration)` - Screen message
- `RandomInt(min, max)` - Random integer
- `RandomFloat(min, max)` - Random float
- `RandomChance(probability)` - Random boolean (0.0-1.0)

### Multiplayer Functions
- `IsMultiplayer()` - Check if in multiplayer mode
- `BroadcastEvent(eventName, data)` - Send event to all clients
- `ScheduleRespawn(player, delay)` - Schedule player respawn

## Example: Creating a Boss NPC

1. Place NPC entity in Construction Set
2. Create `boss_dragon.script`:

```papyrus
Event OnInit()
    SetProperty("health", 500)
    SetProperty("damage", 25)
    SetProperty("boss", true)
    Print("Dragon Boss spawned!")
EndEvent

Event OnDeath()
    Print("Dragon Boss defeated!")
    BroadcastEvent("BossDefeated", "Dragon")
    SpawnItem("LegendarySword", 1, GetPosition())
    SpawnItem("Gold", 1000, GetPosition())
EndEvent
```

3. Attach script to NPC entity
4. Enable multiplayer sync
5. Test with multiple players

## Tips

- Keep scripts simple and focused
- Use descriptive property names
- Test scripts before deploying
- Handle edge cases (empty inventory, locked doors)
- Use Print() for debugging
- Comment your code

## See Also

- [CONSTRUCTION_SET_GUIDE.md](../CONSTRUCTION_SET_GUIDE.md) - Full editor documentation
- [Scripts/SCRIPTING.md](../../Scripts/SCRIPTING.md) - Scripting language reference
- [README.md](../../README.md) - Project overview
