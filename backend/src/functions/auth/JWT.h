#pragma once

#include <string>
#include <optional>

std::string generate_token(const std::string& username);
std::optional<std::string> verify_token(const std::string& token);
