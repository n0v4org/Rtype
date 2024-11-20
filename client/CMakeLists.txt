cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Rtype VERSION 1.0)

set(SRCS
    src/main.cpp
    )

find_package(GTest CONFIG REQUIRED)

enable_testing()

add_executable(r-type_client ${SRCS})
target_include_directories(r-type_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(r-type_server PRIVATE GTest::gtest GTest::gtest_main)
add_test(AllTestsInMain r-type_server)
