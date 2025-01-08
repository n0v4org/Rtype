cmake_minimum_required(VERSION 3.26)

project(modulenew VERSION 1.0)

set(SRC
    new.cpp
)

find_package(asio REQUIRED CONFIG)

add_library(modulenew SHARED ${SRC})

target_include_directories(modulenew PUBLIC ${GLOBAL_INCLUDE_DIRS})

add_custom_command(
    TARGET modulenew POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:modulenew> ${CMAKE_CURRENT_SOURCE_DIR}/../../../bin
)

target_link_libraries(modulenew PRIVATE asio)
