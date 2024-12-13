cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(RtypeServer VERSION 1.0)

set(SRCS
    src/Core.cpp
    src/Arguments.cpp
    src/main.cpp
    game/game.cpp
)

set(TEST
    src/test/Arguments.test.cpp
    src/test/main.test.cpp
)

add_executable(r-type_server ${SRCS})

find_package(asio REQUIRED CONFIG)

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
    sfml
    zefir
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
    game_network
)

#enable_testing()

#add_executable(r-type_server  ${SRCS})


#target_link_libraries(r-type_server_tests PRIVATE GTest::gtest GTest::gtest_main)
#target_include_directories(r-type_server_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
#add_test(NAME RtypeTests COMMAND r-type_tests)
