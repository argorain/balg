cmake_minimum_required(VERSION 2.8.4)
project(c203)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES
    c203-test.c
    c203.c
    c203.h)

add_executable(c203 ${SOURCE_FILES})