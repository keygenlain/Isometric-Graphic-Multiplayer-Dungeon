#include "LauncherApp.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "Isometric MUD Launcher" << std::endl;
    std::cout << "======================" << std::endl;
    std::cout << "Press 1 to launch Client" << std::endl;
    std::cout << "Press 2 to launch Server" << std::endl;
    std::cout << "Press 3 to launch Editor" << std::endl;
    std::cout << "Press ESC to exit" << std::endl;
    std::cout << std::endl;
    
    IsometricMUD::LauncherApp launcher;
    
    if (!launcher.initialize()) {
        std::cerr << "Failed to initialize launcher" << std::endl;
        return 1;
    }
    
    launcher.run();
    
    return 0;
}
