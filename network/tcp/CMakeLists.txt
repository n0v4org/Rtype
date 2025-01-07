cmake_minimum_required(VERSION 3.26)

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

add_library( STATIC ${SRCS})

find_package(asio REQUIRED CONFIG)

find_package(nlohmann_json REQUIRED)

target_link_libraries( PRIVATE asio nlohmann_json::nlohmann_json)

target_include_directories( PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(WIN32)
    target_compile_definitions( PRIVATE _WIN32_WINNT=0x0A00)
endif()
