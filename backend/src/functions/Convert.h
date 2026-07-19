#pragma once
#include <string>
#include "../types/Message.h"

std::string sender_type_to_string(SenderType type);
SenderType string_to_sender_type(const std::string& value);
