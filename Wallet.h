#ifndef WALLET_H
#define WALLET_H

#include <string>

class Wallet {
public:
    std::string privateKey;
    std::string publicKey;
    std::string address;

    Wallet(const std::string& name);
};

#endif
