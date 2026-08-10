#pragma once
#include <crow/app.h>
#include <crow/common.h>
#include <crow/http_request.h>
#include <crow/http_response.h>
#include <crow/json.h>
#include <crow/logging.h>
#include <crow/routing.h>
#include <crow/websocket.h>
#include <rtc/rtc.hpp>
#include <filesystem>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "functions/Convert.h"
#include "functions/Path.h"
#include "functions/Time.h"
#include "functions/auth/JWT.h"
#include "functions/Conver.h"


class Backend {
    public:
        Backend();
        void run();
        ~Backend();

    private:
        crow::SimpleApp app;

        std::unordered_map<ConverID, Conver> g_conversations;
        std::mutex g_conver_mutex;

        std::unordered_map<std::string, User> g_users; // username match Conver
        std::shared_mutex g_user_mutex;

        std::unordered_map<std::string, std::vector<crow::websocket::connection*>> g_connections; // Conver id match conns
        std::mutex g_conn_mutex;

};
