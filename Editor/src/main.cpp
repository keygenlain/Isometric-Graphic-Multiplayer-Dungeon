#include "EditorApp.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "Isometric MUD Editor" << std::endl;
    std::cout << "====================" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  1-5         - Select tile type" << std::endl;
    std::cout << "  Left Click  - Place tile" << std::endl;
    std::cout << "  Right Click - Remove tile" << std::endl;
    std::cout << "  Page Up/Dn  - Change layer" << std::endl;
    std::cout << "  Ctrl+S      - Save level" << std::endl;
    std::cout << "  Ctrl+L      - Load level" << std::endl;
    std::cout << "  Ctrl+N      - New level" << std::endl;
    std::cout << "  ESC         - Exit" << std::endl;
    std::cout << std::endl;
    
    IsometricMUD::EditorApp editor;
    
    if (!editor.initialize()) {
        std::cerr << "Failed to initialize editor" << std::endl;
        return 1;
    }
    
    editor.run();
    
    return 0;
}
