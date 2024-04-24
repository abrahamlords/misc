cmake_minimum_required(VERSION 3.17)
project(cse310proj1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(cse310proj1 encode.cpp)
