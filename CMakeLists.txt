cmake_minimum_required(VERSION 3.24)
project(cfrc)

set(CMAKE_CXX_STANDARD 11)

add_executable(cfrc main.cpp)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG a2d35a1cb9f3f7e2f1469d6a189751331dc99f96) # The commit hash for 1.9.0. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(cfrc PRIVATE cpr::cpr)
target_link_libraries(cfrc PRIVATE nlohmann_json::nlohmann_json)

