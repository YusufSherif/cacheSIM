cmake_minimum_required(VERSION 3.12)
project(cacheSIM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -Wall")     #-gdwarf-3

add_executable(cacheSIM
        main.cpp cacheLine.cpp cacheLine.h cache.cpp cache.h)
