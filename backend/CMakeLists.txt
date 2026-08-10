cmake_minimum_required(VERSION 3.15)
project(EasyToChatBackend)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Crow REQUIRED)
find_package(jwt-cpp CONFIG REQUIRED)
find_package(LibDataChannel REQUIRED)
find_package(stduuid REQUIRED)

file(GLOB_RECURSE SOURCES
     "src/*.cpp"
)


add_library(EasyToChatBackend STATIC ${SOURCES})
target_link_libraries(EasyToChatBackend PRIVATE
    pthread
    jwt-cpp::jwt-cpp
    stduuid
)
target_include_directories(EasyToChatBackend PRIVATE
    ${stduuid_SOURCE_DIR}/include
)

if(ENABLE_TESTS)
    target_sources(EasyToChatBackend PRIVATE
        tests/dependencies.cpp
    )
endif()
