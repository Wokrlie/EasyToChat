cmake_minimum_required(VERSION 3.15)
project(EasyToChatDesktopClient)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
    webview
    GIT_REPOSITORY https://github.com/webview/webview
    GIT_TAG 0.12.0
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(webview)

add_executable(Client src/main.cpp)
target_link_libraries(Client PRIVATE webview::core)
