#include "Backend.h"
#include "functions/Conver.h"
#include "functions/auth/UUID.h"
#include "functions/UserDataWS.h"
#include <crow/json.h>
#include <crow/logging.h>
#include <uuid.h>

Backend::Backend() {
    std::filesystem::path staticDir = getStaticDir();
    CROW_ROUTE(app, "/")
        ([&]() {
            crow::response res;
            res.set_static_file_info((staticDir / "index.html").string());
            return res;
        });

    CROW_ROUTE(app, "/api/ping")
        ([]() {
            return crow::response("pong");
        });

    CROW_ROUTE(app, "/api/messages")
        ([&](const crow::request& req) {
            std::string auth_header = req.get_header_value("Authorization");
            if (auth_header.empty()) return crow::response(401, "Missing Authorization header");
            const std::string prefix = "Bearer ";
            if (auth_header.compare(0, prefix.size(), prefix) != 0) return crow::response(401, "Invalid Authorization format");

            std::string token = auth_header.substr(prefix.size());
            auto username_opt = verify_token(token);
            if (!username_opt.has_value()) return crow::response(401, "Invalid token");

            auto body = crow::json::load(req.body);
            if (!body.has("conver_id")) return crow::response(400, "Missing field: conver_id");
            Conver conver = g_conversations.find(body["conver_id"].s())->second;

            std::lock_guard<std::mutex> lock(g_conver_mutex);
            std::vector<crow::json::wvalue> json_messages;
            for (const auto& msg : conver.get_message()) {
                crow::json::wvalue json_msg;
                json_msg["id"] = uuids::to_string(msg.id);
                json_msg["sender_type"] = sender_type_to_string(msg.sender_type);
                json_msg["sender_name"] = msg.sender_name;
                json_msg["content"] = msg.content;
                json_msg["timestamp"] = msg.timestamp;
                json_messages.push_back(std::move(json_msg));
            }

            crow::json::wvalue result;
            result = std::move(json_messages);
            return crow::response(200, result);
        });
    CROW_ROUTE(app, "/api/messages").methods(crow::HTTPMethod::Post)
        ([&](const crow::request& req) {
            std::string auth_header = req.get_header_value("Authorization");
            if (auth_header.empty()) return crow::response(401, "Missing Authorization header");
            const std::string prefix = "Bearer ";
            if (auth_header.compare(0, prefix.size(), prefix) != 0) return crow::response(401, "Invalid Authorization format");

            std::string token = auth_header.substr(prefix.size());
            auto username_opt = verify_token(token);
            if (!username_opt.has_value()) return crow::response(401, "Invalid token");


            if (!verify_token(token).has_value()) return crow::response(401, "Invaild token");

            CROW_LOG_DEBUG << "Received POST body: " << req.body;
            auto body = crow::json::load(req.body);
            if (!body) {
                return crow::response(400, "Invaild JSON");
            }

            if (!body.has("content")
                || !body.has("sender_type")
                || !body.has("sender_name")
                || !body.has("conver_id")
            ) {
                return crow::response(400, "Failed because of omissions of paramters.");
            }


            std::string content = body["content"].s();
            std::string sender_type_str = body["sender_type"].s();
            std::string sender_name = body["sender_name"].s();
            SenderType sender_type = string_to_sender_type(sender_type_str);

            std::string conver_id = body["conver_id"].s();
            {
                std::lock_guard<std::mutex> lock(g_conver_mutex);
                Conver conver = g_conversations.find(body["conver_id"].s())->second;

                Message msg{
                    UUIDGenerator::instance().generate(),
                    sender_type,
                    sender_name,
                    content,
                    get_current_time()
                };

                conver.receive_message(msg);
            }

            crow::json::wvalue broadcast_msg;
            broadcast_msg["type"] = "new_msg";
            broadcast_message(broadcast_msg.dump(), g_connections.find(conver_id)->second);

            return crow::response(201);
        });

    CROW_ROUTE(app, "/api/auth/login").methods(crow::HTTPMethod::Post)
        ([&](const crow::request& req) {
            auto body = crow::json::load(req.body);
            if (!body) {
                return crow::response(400, "Invalid JSON");
            }
            if (!body.has("username") || !body.has("password")) {
                return crow::response(400, "Missing username or password");
            }
            std::string username = body["username"].s();
            std::string password = body["password"].s();
            CROW_LOG_INFO << "Usename: " << username;

            std::shared_lock<std::shared_mutex> lock(g_user_mutex);
            auto it = g_users.find(username);
            if (it == g_users.end()) {
                crow::json::wvalue err;
                err["error"] = "User not found";
                return crow::response(404, err);
            }
            const User& user = it->second;
            std::string token = generate_token(username);

            crow::json::wvalue result;
            result["token"] = token;
            result["nickname"] = user.nickname;
            result["username"] = user.username;
            result["gender"] = gender_to_string(user.gender);
            // ...
            return crow::response(200, result);
        });
    CROW_ROUTE(app, "/api/auth/register").methods(crow::HTTPMethod::Post)
        ([&](const crow::request& req){
            auto body = crow::json::load(req.body);
            if (!body.has("username") || !body.has("nickname") || !body.has("password")) {
                crow::json::wvalue err;
                err["error"] = "Failed to get require params";
                return crow::response(400, err);
            }

            std::unique_lock<std::shared_mutex> lock(g_user_mutex);
            User user = {
                body["username"].s(),
                body["nickname"].s(),
                body["password"].s()
            };
            if (body.has("gender")) user.gender = string_to_gender(body["gender"].s());

            auto [it, inserted] = g_users.insert_or_assign(body["username"].s(), user);
            if (inserted) {
                return crow::response(201);
            }
            crow::json::wvalue result;
            result["message"] = "success";
            result["username"] = body["username"].s();
            return crow::response(200, result);
        });

    CROW_WEBSOCKET_ROUTE(app, "/ws")
        .onaccept([](const crow::request& req, void**) {
            auto body = crow::json::load(req.body);
            if (!body.has("conver_id")) {
                CROW_LOG_ERROR << "WebSocket connection is missing required data.";
                return false;
            }
            return true;
        })
        .onopen([&](crow::websocket::connection& conn) {
            CROW_LOG_INFO << "Websocket client connected";
            std::lock_guard<std::mutex> lock(g_conn_mutex);

        })
        .onmessage([](crow::websocket::connection& conn, const std::string& data, bool is_binary) {
        })
        .onclose([&](crow::websocket::connection& conn, const std::string& reason, unsigned short code) {
            CROW_LOG_INFO << "Connection have been closed, reason: " << reason << ", status code: " << code;
            std::lock_guard<std::mutex> lock(g_conn_mutex);

        })
        .onerror([](crow::websocket::connection& conn, const std::string& error) {
            CROW_LOG_ERROR << "Websocket error: " << error;
        });

}

void Backend::run() {
    app.port(8080).multithreaded().run();
}
