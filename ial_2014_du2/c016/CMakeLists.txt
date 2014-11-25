cmake_minimum_required(VERSION 2.8.4)
project(c016)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES
    c016-test.c
    c016.c
    c016.h)

add_executable(c016 ${SOURCE_FILES})