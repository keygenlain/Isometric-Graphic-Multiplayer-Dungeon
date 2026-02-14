#!/bin/bash
# Build script for creating portable distribution package

echo "Building Isometric MUD Portable Package..."
echo ""

# Configuration
PACKAGE_NAME="IsometricMUD-Portable"
BUILD_DIR="build"
PACKAGE_DIR="$BUILD_DIR/$PACKAGE_NAME"

# Clean previous build
rm -rf "$BUILD_DIR"
mkdir -p "$PACKAGE_DIR"

# Create directory structure
mkdir -p "$PACKAGE_DIR/bin/lib"
mkdir -p "$PACKAGE_DIR/data/levels"
mkdir -p "$PACKAGE_DIR/data/scripts"
mkdir -p "$PACKAGE_DIR/data/assets"
mkdir -p "$PACKAGE_DIR/config"
mkdir -p "$PACKAGE_DIR/saves"

echo "Creating directory structure..."

# Copy executables (from CMake build output)
# Assuming CMake build was done in ../build
CMAKE_BUILD_DIR="../build"

if [ -d "$CMAKE_BUILD_DIR" ]; then
    echo "Copying executables from $CMAKE_BUILD_DIR..."
    
    # Copy executables
    [ -f "$CMAKE_BUILD_DIR/Client/Client" ] && cp "$CMAKE_BUILD_DIR/Client/Client" "$PACKAGE_DIR/bin/"
    [ -f "$CMAKE_BUILD_DIR/Server/Server" ] && cp "$CMAKE_BUILD_DIR/Server/Server" "$PACKAGE_DIR/bin/"
    [ -f "$CMAKE_BUILD_DIR/Editor/Editor" ] && cp "$CMAKE_BUILD_DIR/Editor/Editor" "$PACKAGE_DIR/bin/"
    [ -f "$CMAKE_BUILD_DIR/Launcher/Launcher" ] && cp "$CMAKE_BUILD_DIR/Launcher/Launcher" "$PACKAGE_DIR/bin/"
    
    echo "Executables copied."
else
    echo "WARNING: CMake build directory not found. Skipping executable copy."
    echo "Please build the project first with CMake."
fi

# Copy launcher scripts
echo "Copying launcher scripts..."
cp Run.sh "$PACKAGE_DIR/"
cp Run.bat "$PACKAGE_DIR/"
chmod +x "$PACKAGE_DIR/Run.sh"

# Copy documentation
echo "Copying documentation..."
cp README.md "$PACKAGE_DIR/"
cp ../README.md "$PACKAGE_DIR/README-Main.md"

# Create sample configuration file
echo "Creating sample configuration..."
cat > "$PACKAGE_DIR/config/game.cfg" << EOF
# Isometric MUD Configuration
# This file is automatically created and can be edited

[Graphics]
WindowWidth=1024
WindowHeight=768
Fullscreen=false
VSync=true

[Network]
DefaultServer=127.0.0.1
DefaultPort=53000

[Game]
PlayerName=Player1
AutoSave=true
EOF

# Create sample script
echo "Creating sample script..."
cat > "$PACKAGE_DIR/data/scripts/welcome.script" << EOF
; Isometric MUD Script Example
; Papyrus-like scripting language

Event OnInit()
    Print("Welcome to Isometric MUD!")
    Print("Press WASD to move, Q/E to go up/down")
EndEvent

Function Greet()
    Print("Hello, adventurer!")
EndFunction
EOF

# Create autorun.inf for DVD (Windows)
echo "Creating autorun.inf..."
cat > "$PACKAGE_DIR/autorun.inf" << EOF
[autorun]
open=Run.bat
icon=data/assets/icon.ico
label=Isometric MUD
action=Start Isometric MUD
EOF

# Create README for portable version
echo "Creating portable README..."
cat > "$PACKAGE_DIR/PORTABLE.txt" << EOF
Isometric MUD - Portable Edition
=================================

This is a portable version that can run directly from:
- DVD
- USB Drive
- External Hard Drive
- Any removable media

NO INSTALLATION REQUIRED!

WINDOWS:
--------
Double-click "Run.bat" to start the game.

LINUX/MAC:
----------
1. Open terminal in this directory
2. Run: chmod +x Run.sh
3. Run: ./Run.sh

FEATURES:
---------
- Runs from any location
- Saves are stored locally if writable
- Falls back to user profile if read-only
- Completely self-contained
- No registry changes
- No system modifications

SYSTEM REQUIREMENTS:
-------------------
- OS: Windows 7+, Linux (kernel 3.0+), macOS 10.12+
- RAM: 512 MB minimum
- Graphics: OpenGL 2.1 compatible
- Space: 100 MB available

For more information, see README.md

Enjoy your adventure!
EOF

# Copy libraries (this is platform-specific)
echo "Copying libraries..."
echo "NOTE: You need to manually copy SFML libraries to bin/lib/"
echo "      Platform-specific libraries must be included for distribution."

# Create a build info file
echo "Creating build info..."
cat > "$PACKAGE_DIR/BUILD_INFO.txt" << EOF
Build Date: $(date)
Build Type: Portable
Version: 1.0.0
Platform: Multi-platform (x64)

Components:
- Server
- Client  
- Editor
- Launcher

Features:
- 6-degree movement system
- Isometric rendering
- Multiplayer support
- Custom scripting (Papyrus-like)
- Level editor
- Portable setup (DVD/USB compatible)
EOF

# Create ZIP package
echo ""
echo "Creating ZIP package..."
cd "$BUILD_DIR"
zip -r "${PACKAGE_NAME}.zip" "$PACKAGE_NAME"
cd ..

echo ""
echo "==========================================="
echo "Portable package created successfully!"
echo "Location: $BUILD_DIR/${PACKAGE_NAME}.zip"
echo "==========================================="
echo ""
echo "To distribute:"
echo "1. Extract the ZIP to DVD/USB drive"
echo "2. Copy SFML libraries to bin/lib/"
echo "3. Copy game assets to data/assets/"
echo "4. Test on target platforms"
echo ""
echo "Package is ready for distribution!"
