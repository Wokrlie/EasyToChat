#pragma once
#include <string>
#include "../type/Message.h"
#include "../type/User.h"
#include "../type/Conver.h"

std::string sender_type_to_string(SenderType type);
SenderType string_to_sender_type(const std::string& value);

Gender string_to_gender(const std::string& value);
std::string gender_to_string(const Gender gender);


std::string converID_to_string(ConverID id);
ConverID string_to_converID(const std::string& value);
