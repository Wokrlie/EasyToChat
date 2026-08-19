#include "JWT.h"
#include <jwt-cpp/jwt.h>
#include <chrono>
#include <optional>
#include <rtc/common.hpp>

static const std::string KEY_SECRET = "Hdsudux8zio2xcznh2u1";

std::string generate_token(const std::string &username) {
    auto token = jwt::create()
        .set_issuer("EasyToChat")
        .set_type("JWS")
        .set_payload_claim("username", jwt::claim(username))
        .set_issued_at(std::chrono::system_clock::now())
        .set_expires_at(std::chrono::system_clock::now() + std::chrono::hours{24})
        .sign(jwt::algorithm::hs256{KEY_SECRET})
    ;
    return token;
}

// The style which change value of paramter by reference is not approrite here
std::optional<std::string> verify_token(const std::string &token) {
    try {
        auto decoded = jwt::decode(token);
        auto verifyer = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{KEY_SECRET})
            .with_issuer("EasyToChat");
        verifyer.verify(decoded);
        return decoded.get_payload_claim("username").as_string();
    } catch (...) {
        return std::nullopt;
    }
}

std::optional<std::string> verify_from_req(const crow::request &req) {
    std::string auth_header = req.get_header_value("Authorization");
    if (auth_header.empty()) return std::nullopt;
    const std::string prefix = "Bearer ";
    if (auth_header.compare(0, prefix.size(), prefix) != 0) return std::nullopt;

    std::string token = auth_header.substr(prefix.size());
    auto username_opt = verify_token(token);
    if (!username_opt.has_value()) return std::nullopt;
    return username_opt;
}
