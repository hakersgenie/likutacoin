#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <vector>

struct Peer {
    std::string ip;
    int port;
};

class Network {
public:
    int port;

    Network(int p);

    void send_message(const std::string& ip, int port, const std::string& message);
    void listen(void (*onMessage)(const std::string&));
};

#endif
