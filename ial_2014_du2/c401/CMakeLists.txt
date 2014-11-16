cmake_minimum_required(VERSION 2.8.4)
project(c401)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    c401-test.c
    c401.c
    c401.h)

add_executable(c401 ${SOURCE_FILES})