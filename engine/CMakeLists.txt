cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(rtype_sfml VERSION 1.0)

set(SRC
    Engine.cpp
)


add_library(zefir STATIC ${SRC})

find_package(asio REQUIRED CONFIG)

target_include_directories(zefir PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ ${CMAKE_CURRENT_SOURCE_DIR}/../network/)


    
target_link_libraries(zefir PRIVATE 
    game_network
    asio
)