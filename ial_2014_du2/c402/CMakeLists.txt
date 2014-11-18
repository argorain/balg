cmake_minimum_required(VERSION 2.8.4)
project(c402)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    c402-test.c
    c402.c
    c402.h)

add_executable(c402 ${SOURCE_FILES})