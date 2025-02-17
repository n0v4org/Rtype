cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(rtype_sfml VERSION 1.0)

set(SRC
    Engine.cpp
    Console.cpp
)


add_library(zefir STATIC ${SRC})

find_package(asio REQUIRED CONFIG)
find_package(nlohmann_json REQUIRED)

target_include_directories(zefir PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/../network/
    ${CMAKE_CURRENT_SOURCE_DIR}/../network/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libHolder
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/
)

    
if(WIN32)
    target_include_directories(zefir PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libHolder/win)
else()
    target_include_directories(zefir PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libHolder/linux)
endif()



    
target_link_libraries(zefir PRIVATE 
    rtype_network
    asio
)