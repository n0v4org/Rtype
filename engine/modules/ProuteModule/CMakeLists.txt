cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(rtype_sfml VERSION 1.0)

set(SRC
    proute.cpp
)


add_library(moduleproute SHARED ${SRC})

target_include_directories(moduleproute PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../network/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libHolder
    ${CMAKE_CURRENT_SOURCE_DIR}/../../modules
)

add_custom_command(
    TARGET moduleproute POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:moduleproute> ${CMAKE_CURRENT_SOURCE_DIR}/../../../bin
)
