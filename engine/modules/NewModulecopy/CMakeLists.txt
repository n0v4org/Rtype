cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(modulenew2 VERSION 1.0)

set(SRC
    new.cpp
)

find_package(asio REQUIRED CONFIG)
add_library(modulenew2 SHARED ${SRC})

target_include_directories(modulenew2 PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../network/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libHolder
    ${CMAKE_CURRENT_SOURCE_DIR}/../../modules
    )
    
if(WIN32)
    target_include_directories(modulenew2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../libHolder/win)
else()
    target_include_directories(modulenew2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../libHolder/linux)
endif()


add_custom_command(
    TARGET modulenew2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:modulenew2> ${CMAKE_CURRENT_SOURCE_DIR}/../../../bin
)

target_link_libraries(modulenew2 PRIVATE
    asio
)
