#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <vector>
#include "Block.h"

class Blockchain {
private:
    std::vector<Block> chain;
    int difficulty;

public:
    Blockchain();

    void addBlock(const std::vector<Transaction>& transactions, const std::string& minerAddress);
    Block createGenesisBlock();
    Block getLastBlock() const;
    bool isChainValid() const;
    void printChain() const;
    double getBalanceOfAddress(const std::string& address) const;
};

#endif
