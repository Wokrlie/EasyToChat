#include <crow/app.h>
#include <crow/common.h>
#include <crow/http_request.h>
#include <crow/http_response.h>
#include <crow/json.h>
#include <crow/logging.h>
#include <crow/routing.h>
#include <crow/websocket.h>
#include <filesystem>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "functions/Time.h"
#include "functions/Convert.h"
#include "functions/Path.h"
#include "functions/JWT.h"
#include "types/Message.h"
#include "types/User.h"

// Datas
std::vector<Message> g_messages;
std::mutex g_message_mutex;
int g_next_id = 1;

std::unordered_map<std::string, User> g_users;
std::shared_mutex g_user_mutex;

std::vector<crow::websocket::connection*> g_connections;
std::mutex g_conn_mutex;

void broadcast_message(const std::string& msg);

int main(int argc, char* argv[]) {
    crow::SimpleApp app;

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

    if (g_messages.empty()) g_messages.push_back({
        g_next_id++,
        SenderType::System,
        "",
        "There is not any messages. Try to send some!",
        get_current_time()
    });

    CROW_ROUTE(app, "/api/messages")
        ([](const crow::request& req) {
            std::lock_guard<std::mutex> lock(g_message_mutex);

            std::string auth_header = req.get_header_value("Authorization");
            if (auth_header.empty()) return crow::response(401, "Missing Authorization header");
            const std::string prefix = "Bearer ";
            if (auth_header.compare(0, prefix.size(), prefix) != 0) return crow::response(401, "Invalid Authorization format");

            std::string token = auth_header.substr(prefix.size());
            auto username_opt = verify_token(token);
            if (!username_opt.has_value()) return crow::response(401, "Invalid token");

            // auth
            std::vector<crow::json::wvalue> json_messages;
            for (const auto& msg : g_messages) {
                crow::json::wvalue json_msg;
                json_msg["id"] = msg.id;
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
        ([](const crow::request& req) {
            CROW_LOG_DEBUG << "Received POST body: " << req.body;
            auto body = crow::json::load(req.body);
            if (!body) {
                return crow::response(400, "Invaild JSON");
            }

            if (!body.has("content")
                || !body.has("sender_type")
                || !body.has("sender_name")
            ) {
                return crow::response(400, "Failed because of omissions of paramters.");
            }

            std::string auth_header = req.get_header_value("Authorization");
            if (auth_header.empty()) return crow::response(401, "Missing Authorization header");
            const std::string prefix = "Bearer ";
            if (auth_header.compare(0, prefix.size(), prefix) != 0) return crow::response(401, "Invalid Authorization format");

            std::string token = auth_header.substr(prefix.size());
            auto username_opt = verify_token(token);
            if (!username_opt.has_value()) return crow::response(401, "Invalid token");


            if (!verify_token(token).has_value()) return crow::response(401, "Invaild token");

            std::string content = body["content"].s();
            std::string sender_type_str = body["sender_type"].s();
            std::string sender_name = body["sender_name"].s();
            SenderType sender_type = string_to_sender_type(sender_type_str);

            {
                std::lock_guard<std::mutex> lock(g_message_mutex);

                if (g_messages.size() == 1 && g_messages[0].sender_type == SenderType::System) {
                    g_messages.clear();
                }

                g_messages.push_back({
                    g_next_id++,
                    sender_type,
                    sender_name,
                    content,
                    get_current_time()
                });
            }

            crow::json::wvalue broadcast_msg;
            broadcast_msg["type"] = "new_msg";
            broadcast_message(broadcast_msg.dump());

            return crow::response(201);
        });

    CROW_ROUTE(app, "/api/auth/login").methods(crow::HTTPMethod::Post)
        ([](const crow::request& req) {
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
        ([](const crow::request& req){
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
            return true;
        })
        .onopen([](crow::websocket::connection& conn) {
            CROW_LOG_INFO << "Websocket client connected";
            conn.send_pong("WebSocket server connected");
            std::lock_guard<std::mutex> lock(g_conn_mutex);
            g_connections.push_back(&conn);
        })
        .onmessage([](crow::websocket::connection& conn, const std::string& data, bool is_binary) {
        })
        .onclose([](crow::websocket::connection& conn, const std::string& reason, unsigned short code) {
            CROW_LOG_INFO << "Connection have been closed, reason: " << reason << ", status code: " << code;
            std::lock_guard<std::mutex> lock(g_conn_mutex);
            g_connections.erase(
                std::remove(g_connections.begin(), g_connections.end(), &conn),
                g_connections.end()
            );
        })
        .onerror([](crow::websocket::connection& conn, const std::string& error) {
            CROW_LOG_ERROR << "Websocket error: " << error;
        });

    app.port(8080).multithreaded().run();
}

void broadcast_message(const std::string& msg) {
    std::lock_guard<std::mutex> lock(g_conn_mutex);
    for (auto conn : g_connections) {
        if (conn) conn->send_text(msg);
    }
}
