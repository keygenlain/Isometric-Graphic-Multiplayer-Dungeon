# Isometric MUD - Portable Setup System

This setup system allows the game to run directly from DVD/USB drive without installation.

## Features
- Runs directly from removable media
- No installation required
- Portable settings and save files
- Self-contained dependencies

## Structure
```
IsometricMUD/
├── Run.bat / Run.sh      - Main launcher script
├── bin/                  - Executables and libraries
│   ├── Client.exe / Client
│   ├── Server.exe / Server
│   ├── Editor.exe / Editor
│   ├── Launcher.exe / Launcher
│   └── lib/             - SFML and other libraries
├── data/                - Game data
│   ├── levels/
│   ├── scripts/
│   └── assets/
├── config/              - Configuration files (user writable)
└── saves/               - Save games (user writable)
```

## Usage

### Windows
Double-click `Run.bat` to start the launcher.

### Linux/Mac
```bash
chmod +x Run.sh
./Run.sh
```

## Building Portable Package

Run the build script:
```bash
cd Setup
./build-portable.sh
```

This will create a `IsometricMUD-Portable.zip` package ready for DVD/USB distribution.
