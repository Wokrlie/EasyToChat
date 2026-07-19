cmake_minimum_required(VERSION 3.15)
project(EasyToChatBackend)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Crow REQUIRED)

file(GLOB_RECURSE SOURCES
     "src/*.cpp"
     "src/*.c"
)

add_executable(EasyToChatBackend ${SOURCES})
target_link_libraries(EasyToChatBackend PRIVATE
  pthread
)
