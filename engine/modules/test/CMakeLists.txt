cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /FS")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(moduletest VERSION 1.0)

set(SRC
	test.cpp
)

find_package(asio REQUIRED CONFIG)

add_library(moduletest SHARED ${SRC})

target_include_directories(moduletest PUBLIC ${GLOBAL_INCLUDE_DIRS})

add_custom_command(
	TARGET moduletest POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:moduletest> ${CMAKE_CURRENT_SOURCE_DIR}/../../../bin
)

target_link_libraries(moduletest PRIVATE asio)

