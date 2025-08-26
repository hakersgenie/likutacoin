#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <string>
#include "Transaction.h"
#include "json.hpp"

class Block {
private:
    int index;
    long timestamp;
    std::vector<Transaction> transactions;
    std::string previousHash;
    std::string hash;
    std::string minerAddress;
    int nonce;

public:
    Block(int idx, long time, std::vector<Transaction> txs, const std::string& prevHash, const std::string& miner);

    std::string calculateHash() const;
    void mineBlock(int difficulty);
    bool hasValidTransactions() const;

    std::string getHash() const;
    std::string getPreviousHash() const;
    std::vector<Transaction> getTransactions() const;
    std::string getMinerAddress() const;

    nlohmann::json to_json() const;
    static Block from_json(const nlohmann::json& j);
};

#endif
