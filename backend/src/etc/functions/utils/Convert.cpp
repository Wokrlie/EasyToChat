#include "Convert.h"
#include <stdexcept>
#include <string>
#include <uuid.h>

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



std::string converID_to_string(ConverID id) {
    return id.to_string();
}

ConverID string_to_converID(const std::string& value) {
    auto result = uuids::uuid::from_string(value);
    ConverID rst;
    if (!result)
    {
        throw std::runtime_error("Failed to convert value to ConverID");
    }
    rst.id = *result;
    return rst;
}
