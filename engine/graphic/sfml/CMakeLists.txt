cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /FS")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(sfml VERSION 1.0)

set(SRC
    Sfml.cpp
    HPBar.cpp
)

add_library(sfml SHARED ${SRC})


find_package(SFML 2.6.2 COMPONENTS system window graphics audio REQUIRED CONFIG)


target_include_directories(sfml PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/../includes ${CMAKE_CURRENT_SOURCE_DIR}/../../

)

if(APPLE)
    target_link_libraries(sfml PRIVATE 
        "-framework CoreAudio"
        "-framework AudioToolbox"
        "-framework CoreServices"
        "-framework CoreFoundation"
        "-framework IOKit"
    )
endif()

if(WIN32)
    target_compile_definitions(sfml PRIVATE _WIN32_WINNT=0x0A00)
endif()
target_link_libraries(sfml PRIVATE 
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
)

add_custom_command(
    TARGET sfml POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:sfml> ${CMAKE_CURRENT_SOURCE_DIR}/../../../bin
)

add_custom_command(
    TARGET sfml POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-system>
        $<TARGET_FILE:sfml-window>
        $<TARGET_FILE:sfml-graphics>
        $<TARGET_FILE:sfml-audio>
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../bin
)