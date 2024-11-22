cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(RtypeServer VERSION 1.0)

set(SRCS
    src/Core.cpp
    src/Arguments.cpp
    src/networking/Server.cpp
)

set(TEST
    src/test/Arguments.test.cpp
    src/test/main.test.cpp
)

add_executable(r-type_server ${SRCS} src/main.cpp)

find_package(asio CONFIG REQUIRED)

target_link_libraries(r-type_server PRIVATE asio)

target_include_directories(r-type_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(GTest CONFIG REQUIRED)

enable_testing()

add_executable(r-type_server_tests ${TEST} ${SRCS})

target_link_libraries(r-type_server_tests PRIVATE GTest::gtest GTest::gtest_main)
target_include_directories(r-type_server_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME RtypeTests COMMAND r-type_tests)
