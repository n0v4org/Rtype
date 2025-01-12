cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(RtypeServer VERSION 1.0)

set(SRCS
    src/Core.cpp
    src/Arguments.cpp
    game/game.cpp
)

set(TEST
    src/test/Arguments.test.cpp
    src/test/main.test.cpp
)

add_executable(r-type_client ${SRCS}  src/main.cpp)

find_package(asio REQUIRED CONFIG)

target_link_libraries(r-type_client PRIVATE asio rtype_network)
find_package(SFML 2.6.2 COMPONENTS system window graphics audio  REQUIRED CONFIG)
find_package(GTest CONFIG REQUIRED)

include_directories(r-type_client PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/include
${CMAKE_CURRENT_SOURCE_DIR}/game
${CMAKE_CURRENT_SOURCE_DIR}/../engine
${CMAKE_CURRENT_SOURCE_DIR}/../engine/ecs
${CMAKE_CURRENT_SOURCE_DIR}/../Common
)

target_link_libraries(r-type_client PRIVATE 
#sfml
zefir
asio
sfml-system
sfml-window
sfml-graphics
sfml-audio
)

set_target_properties(r-type_client PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)

enable_testing()

add_executable(r-type_client_tests ${TEST} ${SRCS})

target_link_libraries(r-type_client_tests PRIVATE
    GTest::gtest GTest::gtest_main
    rtype_network
    zefir
    asio
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
)

target_include_directories(r-type_client_tests PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/game
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/ecs
    ${CMAKE_CURRENT_SOURCE_DIR}/../Common
)

add_test(NAME type_client_tests COMMAND r-type_tests)

set_target_properties(r-type_client_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)
