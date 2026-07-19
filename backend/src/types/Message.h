#pragma once
#include <string>

enum class SenderType {
    User = 0,
    System
};
struct Message {
    int id;
    SenderType sender_type;
    std::string sender_name;
    std::string content;
    std::string timestamp;
};
