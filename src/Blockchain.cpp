#include "Blockchain.h"
#include "Utils.h"
#include <iostream>
#include <ctime>

Blockchain::Blockchain() : difficulty(2) {
    chain.push_back(createGenesisBlock());
}

Block Blockchain::createGenesisBlock() {
    Transaction genesisTx("network", "root10", 1000000);
    std::vector<Transaction> genesisTxs = {genesisTx};
    Block genesis(0, std::time(nullptr), genesisTxs, "0", "network");
    genesis.mineBlock(difficulty);
    return genesis;
}

Block Blockchain::getLastBlock() const {
    return chain.back();
}

void Blockchain::addBlock(const std::vector<Transaction>& transactions, const std::string& minerAddress) {
    Block newBlock(chain.size(), std::time(nullptr), transactions, getLastBlock().getHash(), minerAddress);
    newBlock.mineBlock(difficulty);
    chain.push_back(newBlock);
}

bool Blockchain::isChainValid() const {
    for (size_t i = 1; i < chain.size(); ++i) {
        const Block& current = chain[i];
        const Block& previous = chain[i - 1];

        if (!current.hasValidTransactions()) return false;
        if (current.getHash() != current.calculateHash()) return false;
        if (current.getPreviousHash() != previous.getHash()) return false;
    }
    return true;
}

void Blockchain::printChain() const {
    for (const auto& block : chain) {
        std::cout << "---------------------------\n";
        std::cout << "Hash        : " << block.getHash() << "\n";
        std::cout << "Précédent   : " << block.getPreviousHash() << "\n";
        std::cout << "Mineur      : " << block.getMinerAddress() << "\n";
        std::cout << "Transactions:\n";
        for (const auto& tx : block.getTransactions()) {
            std::cout << "  " << tx.sender << " -> " << tx.recipient << " : " << tx.amount << "\n";
        }
    }
}

double Blockchain::getBalanceOfAddress(const std::string& address) const {
    double balance = 0.0;
    for (const auto& block : chain) {
        for (const auto& tx : block.getTransactions()) {
            if (tx.sender == address) {
                balance -= tx.amount;
            }
            if (tx.recipient == address) {
                balance += tx.amount;
            }
        }
    }
    return balance;
}
