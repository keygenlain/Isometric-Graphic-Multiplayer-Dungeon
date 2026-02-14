#!/bin/bash
# Isometric MUD Portable Launcher for Linux/Mac
# This script runs the game from the current directory (DVD/USB)

echo "=========================================="
echo "Isometric MUD - Portable Edition"
echo "=========================================="
echo ""

# Get the directory where this script is located
GAME_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Set paths relative to script location
BIN_DIR="$GAME_DIR/bin"
DATA_DIR="$GAME_DIR/data"
CONFIG_DIR="$GAME_DIR/config"
SAVES_DIR="$GAME_DIR/saves"

# Create user-writable directories if they don't exist
mkdir -p "$CONFIG_DIR" 2>/dev/null
mkdir -p "$SAVES_DIR" 2>/dev/null

# Set environment variables for portable mode
export ISOMETRIC_MUD_PORTABLE=1
export ISOMETRIC_MUD_ROOT="$GAME_DIR"
export ISOMETRIC_MUD_DATA="$DATA_DIR"
export ISOMETRIC_MUD_CONFIG="$CONFIG_DIR"
export ISOMETRIC_MUD_SAVES="$SAVES_DIR"

# Add bin directory to library path
export LD_LIBRARY_PATH="$BIN_DIR/lib:$LD_LIBRARY_PATH"
export DYLD_LIBRARY_PATH="$BIN_DIR/lib:$DYLD_LIBRARY_PATH"  # For macOS

echo "Game directory: $GAME_DIR"
echo ""

# Check if running from read-only media (DVD)
if ! touch "$GAME_DIR/test_write.tmp" 2>/dev/null; then
    echo "WARNING: Running from read-only media."
    echo "Save files will be stored in your home directory."
    echo ""
    # Fallback to home directory for saves
    CONFIG_DIR="$HOME/.isometricmud/config"
    SAVES_DIR="$HOME/.isometricmud/saves"
    mkdir -p "$CONFIG_DIR"
    mkdir -p "$SAVES_DIR"
    export ISOMETRIC_MUD_CONFIG="$CONFIG_DIR"
    export ISOMETRIC_MUD_SAVES="$SAVES_DIR"
else
    rm -f "$GAME_DIR/test_write.tmp"
fi

echo "Starting Launcher..."
echo ""

# Launch the game launcher
if [ -f "$BIN_DIR/Launcher" ]; then
    cd "$BIN_DIR"
    ./Launcher
else
    echo "ERROR: Launcher not found in $BIN_DIR"
    echo "Please ensure the game is properly installed."
    exit 1
fi

echo ""
echo "Game closed."
