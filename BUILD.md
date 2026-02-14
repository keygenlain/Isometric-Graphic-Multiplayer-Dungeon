# Build Instructions

## Prerequisites

### All Platforms
- CMake 3.16 or higher
- C++17 compatible compiler
- SFML 2.5 or higher

### Windows
- Visual Studio 2019 or higher, or MinGW
- Windows SDK

### Linux
- GCC 7+ or Clang 5+
- X11 development libraries
- OpenGL development libraries

### macOS
- Xcode Command Line Tools
- Homebrew (recommended for dependencies)

### Android
- Android NDK r21 or higher
- Android SDK API level 21+
- CMake with Android support

## Installing Dependencies

### Windows
Download and install SFML from https://www.sfml-dev.org/download.php
Or use vcpkg:
```powershell
vcpkg install sfml
```

### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install build-essential cmake
sudo apt-get install libsfml-dev
```

### Linux (Fedora)
```bash
sudo dnf install cmake gcc-c++
sudo dnf install SFML-devel
```

### macOS
```bash
brew install cmake sfml
```

## Building the Project

### Desktop (Windows/Linux/macOS)

1. Clone the repository:
```bash
git clone <repository-url>
cd Isometric-Graphic-Multiplayer-Dungeon
```

2. Create build directory:
```bash
mkdir build
cd build
```

3. Configure with CMake:
```bash
cmake ..
```

Or with specific options:
```bash
cmake .. -DBUILD_SERVER=ON -DBUILD_CLIENT=ON -DBUILD_LAUNCHER=ON -DBUILD_EDITOR=ON
```

4. Build:
```bash
cmake --build . --parallel
```

Or on Windows with Visual Studio:
```bash
cmake --build . --config Release
```

### Android Build

1. Set environment variables:
```bash
export ANDROID_SDK_ROOT=/path/to/android/sdk
export ANDROID_NDK_ROOT=/path/to/android/ndk
```

2. Run Android build script:
```bash
cd Android
./build-android.sh
```

Or manually:
```bash
mkdir build-android
cd build-android
cmake .. \
    -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK_ROOT/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI=arm64-v8a \
    -DANDROID_PLATFORM=android-21 \
    -DBUILD_ANDROID=ON
cmake --build .
```

## Building Portable Package

To create a portable distribution that can run from DVD/USB:

```bash
cd Setup
./build-portable.sh
```

This creates `IsometricMUD-Portable.zip` with:
- All executables
- Required libraries
- Launcher scripts (Run.bat/Run.sh)
- Sample configuration
- Documentation

## CMake Build Options

- `BUILD_SERVER` - Build server component (default: ON)
- `BUILD_CLIENT` - Build client component (default: ON)
- `BUILD_LAUNCHER` - Build launcher/updater (default: ON)
- `BUILD_EDITOR` - Build game editor (default: ON)
- `BUILD_ANDROID` - Build Android version (default: OFF)

Example:
```bash
cmake .. -DBUILD_SERVER=OFF -DBUILD_ANDROID=ON
```

## Running the Components

### Server
```bash
./Server [port]
# Default port: 53000
```

### Client
```bash
./Client [server_address] [port]
# Default: 127.0.0.1:53000
```

### Editor
```bash
./Editor
```

### Launcher
```bash
./Launcher
```

## Troubleshooting

### SFML Not Found
If CMake cannot find SFML:
```bash
cmake .. -DSFML_DIR=/path/to/sfml/lib/cmake/SFML
```

### Missing OpenGL Libraries (Linux)
```bash
sudo apt-get install libgl1-mesa-dev libglu1-mesa-dev
```

### Build Errors on Windows
Make sure you're using the correct generator:
```bash
cmake .. -G "Visual Studio 16 2019"
```

### Android Build Issues
Ensure NDK and SDK paths are correctly set:
```bash
echo $ANDROID_NDK_ROOT
echo $ANDROID_SDK_ROOT
```

## Development

### Debug Build
```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build .
```

### Release Build
```bash
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

### Running Tests
```bash
cmake --build . --target test
```

## Project Structure

```
Isometric-Graphic-Multiplayer-Dungeon/
├── CMakeLists.txt          - Main CMake configuration
├── Common/                 - Shared code library
│   ├── include/           - Header files
│   └── src/               - Source files
├── Server/                 - Server component
├── Client/                 - Client component
├── Launcher/               - Launcher/Updater
├── Editor/                 - Game editor
├── Android/                - Android build
├── Setup/                  - Portable setup system
└── README.md              - Main documentation
```

## Next Steps

After building:
1. Test each component individually
2. Run server and client to test multiplayer
3. Use editor to create levels
4. Build portable package for distribution
5. Test Android build on device/emulator
