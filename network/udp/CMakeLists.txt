cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(RtypeNetwork VERSION 1.0)

set(SRCS
    src/Server.cpp
    src/Client.cpp
)

add_library(game_network STATIC ${SRCS})

find_package(asio REQUIRED CONFIG)

find_package(nlohmann_json 3.2.0 REQUIRED)

target_link_libraries(game_network PRIVATE asio nlohmann_json::nlohmann_json)

target_include_directories(game_network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(WIN32)
    target_compile_definitions(game_network PRIVATE _WIN32_WINNT=0x0A00)
endif()
