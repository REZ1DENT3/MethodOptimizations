cmake_minimum_required(VERSION 3.2)
project(steepest_descent)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(steepest_descent ${SOURCE_FILES})