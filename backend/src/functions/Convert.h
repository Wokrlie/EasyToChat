#pragma once
#include <string>
#include "../types/Message.h"
#include "../types/User.h"

std::string sender_type_to_string(SenderType type);
SenderType string_to_sender_type(const std::string& value);

Gender string_to_gender(const std::string& value);
std::string gender_to_string(Gender gender);
