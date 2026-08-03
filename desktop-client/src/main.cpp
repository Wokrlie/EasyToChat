#include "webview/webview.h"
#include <filesystem>
// #include <fstream>
#include <iostream>

int main() {
    try {
        std::filesystem::path currentPath = std::filesystem::current_path();
        std::filesystem::path htmlRelative = "../../frontend/dist/index.html";
        std::filesystem::path htmlAbsolute = std::filesystem::canonical(currentPath / htmlRelative);
        std::string url = "file://" + htmlAbsolute.u8string();
        // std::ifstream file(htmlAbsolute);
        // if (file.is_open()) {
            // std::string content((std::istreambuf_iterator<char>(file)),
                                 // std::istreambuf_iterator<char>());
            // std::cout << "HTML content:\n" << content << std::endl;
        // } else {
            // std::cerr << "Failed to open file: " << htmlAbsolute << std::endl;
        // }

        webview::webview w(false, nullptr);
        w.set_title("EasyToChat");
        w.set_size(1280, 720, WEBVIEW_HINT_NONE);
        w.navigate(url);
        w.run();
    } catch (const webview::exception &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}
