cmake_minimum_required(VERSION 2.8.4)
project(c201)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    c201-test.c
    c201.c
    c201.h)

add_executable(c201 ${SOURCE_FILES})