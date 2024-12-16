cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Rtype VERSION 1.0)

set(SRCS
    src/Core.cpp
    src/Arguments.cpp
    src/networking/TcpClient.cpp
)

set(TEST
    src/test/main.test.cpp
    src/test/Arguments.test.cpp
)

add_executable(r-type_client ${SRCS} src/main.cpp)

find_package(asio REQUIRED CONFIG)

target_link_libraries(r-type_client PRIVATE asio lobby_network game_network)

target_include_directories(r-type_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(GTest CONFIG REQUIRED)

enable_testing()

add_executable(r-type_client_tests ${TEST} ${SRCS})

target_link_libraries(r-type_client_tests PRIVATE GTest::gtest GTest::gtest_main lobby_network game_network)
target_include_directories(r-type_client_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME type_client_tests COMMAND r-type_tests)

if(WIN32)
    target_compile_definitions(r-type_client PRIVATE _WIN32_WINNT=0x0A00)
    target_compile_definitions(r-type_client_tests PRIVATE _WIN32_WINNT=0x0A00)
endif()
