add_executable(Launcher
    src/main.cpp
    src/LauncherApp.cpp
    src/Updater.cpp
)

target_include_directories(Launcher PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Launcher PRIVATE
    Common
    sfml-graphics
    sfml-window
    sfml-system
    sfml-network
)
