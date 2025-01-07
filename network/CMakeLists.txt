cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(RtypeNetwork VERSION 1.0)

set(SRCS
    udp/src/Server.cpp
    udp/src/Client.cpp
    tcp/src/Server.cpp
    tcp/src/Client.cpp
    tcp/src/queue.cpp
    src/Network_server.cpp
    src/Network_client.cpp
)

add_library(rtype_network STATIC ${SRCS})

find_package(asio REQUIRED CONFIG)

find_package(nlohmann_json 3.2.0 REQUIRED)

target_link_libraries(rtype_network PRIVATE asio nlohmann_json::nlohmann_json)

target_include_directories(rtype_network PUBLIC
 ${CMAKE_CURRENT_SOURCE_DIR}/include
 ${CMAKE_CURRENT_SOURCE_DIR}/udp/include
 ${CMAKE_CURRENT_SOURCE_DIR}/tcp/include
)

if(WIN32)
    target_compile_definitions(rtype_network PRIVATE _WIN32_WINNT=0x0A00)
endif()
