cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(BlackJack VERSION 1.0)

set(SRCS
    main.cpp
)



add_executable(BlackJack ${SRCS})

find_package(asio REQUIRED CONFIG)

target_link_libraries(BlackJack PRIVATE asio  rtype_network)

target_include_directories(BlackJack PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(SFML 2.6.2 COMPONENTS system window graphics audio REQUIRED CONFIG)
find_package(GTest CONFIG REQUIRED)

include_directories(BlackJack PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/game
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/ecs
    ${CMAKE_CURRENT_SOURCE_DIR}/../network/udp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Common
)

target_link_libraries(BlackJack PRIVATE 
    asio
    #sfml
    zefir
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
    rtype_network
)




set_target_properties(BlackJack PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)


if(WIN32) 
    file(COPY "${CMAKE_SOURCE_DIR}/vcpkg_installed/x64-windows/debug/bin/" DESTINATION "${CMAKE_BINARY_DIR}/server/Debug/")
endif()
