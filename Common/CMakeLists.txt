add_library(Common STATIC
    src/Vector3D.cpp
    src/IsometricEngine.cpp
    src/Movement.cpp
    src/NetworkProtocol.cpp
    src/ScriptEngine.cpp
)

target_include_directories(Common PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Common PUBLIC
    sfml-graphics
    sfml-window
    sfml-system
    sfml-network
)
