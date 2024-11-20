cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(RtypeServer VERSION 1.0)

set(SRCS
    src/main.cpp
    src/Core.cpp
    src/Arguments.cpp
    )

set(TEST
)

add_executable(r-type_server ${SRCS})
target_include_directories(r-type_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(GTest CONFIG REQUIRED)

enable_testing()

add_executable(r-type_server_tests ${TEST})

target_link_libraries(r-type_server_tests PRIVATE GTest::gtest GTest::gtest_main)
target_include_directories(r-type_server_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME RtypeTests COMMAND r-type_tests)
