cmake_minimum_required(VERSION 3.25)
project(ProcessorSimulator)

set(CMAKE_CXX_STANDARD 23)

add_executable(ProcessorSimulator main.cpp
        main_6502.h)
