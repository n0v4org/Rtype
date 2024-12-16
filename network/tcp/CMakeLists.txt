cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(RtypeNetwork VERSION 1.0)

set(SRCS
    src/Lobby.cpp
    src/Commands/FactoryCmd.cpp
    src/Commands/Join.cpp
    src/Commands/GetAllLobby.cpp
    src/Commands/GetLobby.cpp
    src/Commands/Launch.cpp
)

add_library(lobby_network STATIC ${SRCS})

find_package(asio REQUIRED CONFIG)

find_package(nlohmann_json 3.2.0 REQUIRED)

target_link_libraries(lobby_network PRIVATE asio nlohmann_json::nlohmann_json)

target_include_directories(lobby_network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(WIN32)
    target_compile_definitions(game_network PRIVATE _WIN32_WINNT=0x0A00)
endif()
