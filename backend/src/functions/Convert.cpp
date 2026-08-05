#include "Convert.h"
#include <string>

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

Gender string_to_gender(const std::string &value) {
    if (value == "male") return Gender::Male;
    if (value == "female") return Gender::Female;
    return Gender::KeepSecret; // As default value
}

std::string gender_to_string(Gender gender) {
    switch (gender) {
        case Gender::Male: return "male";
        case Gender::Female: return "female";
        case Gender::KeepSecret: return "keepSecret";
        default: return "keepSecret";
    }
}
