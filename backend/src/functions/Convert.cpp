#include "Convert.h"

std::string sender_type_to_string(SenderType type) {
    switch (type) {
        case SenderType::User: return "user";
        case SenderType::System: return "system";
        default: return "unknown";
    }
}

SenderType string_to_sender_type(const std::string& value) {
    if (value == "user") return SenderType::User;
    if (value == "system") return SenderType::System;
    return SenderType::User;
}
