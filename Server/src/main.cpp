#include "GameServer.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    unsigned short port = 53000;
    
    if (argc > 1) {
        port = static_cast<unsigned short>(std::stoi(argv[1]));
    }
    
    std::cout << "Isometric MUD Server" << std::endl;
    std::cout << "===================" << std::endl;
    
    IsometricMUD::GameServer server;
    
    if (!server.start(port)) {
        std::cerr << "Failed to start server" << std::endl;
        return 1;
    }
    
    std::cout << "Server running. Press Ctrl+C to stop." << std::endl;
    server.run();
    
    return 0;
}
