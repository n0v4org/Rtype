cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Rtype VERSION 1.0)
add_subdirectory(network/tcp)
add_subdirectory(network/udp)
add_subdirectory(server)
add_subdirectory(client)