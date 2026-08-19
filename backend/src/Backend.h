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

#include "functions/utils/Convert.h"
#include "functions/utils/Path.h"
#include "functions/utils/Time.h"
#include "functions/auth/JWT.h"
#include "functions/type/Conver.h"


class Backend {
    public:
        Backend();
        void run();
        ~Backend();

    private:
        crow::SimpleApp app;

        std::unordered_map<ConverID, Conver> _conversations;
        std::mutex _conver_mutex;

        std::unordered_map<std::string, User> _users; // username match User
        std::shared_mutex _user_mutex;

        std::unordered_map<ConverID, std::vector<crow::websocket::connection*>> _connections; // Conver id match conns
        std::mutex _conn_mutex;

};
