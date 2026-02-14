add_executable(Client
    src/main.cpp
    src/GameClient.cpp
)

target_include_directories(Client PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Client PRIVATE
    Common
    sfml-graphics
    sfml-window
    sfml-system
    sfml-network
)
