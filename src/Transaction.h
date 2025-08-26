#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "json.hpp"

class Transaction {
public:
    std::string sender;
    std::string recipient;
    double amount;
    double fee = 0.1;

    std::string senderPublicKey;
    std::string signature;

    Transaction(const std::string& from, const std::string& to, double amount);

    void signTransaction(const std::string& privateKey);
    bool verifySignature() const;
    bool isValid() const;

    nlohmann::json to_json() const;
    static Transaction from_json(const nlohmann::json& j);
};

#endif
