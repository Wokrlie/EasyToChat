#include <crow/app.h>
#include <crow/http_response.h>
#include <string>

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/api/ping")
        ([]() {
            return crow::response("pong");
        });

    app.port(8080).multithreaded().run();
}
