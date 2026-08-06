#include "JWT.h"
#include <jwt-cpp/jwt.h>
#include <chrono>

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

bool verify_token(const std::string &token, std::string &username) {
    try {
        auto decoded = jwt::decode(token);
        auto verifyer = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{KEY_SECRET})
            .with_issuer("EasyToChat");
        verifyer.verify(decoded);
        username = decoded.get_payload_claim("username").as_string();
        return true;
    } catch (...) {
        return false;
    }
}
