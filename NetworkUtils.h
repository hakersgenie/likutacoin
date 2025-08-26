#ifndef NETWORK_UTILS_H
#define NETWORK_UTILS_H

#include "Network.h"
#include "Transaction.h"
#include "json.hpp"

void broadcast_transaction(Network& net, const Transaction& tx) {
    nlohmann::json j;
    j["type"] = "transaction";
    j["data"] = tx.to_json();

    // À adapter selon ta liste de peers
    // Par exemple :
    // for (const auto& peer : peers) {
    //     net.send_message(peer.ip, peer.port, j.dump());
    // }
    std::cout << "🌐 Diffusion de la transaction : " << j.dump() << "\n";
}

#endif
