cmake_minimum_required(VERSION 3.27)

project(start)

set(CMAKE_CXX_COMPILER "g++")
add_compile_options(-std=c++11)
add_compile_options(-g)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

option(TEST "build test" ON)
if(TEST)
    add_subdirectory(test)
endif()

set(SRC_LIST 
./src/base/Thread.cpp
./src/base/Semaphore.cpp
)

add_library(start SHARED ${SRC_LIST})