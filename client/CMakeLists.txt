cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(RtypeServer VERSION 1.0)

set(SRCS
    src/Core.cpp
    src/Arguments.cpp
    src/main.cpp
    game/game.cpp
)

set(TEST
    src/test/Arguments.test.cpp
    src/test/main.test.cpp
)

add_executable(r-type_client ${SRCS})

include_directories(r-type_client PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/game
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/ecs
)
#find_package(boost_asio REQUIRED CONFIG)





# Chercher les bibliothèques par leur nom (sans extension)
#find_library(SFML sfmlt PATHS ${LIBRARY_SEARCH_PATH})
#find_library(ZEFIR zefir PATHS ${LIBRARY_SEARCH_PATH})
#
## Vérifier si les bibliothèques ont été trouvées
#if (NOT SFML OR NOT ZEFIR)
#    message(FATAL_ERROR "Une ou plusieurs bibliothèques n'ont pas été trouvées.")
#endif()




target_link_libraries(r-type_client PRIVATE 
    sfml
    zefir
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
)

#enable_testing()

#add_executable(r-type_client  ${SRCS})


#target_link_libraries(r-type_server_tests PRIVATE GTest::gtest GTest::gtest_main)
#target_include_directories(r-type_server_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
#add_test(NAME RtypeTests COMMAND r-type_tests)
