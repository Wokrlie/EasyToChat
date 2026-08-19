#pragma once

#include <crow/http_request.h>
#include <crow/http_response.h>
#include <string>
#include <optional>

std::string generate_token(const std::string& username);
std::optional<std::string> verify_token(const std::string& token);

std::optional<std::string> verify_from_req(const crow::request& req);
