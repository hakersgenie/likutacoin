#include "Blockchain.h"
#include "Wallet.h"
#include "Network.h"
#include "NetworkUtils.h"
#include "Utils.h"
#include <iostream>
#include <map>
#include <vector>
#include "json.hpp"
#include "toUpper.h"

using json = nlohmann::json;

Network network(12345);
std::vector<Transaction> mempool;
Blockchain likuta;
std::vector<Peer> peers;
Blockchain
// Validation des transactions
bool validate_transaction(const Transaction& tx) {
    return tx.isValid();
}

// Validation basique des blocs
bool validate_block(const Block& b) {
    const Block& lastBlock = likuta.getLastBlock();
    return b.getPreviousHash() == lastBlock.getHash() && b.hasValidTransactions();
}

// Diffusion d’un nouveau bloc aux pairs
void broadcast_block(const Block& block) {
    json j;
    j["type"] = "block";
    j["data"] = block.to_json();
    for (const auto& peer : peers) {
        network.send_message(peer.ip, peer.port, j.dump());
    }Blockchain
}

// Gestion des messages réseau (transactions/blocs reçus)
void handle_message(const std::string& msg) {
    try {
        auto j = json::parse(msg);
        std::string type = j["type"];
        if (type == "transaction") {
            Transaction tx = Transaction::from_json(j["data"]);
            if (validate_transaction(tx)) {
                mempool.push_back(tx);
                broadcast_transaction(network, tx);
            }
        } else if (type == "block") {
            Block b = Block::from_json(j["data"]);
            if (validate_block(b)) {
                likuta.addBlock(b.getTransactions(), b.getMinerAddress());
                broadcast_block(b);
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Erreur traitement message réseau : " << e.what() << std::endl;
    }
}

int main() {

    std::cout << "=== Lancement du nœud Likuta ===\n";

    Wallet root10("root10");
    std::cout << "Adresse de root10 : " << root10.address << "\n";

    Wallet bob("Bob");
    std::cout << "Adresse de Bob    : " << bob.address << "\n";

    // === 1. Création du bloc génésis (coinbase) ===
    Transaction genesisTx("network", root10.address, 1000000);

    if (!genesisTx.isValid()) {
        std::cerr << "Erreur : transaction initiale invalide\n";
        return 1;
    }
    likuta.addBlock({ genesisTx }, "network");

    std::map<std::string, Wallet> wallets;
    wallets[root10.address] = root10;
    wallets[bob.address] = bob;

    std::cout << "Solde initial root10 : " << likuta.getBalanceOfAddress(root10.address) << "\n";
    std::cout << "Solde initial Bob    : " << likuta.getBalanceOfAddress(bob.address) << "\n";

    // === 2. Première transaction root10 → Bob ===
    Transaction tx1(root10.address, bob.address, 10);
    tx1.senderPublicKey = root10.publicKey;
    tx1.signTransaction(root10.privateKey);

    if (tx1.verifySignature()) {
        std::vector<Transaction> blockTxs = {tx1};
        double totalFees = tx1.fee;
        Transaction rewardTx("network", root10.address, totalFees + 50);
        blockTxs.push_back(rewardTx);
        likuta.addBlock(blockTxs, root10.address);
    } else {
        std::cout << "❌ Signature invalide !\n";
    }

    // === 4. Résultat final ===
    std::cout << "\n=== Chaîne finale ===\n";
    likuta.printChain();
    std::cout << "\nChaîne valide : " << (likuta.isChainValid() ? "Oui ✅" : "Non ❌") << "\n";
    std::cout << "Solde final root10 : " << likuta.getBalanceOfAddress(root10.address) << "\n";
    std::cout << "Solde final Bob    : " << likuta.getBalanceOfAddress(bob.address) << "\n";

    std::cout << "\nAppuyez sur Entrée pour quitter...";
    std::string dummy;
    std::getline(std::cin, dummy);
    return 0;
}
