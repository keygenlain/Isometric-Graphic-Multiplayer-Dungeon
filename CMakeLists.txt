cmake_minimum_required(VERSION 3.16)
project(IsometricMUD VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options for building different components
option(BUILD_SERVER "Build the server component" ON)
option(BUILD_CLIENT "Build the client component" ON)
option(BUILD_LAUNCHER "Build the launcher/updater component" ON)
option(BUILD_EDITOR "Build the game editor component" ON)
option(BUILD_ANDROID "Build Android version" OFF)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system network REQUIRED)

# Add subdirectories
add_subdirectory(Common)

if(BUILD_SERVER)
    add_subdirectory(Server)
endif()

if(BUILD_CLIENT)
    add_subdirectory(Client)
endif()

if(BUILD_LAUNCHER)
    add_subdirectory(Launcher)
endif()

if(BUILD_EDITOR)
    add_subdirectory(Editor)
endif()

if(BUILD_ANDROID)
    add_subdirectory(Android)
endif()
