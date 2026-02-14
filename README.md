# Isometric Graphic Multiplayer Dungeon

A complex isometric engine for a MUD (Multi-User Dungeon) using SFML in C++.

## Features

### Core Features
- **6-Degree Movement System**: Move in all directions (North, South, East, West, Up, Down)
- **Isometric Rendering Engine**: Beautiful 3D-like graphics in 2D
- **Multiplayer Support**: Client-server architecture for online play
- **Custom Scripting**: Papyrus-like scripting language for game logic
- **Level Editor**: Visual editor for creating game worlds
- **Portable Setup**: Run directly from DVD/USB drive

### Components

#### 1. Server
- Handles multiplayer game state
- Manages client connections
- Processes movement and game logic
- Network protocol implementation
- Default port: 53000

#### 2. Client
- Isometric graphics rendering
- 6-directional movement controls
- Network communication with server
- Keyboard controls (WASD/Arrow keys + Q/E for vertical)
- Real-time multiplayer interaction

#### 3. Launcher/Updater
- Launch server, client, or editor
- Check for game updates
- Manage game versions
- User-friendly interface

#### 4. Editor
- Visual level editor
- Place and remove tiles
- Multi-layer support
- Save/load levels
- Script attachment
- Mouse-based tile placement

#### 5. Android Build
- Secondary Android build support
- Touch controls optimized
- Native Android integration

### Movement System

The game features a unique 6-degree movement system:
- **North** (W/Up Arrow): Move +Y
- **South** (S/Down Arrow): Move -Y
- **East** (D/Right Arrow): Move +X
- **West** (A/Left Arrow): Move -X
- **Up** (Q/Page Up): Move +Z (climb up)
- **Down** (E/Page Down): Move -Z (go down)

### Scripting System

Custom papyrus-like scripting language for game events:

```papyrus
; Example script
Event OnInit()
    Print("Welcome to the dungeon!")
EndEvent

Function OnPlayerEnter()
    Print("A player has entered!")
EndFunction
```

## Quick Start

### Building

See [BUILD.md](BUILD.md) for detailed build instructions.

Quick build:
```bash
mkdir build && cd build
cmake ..
cmake --build . --parallel
```

### Running

Start server:
```bash
./build/Server/Server
```

Start client (in another terminal):
```bash
./build/Client/Client
```

Start editor:
```bash
./build/Editor/Editor
```

### Portable Distribution

Create a portable package for DVD/USB:
```bash
cd Setup
./build-portable.sh
```

Then extract the generated ZIP to removable media and run:
- Windows: `Run.bat`
- Linux/Mac: `./Run.sh`

## Controls

### Client
- **W/↑** - Move North
- **S/↓** - Move South  
- **D/→** - Move East
- **A/←** - Move West
- **Q/Page Up** - Move Up (climb)
- **E/Page Down** - Move Down (descend)

### Editor
- **1-5** - Select tile type
- **Left Click** - Place tile
- **Right Click** - Remove tile
- **Page Up/Down** - Change layer (Z-level)
- **Ctrl+S** - Save level
- **Ctrl+L** - Load level
- **Ctrl+N** - New level
- **ESC** - Exit

## Architecture

### Technology Stack
- **Language**: C++17
- **Graphics**: SFML 2.5+
- **Build System**: CMake 3.16+
- **Platforms**: Windows, Linux, macOS, Android

### Project Structure
```
├── Common/          # Shared code (engine, movement, networking)
├── Server/          # Server component
├── Client/          # Client component
├── Launcher/        # Launcher/Updater
├── Editor/          # Level editor
├── Android/         # Android build configuration
└── Setup/           # Portable setup system
```

### Key Classes
- `Vector3D` - 3D position vector
- `Movement` - 6-directional movement system
- `IsometricEngine` - Isometric rendering engine
- `NetworkProtocol` - Client-server communication
- `ScriptEngine` - Custom scripting system
- `TileEditor` - Level editing functionality

## Development

### Requirements
- CMake 3.16+
- C++17 compiler
- SFML 2.5+
- Android NDK (for Android builds)

### Building Components

Build specific components:
```bash
cmake .. -DBUILD_SERVER=ON -DBUILD_CLIENT=ON -DBUILD_EDITOR=ON
```

Build for Android:
```bash
cmake .. -DBUILD_ANDROID=ON
```

### Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Build and test all components
5. Submit a pull request

## System Requirements

### Minimum
- OS: Windows 7+, Linux (kernel 3.0+), macOS 10.12+, Android 5.0+
- RAM: 512 MB
- Graphics: OpenGL 2.1 compatible
- Disk: 100 MB

### Recommended
- OS: Windows 10+, Ubuntu 20.04+, macOS 11+, Android 9.0+
- RAM: 2 GB
- Graphics: OpenGL 3.3+ compatible
- Disk: 500 MB

## License

[Add your license information here]

## Credits

Developed using:
- SFML - Simple and Fast Multimedia Library
- CMake - Cross-platform build system

## Support

For issues, questions, or contributions, please visit the project repository.

---

**Isometric Graphic Multiplayer Dungeon** - A modern take on classic MUDs with beautiful isometric graphics!
