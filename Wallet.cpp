#include "Wallet.h"
#include "Utils.h"

Wallet::Wallet(const std::string& name) {
    privateKey = Utils::generatePrivateKey(name);
    publicKey = Utils::generatePublicKey(privateKey);
    address = Utils::generateAddress(publicKey);
}
