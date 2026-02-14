# Android Build Configuration
cmake_minimum_required(VERSION 3.16)

# Android specific settings
if(ANDROID)
    # Add Android-specific sources
    add_library(IsometricMUD_Android SHARED
        ../Client/src/GameClient.cpp
        android_main.cpp
    )

    target_include_directories(IsometricMUD_Android PRIVATE
        ../Client/include
        ../Common/include
    )

    target_link_libraries(IsometricMUD_Android PRIVATE
        Common
        sfml-graphics
        sfml-window
        sfml-system
        sfml-network
        android
        log
    )
endif()
