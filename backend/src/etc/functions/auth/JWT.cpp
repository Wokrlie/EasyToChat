#include "JWT.h"
#include <jwt-cpp/jwt.h>
#include <chrono>
#include <optional>

#include <jwt-cpp/traits/nlohmann-json/traits.h>

static const std::string KEY_SECRET = "Hdsudux8zio2xcznh2u1";
using traits = jwt::traits::nlohmann_json;
using claim = jwt::basic_claim<traits>;

std::string generate_token(const std::string &username) {
    auto token = jwt::create<traits>()
        .set_issuer("EasyToChat")
        .set_type("JWS")
        .set_payload_claim("username", claim(username))
        .set_issued_at(std::chrono::system_clock::now())
        .set_expires_at(std::chrono::system_clock::now() + std::chrono::hours{12})
        .sign(jwt::algorithm::hs256{KEY_SECRET})
    ;
    return token;
}

// The style which change value of paramter by reference is not approrite here
std::optional<std::string> verify_token(const std::string &token) {
    try {
        auto decoded = jwt::decode<traits>(token);
        auto verifyer = jwt::verify<traits>()
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
