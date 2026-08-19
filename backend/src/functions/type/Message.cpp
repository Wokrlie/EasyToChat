#include "Message.h"
#include <vector>

void broadcast_message(const std::string& msg, std::vector<crow::websocket::connection*> connections) {
    for (auto conn : connections) {
        if (conn) conn->send_text(msg);
    }
}
