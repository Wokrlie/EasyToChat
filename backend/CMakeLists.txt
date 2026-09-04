cmake_minimum_required(VERSION 3.15)
project(EasyToChatBackend)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Crow CONFIG REQUIRED)
find_package(jwt-cpp REQUIRED)
find_package(LibDataChannel REQUIRED)
find_package(stduuid CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

file(GLOB_RECURSE ETC_SOURCES
  "src/*.cpp"
)
add_library(ETCBackend SHARED ${ETC_SOURCES})
target_link_libraries(ETCBackend PRIVATE
    pthread
    jwt-cpp::jwt-cpp
    stduuid
    nlohmann_json::nlohmann_json
)
target_include_directories(ETCBackend
  PRIVATE ${stduuid_SOURCE_DIR}/include
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/etc
)
set_target_properties(ETCBackend PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Please setup Windows Configuration manually here if you need,
# I mainly tested it on Linux platform.
