cmake_minimum_required(VERSION 3.10)
project(.)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

file(GLOB_RECURSE INCLUDE "../include/*.h")
file(GLOB_RECURSE SOURCES "../src/*.c")

include_directories("../include")
add_executable(main main.c ${SOURCES} ${INCLUDE})