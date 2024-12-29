cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(rtype_sfml VERSION 1.0)

set(SRC
    Sfml.cpp
)

add_library(sfml SHARED ${SRC})


find_package(SFML 2.6.2 COMPONENTS system window graphics audio REQUIRED CONFIG)

message(STATUS "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ ${SFML_INCLUDE_DIRS}")

target_include_directories(sfml PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/../includes ${CMAKE_CURRENT_SOURCE_DIR}/../../

)

if(WIN32)
    target_compile_definitions(sfml PRIVATE _WIN32_WINNT=0x0A00)
endif()
target_link_libraries(sfml PRIVATE 
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
)




