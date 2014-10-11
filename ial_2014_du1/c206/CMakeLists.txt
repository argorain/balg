cmake_minimum_required(VERSION 2.8.4)
project(c206)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES
    c206-test.c
    c206.c
    c206.h)

add_executable(c206 ${SOURCE_FILES})