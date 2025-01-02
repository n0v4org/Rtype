cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(RtypeServer VERSION 1.0)

set(SRCS
    src/Core.cpp
    src/Arguments.cpp
)

set(TEST
    src/test/Arguments.test.cpp
    src/test/main.test.cpp
)

add_executable(r-type_server ${SRCS} src/main.cpp)

find_package(asio REQUIRED CONFIG)

target_link_libraries(r-type_server PRIVATE asio  rtype_network)

target_include_directories(r-type_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(GTest CONFIG REQUIRED)

enable_testing()

add_executable(r-type_server_tests ${TEST} ${SRCS})

target_link_libraries(r-type_server_tests PRIVATE GTest::gtest GTest::gtest_main  rtype_network)
target_include_directories(r-type_server_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME RtypeTests COMMAND r-type_tests)

if(WIN32)
    target_compile_definitions(r-type_server PRIVATE _WIN32_WINNT=0x0A00)
    target_compile_definitions(r-type_server_tests PRIVATE _WIN32_WINNT=0x0A00)
endif()
