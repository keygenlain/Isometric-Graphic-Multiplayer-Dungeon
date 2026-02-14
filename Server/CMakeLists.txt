add_executable(Server
    src/main.cpp
    src/GameServer.cpp
)

target_include_directories(Server PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Server PRIVATE
    Common
    sfml-network
    sfml-system
)
