#include "GameClient.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    std::string serverAddress = "127.0.0.1";
    unsigned short port = 53000;
    
    if (argc > 1) {
        serverAddress = argv[1];
    }
    if (argc > 2) {
        try {
            int portNum = std::stoi(argv[2]);
            if (portNum < 1 || portNum > 65535) {
                std::cerr << "Error: Port must be between 1 and 65535" << std::endl;
                return 1;
            }
            port = static_cast<unsigned short>(portNum);
        } catch (const std::exception& e) {
            std::cerr << "Error: Invalid port number '" << argv[2] << "'" << std::endl;
            std::cerr << "Usage: " << argv[0] << " [server_address] [port]" << std::endl;
            return 1;
        }
    }
    
    std::cout << "Isometric MUD Client" << std::endl;
    std::cout << "====================" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  W/Up    - Move North" << std::endl;
    std::cout << "  S/Down  - Move South" << std::endl;
    std::cout << "  D/Right - Move East" << std::endl;
    std::cout << "  A/Left  - Move West" << std::endl;
    std::cout << "  Q/PgUp  - Move Up" << std::endl;
    std::cout << "  E/PgDn  - Move Down" << std::endl;
    std::cout << std::endl;
    
    IsometricMUD::GameClient client;
    
    if (!client.initialize()) {
        std::cerr << "Failed to initialize client" << std::endl;
        return 1;
    }
    
    // Try to connect to server
    client.connect(serverAddress, port);
    
    client.run();
    
    return 0;
}
