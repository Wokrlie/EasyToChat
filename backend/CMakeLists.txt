cmake_minimum_required(VERSION 3.15)
project(EasyToChatBackend)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(json)
find_package(Crow REQUIRED)
find_package(jwt-cpp CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES
     "src/*.cpp"
     "src/*.c"
)

add_executable(EasyToChatBackend ${SOURCES})
target_link_libraries(EasyToChatBackend PRIVATE
    pthread
    nlohmann_json::nlohmann_json
    jwt-cpp::jwt-cpp
)
