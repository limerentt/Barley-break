cmake_minimum_required(VERSION 3.21)
project(Barley_break)

set(CMAKE_CXX_STANDARD 23)

add_executable(test tests/test.cpp src/algorithm.h
        src/position.h)
