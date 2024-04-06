cmake_minimum_required(VERSION 3.15)
project("SO2_rail_simulator")

set(CMAKE_CXX_STANDARD 20)



set(SOURCES
        main.cpp
        )

add_executable(main_app ${SOURCES})

find_package( Threads )

target_link_libraries( main_app ${CMAKE_THREAD_LIBS_INIT} )

# Adding sfml
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(main_app ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

target_link_libraries(main_app sfml-graphics sfml-window sfml-system)
