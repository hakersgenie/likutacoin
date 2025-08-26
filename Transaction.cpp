#include "Transaction.h"
#include "Utils.h"

Transaction::Transaction(const std::string& from, const std::string& to, double amt)
    : sender(from), recipient(to), amount(amt) {}

void Transaction::signTransaction(const std::string& privateKey) {
    std::string data = sender + recipient + std::to_string(amount);
    signature = Utils::signData(data, privateKey);
}

bool Transaction::verifySignature() const {
    std::string data = sender + recipient + std::to_string(amount);
    return Utils::verifySignature(data, signature, senderPublicKey);
}

bool Transaction::isValid() const {
    if (sender == "network") return true;
    return verifySignature();
}

nlohmann::json Transaction::to_json() const {
    return {
        {"sender", sender},
        {"recipient", recipient},
        {"amount", amount},
        {"fee", fee},
        {"senderPublicKey", senderPublicKey},
        {"signature", signature}
    };
}

Transaction Transaction::from_json(const nlohmann::json& j) {
    Transaction tx(j["sender"], j["recipient"], j["amount"]);
    tx.fee = j["fee"];
    tx.senderPublicKey = j["senderPublicKey"];
    tx.signature = j["signature"];
    return tx;
}
