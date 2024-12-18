cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Rtype VERSION 1.0)



#add_subdirectory(network/tcp)


add_subdirectory(engine/graphic/sfml)
add_subdirectory(network/tcp)
add_subdirectory(network/udp)
add_subdirectory(engine)
add_subdirectory(server)
add_subdirectory(client)