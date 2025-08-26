#include "Block.h"
#include "Utils.h"

Block::Block(int idx, long time, std::vector<Transaction> txs, const std::string& prevHash, const std::string& miner)
    : index(idx), timestamp(time), transactions(txs), previousHash(prevHash), minerAddress(miner), nonce(0) {
    hash = calculateHash();
}

std::string Block::calculateHash() const {
    std::string data = std::to_string(index) + std::to_string(timestamp) + previousHash + minerAddress + std::to_string(nonce);
    for (const auto& tx : transactions) {
        data += tx.sender + tx.recipient + std::to_string(tx.amount);
    }
    return Utils::sha256(data);
}

void Block::mineBlock(int difficulty) {
    std::string target(difficulty, '0');
    while (hash.substr(0, difficulty) != target) {
        nonce++;
        hash = calculateHash();
    }
}

bool Block::hasValidTransactions() const {
    for (const auto& tx : transactions) {
        if (!tx.isValid()) return false;
    }
    return true;
}

std::string Block::getHash() const {
    return hash;
}

std::string Block::getPreviousHash() const {
    return previousHash;
}

std::vector<Transaction> Block::getTransactions() const {
    return transactions;
}

std::string Block::getMinerAddress() const {
    return minerAddress;
}

nlohmann::json Block::to_json() const {
    nlohmann::json j;
    j["index"] = index;
    j["timestamp"] = timestamp;
    j["transactions"] = nlohmann::json::array();
    for (const auto& tx : transactions) {
        j["transactions"].push_back(tx.to_json());
    }
    j["previousHash"] = previousHash;
    j["hash"] = hash;
    j["minerAddress"] = minerAddress;
    j["nonce"] = nonce;
    return j;
}

Block Block::from_json(const nlohmann::json& j) {
    std::vector<Transaction> txs;
    for (const auto& item : j["transactions"]) {
        txs.push_back(Transaction::from_json(item));
    }

    Block b(j["index"], j["timestamp"], txs, j["previousHash"], j["minerAddress"]);
    b.hash = j["hash"];
    b.nonce = j["nonce"];
    return b;
}
