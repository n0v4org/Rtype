cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(modulenew VERSION 1.0)

set(SRC
    new.cpp
)

find_package(asio REQUIRED CONFIG)
add_library(modulenew SHARED ${SRC})

target_include_directories(modulenew PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../network/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libHolder
    ${CMAKE_CURRENT_SOURCE_DIR}/../../modules
    )
    
if(WIN32)
    target_include_directories(modulenew PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../libHolder/win)
else()
    target_include_directories(modulenew PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../libHolder/linux)
endif()


add_custom_command(
    TARGET modulenew POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:modulenew> ${CMAKE_CURRENT_SOURCE_DIR}/../../../bin
)

target_link_libraries(modulenew PRIVATE
    asio
)
