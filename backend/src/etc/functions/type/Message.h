#pragma once
#include <crow/websocket.h>
#include <string>
#include <uuid.h>

void broadcast_message(const std::string& msg, std::vector<crow::websocket::connection*> connections);

enum class SenderType {
    User = 0,
    System
};

struct Message {
    uuids::uuid id;
    SenderType sender_type;
    std::string sender_name;
    std::string content;
    std::string timestamp;
};
