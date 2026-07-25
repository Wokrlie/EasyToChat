#include <crow/app.h>
#include <crow/common.h>
#include <crow/http_request.h>
#include <crow/http_response.h>
#include <crow/json.h>
#include <crow/logging.h>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "functions/Time.h"
#include "functions/Convert.h"
#include "types/Message.h"
#include "types/User.h"

std::vector<Message> g_messages;
std::mutex g_message_mutex;
int g_next_id = 1;

std::unordered_map<std::string, User> g_users;
std::shared_mutex g_user_mutex;

int main() {
    crow::SimpleApp app;

    // test
    g_users.insert_or_assign("Wokrlie", User{ "Wokrlie John" });
    g_users.insert_or_assign("Bonus", User{ "Bonus Louis" });
    // end test

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
        ([]() {
            std::lock_guard<std::mutex> lock(g_message_mutex);

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
            return result;
        });
    CROW_ROUTE(app, "/api/messages").methods(crow::HTTPMethod::Post)
        ([](const crow::request& req) {
            CROW_LOG_DEBUG << "Received POST body: " << req.body;
            auto body = crow::json::load(req.body);
            if (!body) {
                return crow::response(400, "Invaild JSON");
            }

            if (!body.has("content") || !body.has("sender_type") || !body.has("sender_name")) {
                return crow::response(400, "Missing fields: content, sender_type, sender_name");
            }

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

            return crow::response(201);
        });

    CROW_ROUTE(app, "/api/auth/login")
        ([](const crow::request& req) {
            const char* username_cstr = req.url_params.get("username");
            if (!username_cstr) {
                return crow::response(400, "Missing 'username' query parameter");
            }
            CROW_LOG_INFO << "Usename: " << username_cstr;
            std::string username = username_cstr;

            std::shared_lock<std::shared_mutex> lock(g_user_mutex);
            auto it = g_users.find(username);
            if (it == g_users.end()) {
                crow::json::wvalue err;
                err["error"] = "User not found";
                return crow::response(404, err);
            } else {
                const User& user = it->second;

               crow::json::wvalue result;
               result["nickname"] = user.nickname;
               // ...
               return crow::response(200, result);
            }
        });
    CROW_ROUTE(app, "/api/auth/register").methods(crow::HTTPMethod::Post)
        ([](const crow::request& req){
            auto body = crow::json::load(req.body);
            if (!body.has("username") || !body.has("nickname")) {
                crow::json::wvalue err;
                err["error"] = "Failed to get require params";
                return crow::response(400, err);
            }

            std::unique_lock<std::shared_mutex> lock(g_user_mutex);
            User user = {
                body["nickname"].s()
            };
            auto [it, inserted] = g_users.insert_or_assign(body["username"].s(), user);
            if (inserted) {
                return crow::response(201);
            }
            crow::json::wvalue result;
            result["message"] = "success";
            result["username"] = body["username"].s();
            return crow::response(200, result);
        });

    app.port(8080).multithreaded().run();
}
