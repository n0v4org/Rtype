cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(Rtype VERSION 1.0)
add_subdirectory(network)
add_subdirectory(engine)
add_subdirectory(engine/graphic/sfml)
add_subdirectory(server)
add_subdirectory(client)

add_subdirectory(bj)


add_subdirectory(engine/modules)