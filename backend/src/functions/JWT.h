#pragma once

#include <string>

std::string generate_token(const std::string& username);
bool verify_token(const std::string& token, std::string& username);
