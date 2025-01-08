cmake_minimum_required(VERSION 3.26)

# Define the module project
project(modulenew VERSION 1.0)

# Source files for this module
set(SRC
    new.cpp
)

# Find dependencies (example: asio)
find_package(asio REQUIRED CONFIG)

# Create a shared library
add_library(modulenew SHARED ${SRC})

# Use the global include directories
target_include_directories(modulenew PUBLIC ${GLOBAL_INCLUDE_DIRS})

# Add post-build command to copy the library to the `bin` folder
add_custom_command(
    TARGET modulenew POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:modulenew> ${CMAKE_CURRENT_SOURCE_DIR}/../../../bin
)

# Link dependencies
target_link_libraries(modulenew PRIVATE asio)
