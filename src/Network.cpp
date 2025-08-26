#include "Network.h"
#include <iostream>

Network::Network(int p) : port(p) {}

void Network::send_message(const std::string& ip, int port, const std::string& message) {
    std::cout << "📤 Message envoyé à " << ip << ":" << port << " : " << message << "\n";
}

void Network::listen(void (*onMessage)(const std::string&)) {
    std::cout << "🛠️  Écoute réseau activée sur le port " << port << "...\n";
    // Simulation : pas de vrai réseau ici
}
