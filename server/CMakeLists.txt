cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(RtypeServer VERSION 1.0)

set(SRCS
    src/Core.cpp
    src/Arguments.cpp
    game/GameServer.cpp
    lobby/Lobby.cpp
    lobby/utils.cpp
    lobby/error_handling.cpp
    lobby/Commands/action.cpp
    lobby/Commands/delete.cpp
    lobby/Commands/get.cpp
    lobby/Commands/set.cpp
    lobby/Commands/update.cpp
)

set(TEST
    src/test/Arguments.test.cpp
    src/test/main.test.cpp
)

add_executable(r-type_server ${SRCS} src/main.cpp)

find_package(asio REQUIRED CONFIG)

target_link_libraries(r-type_server PRIVATE asio  rtype_network)

target_include_directories(r-type_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(SFML 2.6.2 COMPONENTS system window graphics audio REQUIRED CONFIG)
find_package(GTest CONFIG REQUIRED)

include_directories(r-type_server PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/game
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/ecs
    ${CMAKE_CURRENT_SOURCE_DIR}/../network/udp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Common
)

target_link_libraries(r-type_server PRIVATE 
    asio
    #sfml
    zefir
    rtype_network
)

enable_testing()

add_executable(r-type_server_tests ${TEST} ${SRCS})

target_link_libraries(r-type_server_tests PRIVATE
    GTest::gtest GTest::gtest_main
    asio
    #sfml
    zefir
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
    rtype_network
)
target_include_directories(r-type_server_tests PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/game
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/ecs
    ${CMAKE_CURRENT_SOURCE_DIR}/../network/udp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Common
)

add_test(NAME RtypeTests COMMAND r-type_tests)

set_target_properties(r-type_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)
set_target_properties(r-type_server_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)


if(WIN32) 
    file(COPY "${CMAKE_SOURCE_DIR}/vcpkg_installed/x64-windows/debug/bin/" DESTINATION "${CMAKE_BINARY_DIR}/server/Debug/")
endif()
