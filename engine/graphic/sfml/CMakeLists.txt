cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(rtype_sfml VERSION 1.0)

set(SRC
    Sfml.cpp
)

add_library(sfml SHARED ${SRC})

target_include_directories(sfml PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/../includes ${CMAKE_CURRENT_SOURCE_DIR}/../../)
