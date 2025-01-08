cmake_minimum_required(VERSION 3.26)

# Set C++ standard globally
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define the main project
project(Rtype VERSION 1.0)

# Common include directories
set(COMMON_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../libHolder
    ${CMAKE_CURRENT_SOURCE_DIR}/../../network/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../network/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../network/udp/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../network/tcp/include
)

# Platform-specific include directories
if(WIN32)
    list(APPEND COMMON_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../libHolder/win)
else()
    list(APPEND COMMON_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../libHolder/linux)
endif()

# Make COMMON_INCLUDE_DIRS globally accessible
set(GLOBAL_INCLUDE_DIRS ${COMMON_INCLUDE_DIRS} CACHE INTERNAL "Global include directories")

# Define subdirectories (triggers sub-CMakeLists)
add_subdirectory(NewModule)
add_subdirectory(NewModulecopy)
