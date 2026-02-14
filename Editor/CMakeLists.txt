add_executable(Editor
    src/main.cpp
    src/EditorApp.cpp
    src/TileEditor.cpp
)

target_include_directories(Editor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Editor PRIVATE
    Common
    sfml-graphics
    sfml-window
    sfml-system
)
