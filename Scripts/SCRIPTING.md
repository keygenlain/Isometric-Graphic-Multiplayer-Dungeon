# Scripting Language Reference

## Isometric MUD Scripting Language
A Papyrus-like scripting language for game events and logic.

## Syntax

### Comments
```papyrus
; This is a single-line comment
```

### Events
Events are triggered by game actions:
```papyrus
Event OnInit()
    ; Code here runs when initialized
EndEvent
```

### Functions
Functions can be called from events or other functions:
```papyrus
Function MyFunction()
    ; Function code
EndFunction
```

### Built-in Functions

#### Print
Display text to the player:
```papyrus
Print("Hello, world!")
```

### Variable Types (Planned)
- `Int` - Integer numbers
- `Float` - Floating point numbers
- `String` - Text strings
- `Bool` - True/False values

### Example Scripts

#### Player Initialization
```papyrus
Event OnPlayerInit()
    Print("Welcome to the game!")
EndEvent
```

#### Door Interaction
```papyrus
Event OnInteract()
    Print("You open the door")
    ; Open door logic
EndEvent
```

#### Treasure Chest
```papyrus
Event OnOpen()
    Print("You found treasure!")
    ; Add items to inventory
EndEvent
```

## Event Types

### Player Events
- `OnPlayerInit()` - Player first loads into game
- `OnPlayerEnterRoom()` - Player enters a new room
- `OnPlayerMove()` - Player moves

### Object Events
- `OnInteract()` - Player interacts with object
- `OnOpen()` - Object is opened
- `OnClose()` - Object is closed
- `OnDestroy()` - Object is destroyed

### World Events
- `OnInit()` - Script initialization
- `OnUpdate()` - Called every frame
- `OnTimer()` - Called on timer

## Best Practices

1. Use descriptive event names
2. Keep scripts focused and modular
3. Comment your code
4. Test scripts in the editor
5. Use Print() for debugging

## Future Enhancements
- Variable declarations
- Conditional statements (if/else)
- Loops (while/for)
- Arrays and collections
- Math operations
- String operations
- Inventory management
- Combat system hooks
