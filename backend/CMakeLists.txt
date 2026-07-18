cmake_minimum_required(VERSION 3.15)
project(EasyToChatBackend LANGUAGE CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Boost REQUIRED COMPONENTS system thread filesystem)
find(Crow REQUIRED)

add_executable(EasyToChatBackend src/main.cpp)
target_link_libraries(EasyToChatBackend PRIVATE
    Boost::system
    Boost::thread
    Boost::filesystem
    pthread
)
