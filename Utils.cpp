#include "Utils.h"
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>

namespace Utils {

    std::string sha256(const std::string& input) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);

        std::stringstream ss;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];

        return ss.str();
    }

    std::string generatePrivateKey(const std::string& seed) {
        return sha256("priv:" + seed);
    }

    std::string generatePublicKey(const std::string& privateKey) {
        return sha256("pub:" + privateKey);
    }

    std::string generateAddress(const std::string& publicKey) {
        return sha256("addr:" + publicKey).substr(0, 40); // raccourci pour lisibilité
    }

    std::string signData(const std::string& data, const std::string& privateKey) {
        return sha256(data + privateKey);
    }

    bool verifySignature(const std::string& data, const std::string& signature, const std::string& publicKey) {
        std::string fakePrivateKey = sha256("priv:" + publicKey);  // simulation
        std::string expectedSignature = sha256(data + fakePrivateKey);
        return expectedSignature == signature;
    }
}
