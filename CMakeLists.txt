cmake_minimum_required(VERSION 3.22.2)

IF (WIN32)

    set(CMAKE_C_COMPILER C:/msys64/mingw64/bin/gcc.exe)
    set(CMAKE_CXX_COMPILER C:/msys64/mingw64/bin/g++.exe)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

    
    set(SFML_DIR "C:/Program Files(x86)/SFML")

ELSEIF (APPLE)

    # run 'where clang' and 'where clang++' to get paths
    set(CMAKE_C_COMPILER /usr/bin/clang)
    set(CMAKE_CXX_COMPILER /usr/bin/clang++)

ELSEIF (UNIX AND NOT APPLE)
    # run 'which gcc' and 'which g++' to get paths
    set(CMAKE_C_COMPILER /usr/bin/gcc)
    set(CMAKE_CXX_COMPILER /usr/bin/g++)

ENDIF()
    
# Get project name from folder name
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

set(CMAKE_BUILD_TYPE "Release")
# Use c++ 17
set(CMAKE_CXX_STANDARD 17)
# Enable additional warnings and debug mode
# https://caiorss.github.io/C-Cpp-Notes/compiler-flags-options.html
set (CMAKE_CXX_FLAGS "-W -pedantic")

set(SOURCES src/main.cpp src/gol.cpp)

include_directories(include)

add_executable(${PROJECT_NAME} ${SOURCES})


file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

target_link_libraries(${PROJECT_NAME} sfml-graphics)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})

install(DIRECTORY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_INSTALL_PREFIX})