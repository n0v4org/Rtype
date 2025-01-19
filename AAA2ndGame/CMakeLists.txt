cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(RtypeServer VERSION 1.0)

set(SRCS
    src/main.cpp
)



add_executable(SecondGame ${SRCS})

find_package(asio REQUIRED CONFIG)

target_link_libraries(SecondGame PRIVATE asio  rtype_network)

target_include_directories(SecondGame PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(SFML 2.6.2 COMPONENTS system window graphics audio REQUIRED CONFIG)
find_package(GTest CONFIG REQUIRED)

include_directories(SecondGame PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/game
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/ecs
    ${CMAKE_CURRENT_SOURCE_DIR}/../network/udp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Common
)

target_link_libraries(SecondGame PRIVATE 
    asio
    #sfml
    zefir
    rtype_network
)


set_target_properties(SecondGame PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)


if(WIN32) 
    file(COPY "${CMAKE_SOURCE_DIR}/vcpkg_installed/x64-windows/debug/bin/" DESTINATION "${CMAKE_BINARY_DIR}/server/Debug/")
endif()
