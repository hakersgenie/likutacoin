#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace Utils {
    std::string sha256(const std::string& input);
    std::string generatePrivateKey(const std::string& seed);
    std::string generatePublicKey(const std::string& privateKey);
    std::string generateAddress(const std::string& publicKey);

    std::string signData(const std::string& data, const std::string& privateKey);
    bool verifySignature(const std::string& data, const std::string& signature, const std::string& publicKey);
}

#endif
